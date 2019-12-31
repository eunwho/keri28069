#include	<header.h>
#include	<extern.h>
// include <scia,h>

#define CPU_FREQ    90E6
#define LSPCLK_FREQ CPU_FREQ/4
#define SCI_FREQ    115200
//#define SCI_FREQ    38400
// #define SCI_FREQ    230400
#define SCI_PRD     (LSPCLK_FREQ/(SCI_FREQ*8))-1

#define UARTA_BAUD_RATE          SCI_PRD     // 115200

int scia_rx_start_addr=0;
int scia_rx_end_addr=0;
int sciRxPoint=0;


char msg_box[20]={0};
char sciaRxIrqBox[SCIA_RX_BUF_MAX] = {0};
char scia_rx_msg_box[SCIA_RX_BUF_MAX] = {0};
char scia_tx_msg_box[SCIA_TX_BUF_MAX] = {0};

void scia_fifo_init()
{
	SciaRegs.SCICCR.all =0x0007;   // 1stopbit,No parity,8 char bits, async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.bit.TXINTENA 	=1;	// debug
//	SciaRegs.SCICTL2.bit.RXBKINTENA     =0;
	SciaRegs.SCICTL2.bit.RXBKINTENA     = 1;    // 2017
	SciaRegs.SCIHBAUD = 0x0000;
	SciaRegs.SCILBAUD = UARTA_BAUD_RATE;
	SciaRegs.SCICCR.bit.LOOPBKENA =0; // Enable loop back
	SciaRegs.SCIFFTX.all=0xC020; // 2011.
    // SciaRegs.SCIFFTX.all=0xC022;        // 2017.09.01

    // SciaRegs.SCIFFRX.all=0xC020;    // 2017.09.01 mal function
    SciaRegs.SCIFFRX.all=0x0021;    // 2017.09.01

    SciaRegs.SCIFFCT.all=0x00;          // 2017.09.01
    SciaRegs.SCIFFTX.bit.TXFFIL = 0;    // irq 15 byte receive
    SciaRegs.SCIFFCT.all=0x00;

    SciaRegs.SCICTL1.all =0x0023;       // Relinquish SCI from Reset
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
    SciaRegs.SCIFFRX.bit.RXFIFORESET=1;

//---
    SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag
	SciaRegs.SCIFFTX.bit.SCIFFENA=1;

	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block 2017.09.03
	PieCtrlRegs.PIEIER9.bit.INTx1=1;     // SCI_RX_INT_A --> PIE Group 9, INT1
	PieCtrlRegs.PIEIER9.bit.INTx2=1;     // SCI_TX_INT_A --> PIE Group 9, INT1
	//PieCtrlRegs.PIEIER9.bit.INTx2=0;     // SCI_TX_INT_A --> PIE Group 9, INT1
	IER |= M_INT9;		// M == 0x0100 scia irq
}

void sciaMonitor()     // need_edit
{
    UNION16 unionRpm,unionIrms,unionPower, unionRePower,unionImPower;
    int i, temp;
    double fTemp;
    char str[50] ={0};

    switch(gMachineState){
        for ( i = 0 ; i < 10 ;i++ ) MonitorMsg[i]=0;
        case STATE_POWER_ON:    strncpy(MonitorMsg,"[POWON]",7); break;
        case STATE_READY:       strncpy(MonitorMsg,"[READY]",7); break;
        case STATE_RUN:         strncpy(MonitorMsg,"[RUN  ]",7); break;
        case STATE_INIT_RUN:    strncpy(MonitorMsg,"[INIT ]",7); break;
        case STATE_GO_STOP:     strncpy(MonitorMsg,"[GSTOP]",7); break;
        case STATE_TRIP:
            strncpy(MonitorMsg,"[TRIP ]",7);
            break;
        default:  strncpy(MonitorMsg,"[SYERR]",7); break;
    }

    if(gMachineState == STATE_TRIP){
        snprintf( str,20,"TripCode=%03d : ",TripInfoNow.CODE);
        load_scia_tx_mail_box(str);
        load_scia_tx_mail_box(TripInfoNow.MSG);

        fTemp = TripInfoNow.RPM;
        temp = (int)(floor(fTemp + 0.5));
        snprintf( str,30," : TripRpm= %4d :",temp);
        load_scia_tx_mail_box(str);

        temp = (int)(floor(TripInfoNow.VDC +0.5));
        snprintf( str,30,"tripVDC=%4d : ",temp);
        load_scia_tx_mail_box(str);

        fTemp = TripInfoNow.CURRENT;
        temp = (int)(floor(fTemp*10 +0.5));
        snprintf( str,30,"tripI = %3d.%1dA : ",(temp/10),temp%10);
        load_scia_tx_mail_box(str);

        temp = (int)(floor(TripInfoNow.DATA +0.5));
        snprintf( str,30,"tripData=%4d \r\n",temp);
        load_scia_tx_mail_box(str);
        // free(TripData);
        return;
    }

    strncpy( str,"9:4:900:0.000e+0:",17); load_scia_tx_mail_box(str);
    load_scia_tx_mail_box(MonitorMsg);

    fTemp = ( rpm < -6000.0 ) ? -6000.0 : rpm;
    fTemp = ( fTemp > 6000.0 ) ? 6000.0 : fTemp;
    unionRpm.INTEGER    = (int)( fTemp * INV_RPM_SCALE * 204.8) + 2048;

    fTemp = ( rpm < 0.0 ) ? 0.0 : Is_mag_rms;
    fTemp = ( fTemp > 500.0 ) ? 500.0 : fTemp;
    unionIrms.INTEGER    = (int)( fTemp * INV_I_SCALE * 204.8) + 2048;

    //unionPower.INTEGER  = (int)( P_total * INV_P_SCALE * 204.8) + 2048;
    unionPower.INTEGER  = (int)( 0.0 * INV_P_SCALE * 204.8) + 2048;

    fTemp = ( reference_out < -3.0 ) ? -3.0 : reference_out;
    fTemp = ( fTemp > 3.0 ) ? 3.0 : fTemp;
    unionRePower.INTEGER  = (int)( fTemp * INV_REF_SCALE * 204.8) + 2048;

    fTemp = ( Vdc < 0.0 ) ? 0.0 : Vdc;
    fTemp = ( fTemp > 800.0 ) ? 800.0 : fTemp;
    unionImPower.INTEGER  = (int)( fTemp * INV_V_SCALE * 204.8) + 2048;

    i = 0;
    str[ i*3 + 0] = (( unionRpm.byte.MSB     ) & 0x0f) | 0x40  ;
    str[ i*3 + 1] = (( unionRpm.byte.LSB >> 4) & 0x0f) | 0x40 ;
    str[ i*3 + 2] = (( unionRpm.byte.LSB     ) & 0x0f) | 0x40;

    i = 1;
    str[ i*3 + 0] = (( unionIrms.byte.MSB     ) & 0x0f) | 0x40;
    str[ i*3 + 1] = (( unionIrms.byte.LSB >> 4) & 0x0f) | 0x40;
    str[ i*3 + 2] = (( unionIrms.byte.LSB     ) & 0x0f) | 0x40;

    i = 2;
    str[ i*3 + 0] = (( unionPower.byte.MSB     ) & 0x0f) | 0x40 ;
    str[ i*3 + 1] = (( unionPower.byte.LSB >> 4) & 0x0f) | 0x40;
    str[ i*3 + 2] = (( unionPower.byte.LSB     ) & 0x0f) | 0x40;

    i = 3;
    str[ i*3 + 0] = (( unionRePower.byte.MSB     ) & 0x0f) | 0x40 ;
    str[ i*3 + 1] = (( unionRePower.byte.LSB >> 4) & 0x0f) | 0x40;
    str[ i*3 + 2] = (( unionRePower.byte.LSB     ) & 0x0f) | 0x40 ;

    i = 4;
    str[ i*3 + 0] = (( unionImPower.byte.MSB     ) & 0x0f) | 0x40 ;
    str[ i*3 + 1] = (( unionImPower.byte.LSB >> 4) & 0x0f) | 0x40;
    str[ i*3 + 2] = (( unionImPower.byte.LSB     ) & 0x0f) | 0x40;

    str[ i*3 + 3 ] = '\r';
    str[ i*3 + 4 ] = '\n';
    str[ i*3 + 5 ] = 0;
    load_scia_tx_mail_box(str);
}

void loadSciaTxMailBox_bk( char * st)
{
    int i;
    char * str;
    str = st;
    i =0;
//    SciaRegs.SCIFFTX.bit.TXFFIENA = 0;  // Clear SCI Interrupt flag
    while( (i < 20 ) && ( !(* str))){
        scia_tx_msg_box[scia_tx_end_addr ++] = *str ++;
        i++;
    }
    Nop();
//    SciaRegs.SCIFFTX.bit.TXFFIENA = 1;  // Clear SCI Interrupt flag
}

int load_scia_tx_mail_box_char( char msg)
{
    if( msg == 0 ) return -1;

    scia_tx_msg_box[scia_tx_end_addr] = msg;

    if(scia_tx_end_addr < ( SCIA_TX_BUF_MAX-1)) scia_tx_end_addr ++;
    else                                        scia_tx_end_addr = 0;

    if(scia_tx_end_addr == scia_tx_start_addr){
        if(scia_tx_end_addr < (SCIA_TX_BUF_MAX-1)) scia_tx_start_addr++;
        else                                        scia_tx_start_addr = 0;
    }
    return 0;
}

void loadSciaTxMailBox( char * st)
{
    int loop_count;
    char * str;
    str = st;
    SciaRegs.SCIFFTX.bit.TXFFIENA = 0;  // Clear SCI Interrupt flag
    loop_count = 0;
     while((*str != 0) && ( loop_count < 20)) {
         load_scia_tx_mail_box_char(*str++);
         loop_count ++;
     }
    SciaRegs.SCIFFTX.bit.TXFFIENA = 1;  // Clear SCI Interrupt flag
}

void load_scia_tx_mail_box( char * st)
{
    int loop_count;
    char * str;
    str = st;
    SciaRegs.SCIFFTX.bit.TXFFIENA = 0;  // Clear SCI Interrupt flag
    loop_count = 0;
     while(( * str != 0) && ( loop_count < 40)) {
         load_scia_tx_mail_box_char(*str++);
         loop_count ++;
     }
    SciaRegs.SCIFFTX.bit.TXFFIENA = 1;  // Clear SCI Interrupt flag
}

// channel 100,101,102,103
// 157msec
void loadSciaTxBufAdc(int channel )
{
    int i,j;
    char str[40]={0};


    scia_tx_start_addr =0;
    scia_tx_end_addr =0;
    delay_msecs(10);           // 157msec

    sendAdcDataFlag = 1;    // data update blocking

    for( j = 0; j < 4 ; j++){
        strncpy( str,"9:4:900:1.000e+2:",17); load_scia_tx_mail_box(str);
        strncpy(str,"ch0:",4);
        str[2] += (j+1);
        str[4] = 0;
        load_scia_tx_mail_box(str);

        for( i = 0 ; i < SCOPE_MAX_NUMBER ; i++){
            //scopeData[j][i].INTEGER = 1000 * ( j + 1);
            str[0] = (( scopeData[j][i].byte.MSB     ) & 0x0f) | 0x40 ;
            str[1] = (( scopeData[j][i].byte.LSB >> 4) & 0x0f) | 0x40;
            str[2] = (( scopeData[j][i].byte.LSB     ) & 0x0f) | 0x40;
            str[3] = 0;
            load_scia_tx_mail_box(str);
            // for ( k = 0 ; k < 3000 ; k ++ ) Nop();
            //delay_msecs(1);           // 157msec
        }
        strncpy(str,"ch0\r\n",5);
         str[2] += (j+1);
        str[5] = 0;
        load_scia_tx_mail_box(str);
        delay_msecs(200);           // 157msec
    }
    sendAdcDataFlag = 0;
}

interrupt void sciaTxFifoIsr(void)
{
    Uint16 i=0;
    static int irqTxCount = 0;

    while( scia_tx_end_addr != scia_tx_start_addr){
 		SciaRegs.SCITXBUF = scia_tx_msg_box[scia_tx_start_addr];
		if(scia_tx_start_addr <  ( SCIA_TX_BUF_MAX - 1) )   scia_tx_start_addr ++;
		else									            scia_tx_start_addr =0;

		irqTxCount ++;

        if( ( irqTxCount >= SCIA_TX_BUF_MAX ) || (scia_tx_end_addr == scia_tx_start_addr)) {
            irqTxCount = 0;
            scia_tx_end_addr = scia_tx_start_addr = 0;
            SciaRegs.SCIFFTX.bit.TXFFIENA = 0;           // Clear SCI Interrupt flagbreak;
            break;
        }
		i++;
		if( i > 3 ) break;
	}
	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;	// Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x0100;     // IN9 
}

interrupt void sciaRxFifoIsr(void)
{

    static Uint32 modebus_start_time=0;
    static int scia_rx_count=0;
    Nop();

    if( ulGetTime_mSec(modebus_start_time) > 10 ){
        modebus_start_time = ulGetNow_mSec( );
        msg_box[0] = SciaRegs.SCIRXBUF.all;  // Read data
        scia_rx_count = 0;
        scia_rx_count++;
    }
    else if( scia_rx_count < 15 ){
        msg_box[scia_rx_count] = SciaRegs.SCIRXBUF.all;  // Read data
        scia_rx_count++;
    }
    else if( scia_rx_count == 15 ){
        msg_box[15] = SciaRegs.SCIRXBUF.all;     // Read data
        scia_rx_count = 0;
        scia_rx_msg_flag =1;
    }
    else{
        msg_box[0] = SciaRegs.SCIRXBUF.all;  // Read data
        scia_rx_count++;
    }
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=0x0100;     // IN9
}

// read data format   "9:4:123:x.xxxe-x"
// write data format  "9:6:123:1.234e-3"
void scia_cmd_proc( int * sci_cmd, double * sci_ref)
{
    static unsigned long sciChkCount,sciOffTimeMsec;

    double data,dbtemp;
    int addr,check,temp;
    char str[30]={0};

    TRIP_INFO * TripData;

    * sci_cmd = CMD_NULL;
    * sci_ref = 0.0;
	 
	* sci_cmd = CMD_NULL;
	* sci_ref = 0.0;

	if( scia_rx_msg_flag == 0) {

	    sciOffTimeMsec = ulGetTime_mSec( sciChkCount);
	    if(sciOffTimeMsec > 2000 ) {
	        scia_fifo_init();
	        sciChkCount = ulGetNow_mSec( );
	    }
	    return;
	}

	sciChkCount = ulGetNow_mSec( );
	scia_rx_msg_flag = 0;

    strncpy( scia_rx_msg_box,msg_box,16);

    if (( scia_rx_msg_box[0] != '9') && ( scia_rx_msg_box[1] != ':')) return;

    addr =  (scia_rx_msg_box[4]- '0')* 100 +(scia_rx_msg_box[5]- '0')*10 + (scia_rx_msg_box[6]- '0');

    scia_rx_msg_box[16]=0;
    data =  atof( & scia_rx_msg_box[8]);
    Nop();
    if( scia_rx_msg_box[2] == '6'){
         if( addr == 900 ){
             check = (int)data;
             if(check == 10){
                 * sci_cmd = CMD_START;
                 * sci_ref = 0.1;           //code_btn_start_ref;
                 load_scia_tx_mail_box("UART CMD_START");
             }
             else if( check == 20 ){
                 * sci_cmd = CMD_STOP;  * sci_ref = 0.0;
                 load_scia_tx_mail_box("UART CMD_STOP");
             }
             else if( check == 30 ){
                 * sci_cmd = CMD_RESET;  * sci_ref = 0.0;
                 load_scia_tx_mail_box("UART CMD_RESET");
             }
             else if( data == 40 ){
                 * sci_cmd = CMD_SAVE;  * sci_ref = 0.0;
                 load_scia_tx_mail_box("UART CMD_SAVE");
             }
/*             else if( data == 50 ){
                   * sci_cmd = CMD_READ_ALL;  * sci_ref = 0.0;
                   load_scia_tx_mail_box("UART CMD_READ_ALL");
            }
 */           else if( data == 80 ){
                   * sci_cmd = CMD_NULL;  * sci_ref = 0.0;
//                   get_adc_offset();
            }
            else if( data == 90 ){
                   * sci_cmd = CMD_NULL;  * sci_ref = 0.0;
                   load_scia_tx_mail_box("EEPROM init Start");
                   check = init_eprom_data();      // 0�씠 �븘�땲硫� address value
                   if( check != 0) load_scia_tx_mail_box("EEPROM init Fail");
                   else        load_scia_tx_mail_box("EEPROM init OK \r\n");
            }
            else{
                 load_scia_tx_mail_box("Illegal CMD data");
            }
         }
         else{
             // registor_write_proc(addr,data);
             check = SaveDataProc(addr, data);
             Nop();
         }
     }
//---   read routine
     else if(scia_rx_msg_box[2] == '4'){
         if(addr == 900){    //  monitor state
             check = (int)data;
             if( check >= 100 ){
                 sendAdcDataFlag = 1;
                 loadSciaTxBufAdc(check);
                 sendAdcDataFlag = 0;
                 }
             else {
                 sciaMonitor();
                 Nop();
             }
             return;
         }
         else if(addr == 901){    //  monitor state
             check = (int)data;
             if(check==0){
                 /* sci_cmd = CMD_READ_ALL;  * sci_ref = 0.0; */
                 readAllCodes();
             }
             return;
         }
         else if(addr == 902){   // read inverter status
             check = (int)data;
             switch( check ){
             case 5 : // Reset;
                if( ( gMachineState == STATE_READY)|| ( gMachineState == STATE_TRIP)){
                    fault_reset();
                }
                 break;
             default:
                 break;
             }
             return;
         }
         else if(addr == 903){   //  EEPROM TRIP DATA
             check = (int)data;
             if( data == 0 ){
                 TripData = (TRIP_INFO*)malloc(sizeof(TRIP_INFO));
                 snprintf( str,20,"\nTripCODE: %03d \t",TripInfoNow.CODE);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 load_scia_tx_mail_box(TripInfoNow.MSG); delay_msecs(220);

                 dbtemp = TripInfoNow.RPM;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,13,"\nFq=%3d[hz]",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.VDC;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,13,"\tVDC =%4d",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.CURRENT;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,13,"\tI1  =%4d ",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.DATA;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,13," \tDATA=%4d\n",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);
                 free(TripData);
                 return;
             }
             else{
                 TripData = (TRIP_INFO*)malloc(sizeof(TRIP_INFO));
                GetTripInfo(check + 1,TripData);
                 strncpy(gStr1,TripInfoNow.MSG,20);

                 snprintf( str,4,"%03d:",TripData->CODE);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 load_scia_tx_mail_box(TripData->MSG); delay_msecs(220);

                 dbtemp = TripData->RPM;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10,"Fq=%3d[hz]",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripData->VDC;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10," VDC =%4d",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripData->CURRENT;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10,"I1  =%4d ",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripData->DATA;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10," DATA=%4d",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);
                 free(TripData);
             }
             return;
         }
         else if(addr == 905){   // RUN & STOP
             check = (int)data;

             switch( check ){
             case 0:
                 * sci_cmd = CMD_START;
                 // * sci_ref = code_btn_start_ref;
                 break;
             case 1:
                 * sci_cmd = CMD_STOP;
                 * sci_ref = 0.0;
                 break;
             case 2:
                 * sci_cmd = CMD_SPEED_UP;
                 break;
             case 3:
                 * sci_cmd = CMD_SPEED_DOWN;
                 break;
             case 4:
                 * sci_cmd = CMD_SPEED_UP1;
                 break;
             default:
                 * sci_cmd = CMD_NULL;
                 break;
             }
             return;
         }
         else if (addr == 909 ){
                 temp = (int) rpm;
              snprintf( str,20,"Rpm = %4d : ",temp); load_scia_tx_mail_box(str);
              snprintf( str,30,"Irms = %.3e : ",Is_mag_rms); load_scia_tx_mail_box(str);
              snprintf( str,30,"P_total = %.1e : ",P_total); load_scia_tx_mail_box(str);
              snprintf( str,30,"Vdc = %.1e : ",Vdc); load_scia_tx_mail_box(str);
              load_scia_tx_mail_box(" \r\n");
              delay_msecs(10);
              return;
          }
         else if (addr == 910 ){ // read adc
              snprintf( str,20,"Ia = %4d : ",adcIa); load_scia_tx_mail_box(str);
              snprintf( str,20,"Ib = %4d : ",adcIb); load_scia_tx_mail_box(str);
              snprintf( str,20,"Vdc= %4d : ",adcVdc); load_scia_tx_mail_box(str);
              snprintf( str,20,"Tmp= %4d : ",adc_result[3]); load_scia_tx_mail_box(str);
              snprintf( str,20,"Sen= %4d : ",adc_result[4]); load_scia_tx_mail_box(str);
              snprintf( str,20,"Cmd= %4d : ",adc_result[5]); load_scia_tx_mail_box(str);
              load_scia_tx_mail_box(" \r\n");
              delay_msecs(10);
              return;
          }
// read code proc
         check = get_code_information( addr, CMD_READ_DATA , & code_inform);
         if(check != 0 ){
             snprintf( str,10,"CODE=%4d:",addr); load_scia_tx_mail_box(str);
             load_scia_tx_mail_box("Error Invalid Address \r\n");delay_msecs(10);
             return;
         }
         snprintf( str,10,"CODE=%4d:",addr); load_scia_tx_mail_box(str);
         snprintf( str,40,"Data=%.3e:",code_inform.code_value);
         load_scia_tx_mail_box(str);
         load_scia_tx_mail_box(code_inform.disp);
         load_scia_tx_mail_box("\r\n");delay_msecs(10);
         return;
     }
 }

//==================================
// End of file.
//==================================

