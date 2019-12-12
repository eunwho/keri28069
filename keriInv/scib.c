#include	<header.h>
#include	<extern.h>
// include <scia,h>

#define CPU_FREQ    90E6
#define LSPCLK_FREQ CPU_FREQ/4
#define SCI_FREQ    115200
//#define SCI_FREQ    38400
//#define SCI_FREQ    230400
#define SCI_PRD     (LSPCLK_FREQ/(SCI_FREQ*8))-1

#define UARTB_BAUD_RATE          SCI_PRD     // 115200

int scib_rx_start_addr=0;
int scib_rx_end_addr=0;
int scibRxPoint=0;

char msg_boxB[20]={0};
char scibRxIrqBox[SCIB_RX_BUF_MAX] = {0};
char scib_rx_msg_box[SCIB_RX_BUF_MAX] = {0};
char scib_tx_msg_box[SCIB_TX_BUF_MAX] = {0};

void scib_fifo_init()
{
	ScibRegs.SCICCR.all =0x0007;   // 1stopbit,No parity,8 char bits, async mode, idle-line protocol
	ScibRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,Disable RX ERR, SLEEP, TXWAKE
	ScibRegs.SCICTL2.bit.TXINTENA 	=1;	// debug
//	ScibRegs.SCICTL2.bit.RXBKINTENA     =0;
	ScibRegs.SCICTL2.bit.RXBKINTENA     = 1;    // 2017
	ScibRegs.SCIHBAUD = 0x0000;
	ScibRegs.SCILBAUD = UARTB_BAUD_RATE;
	ScibRegs.SCICCR.bit.LOOPBKENA =0; // Enable loop back
	ScibRegs.SCIFFTX.all=0xC020; // 2011.
    // ScibRegs.SCIFFTX.all=0xC022;        // 2017.09.01

    // ScibRegs.SCIFFRX.all=0xC020;    // 2017.09.01 mal function
    ScibRegs.SCIFFRX.all=0x0021;    // 2017.09.01

    ScibRegs.SCIFFCT.all=0x00;          // 2017.09.01
    ScibRegs.SCIFFTX.bit.TXFFIL = 0;    // irq 15 byte receive
    ScibRegs.SCIFFCT.all=0x00;

    ScibRegs.SCICTL1.all =0x0023;       // Relinquish SCI from Reset
    ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;
    ScibRegs.SCIFFRX.bit.RXFIFORESET=1;

//---
    ScibRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag
	ScibRegs.SCIFFTX.bit.SCIFFENA=1;

	ScibRegs.SCIFFTX.bit.TXFFINTCLR=1;

	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block 2017.09.03
	PieCtrlRegs.PIEIER9.bit.INTx3=1;     // SCI_RX_INT_B --> PIE Group 9, INT1
	PieCtrlRegs.PIEIER9.bit.INTx4=1;     // SCI_TX_INT_B --> PIE Group 9, INT1
	IER |= M_INT9;		// M == 0x0100 scia scib irq
}


void scibMonitor()     // need_edit
{
    UNION16 unionRpm,unionIrms,unionPower, unionRePower,unionImPower;
    int i, temp;
    double fTemp;
    char str[50] ={0};

    switch(gMachineState){
        case STATE_POWER_ON:    strncpy(MonitorMsg,"[POWON]",7); break;
        case STATE_READY:       strncpy(MonitorMsg,"[READY]",7); break;
        case STATE_RUN:         strncpy(MonitorMsg,"[RUN  ]",7); break;
        case STATE_INIT_RUN:    strncpy(MonitorMsg,"[INIT ]",7); break;
        case STATE_GO_STOP:     strncpy(MonitorMsg,"[GOSTP]",7); break;
        case STATE_TRIP:
            strncpy(MonitorMsg,"[TRIP ]",7);
            break;
        default:  strncpy(MonitorMsg,"[SYERR]",7); break;
    }

    if(gMachineState == STATE_TRIP){
        snprintf( str,20,"TripCode=%03d : ",TripInfoNow.CODE);
        load_scib_tx_mail_box(str);
        load_scib_tx_mail_box(TripInfoNow.MSG);

        fTemp = TripInfoNow.RPM;
        temp = (int)(floor(fTemp + 0.5));
        snprintf( str,30," : TripRpm= %4d :",temp);
        load_scib_tx_mail_box(str);

        temp = (int)(floor(TripInfoNow.VDC +0.5));
        snprintf( str,30,"tripVDC=%4d : ",temp);
        load_scib_tx_mail_box(str);

        fTemp = TripInfoNow.CURRENT;
        temp = (int)(floor(fTemp*10 +0.5));
        snprintf( str,30,"tripI = %3d.%1dA : ",(temp/10),temp%10);
        load_scib_tx_mail_box(str);

        temp = (int)(floor(TripInfoNow.DATA +0.5));
        snprintf( str,30,"tripData=%4d \r\n",temp);
        load_scib_tx_mail_box(str);
        // free(TripData);
        return;
    }

    strncpy( str,"9:4:900:0.000e+0:",17); load_scib_tx_mail_box(str);
    load_scib_tx_mail_box(MonitorMsg);

    unionRpm.INTEGER    = (int)( rpm * INV_RPM_SCALE * 204.8) + 2048;
    unionIrms.INTEGER   = (int)( Is_mag_rms * INV_I_SCALE * 204.8) + 2048;
    unionPower.INTEGER  = (int)( P_total * INV_P_SCALE * 204.8) + 2048;
    unionRePower.INTEGER  = (int)( Re_Power * INV_P_SCALE * 204.8) + 2048;
    unionImPower.INTEGER  = (int)( Im_Power * INV_P_SCALE * 204.8) + 2048;

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
    load_scib_tx_mail_box(str);
}

void loadScibTxMailBox_bk( char * st)
{
    int i;
    char * str;
    str = st;
    i =0;

    while( (i < 20 ) && ( !(* str))){
        scib_tx_msg_box[scib_tx_end_addr ++] = *str ++;
        i++;
    }
    Nop();
//    ScibRegs.SCIFFTX.bit.TXFFIENA = 1;  // Clear SCI Interrupt flag
}

int load_scib_tx_mail_box_char( char msg)
{
    if( msg == 0 ) return -1;

    scib_tx_msg_box[scib_tx_end_addr] = msg;

    if(scib_tx_end_addr < ( SCIB_TX_BUF_MAX-1)) scib_tx_end_addr ++;
    else                                        scib_tx_end_addr = 0;

    if(scib_tx_end_addr == scib_tx_start_addr){
        if(scib_tx_end_addr < (SCIB_TX_BUF_MAX-1)) scib_tx_start_addr++;
        else                                        scib_tx_start_addr = 0;
    }
    return 0;
}

void loadScibTxMailBox( char * st)
{
    int loop_count;
    char * str;
    str = st;
    ScibRegs.SCIFFTX.bit.TXFFIENA = 0;  // Clear SCI Interrupt flag
    loop_count = 0;
     while((*str != 0) && ( loop_count < 20)) {
         load_scib_tx_mail_box_char(*str++);
         loop_count ++;
     }
    ScibRegs.SCIFFTX.bit.TXFFIENA = 1;  // Clear SCI Interrupt flag
}

void load_scib_tx_mail_box( char * st)
{
    int loop_count;
    char * str;
    str = st;
    ScibRegs.SCIFFTX.bit.TXFFIENA = 0;  // Clear SCI Interrupt flag
    loop_count = 0;
     while(( * str != 0) && ( loop_count < 40)) {
         load_scib_tx_mail_box_char(*str++);
         loop_count ++;
     }
    ScibRegs.SCIFFTX.bit.TXFFIENA = 1;  // Clear SCI Interrupt flag
}

// channel 100,101,102,103
// 157msec
void loadScibTxBufAdc(int channel )
{
    int i,j;
    char str[40]={0};

    scib_tx_start_addr =0;
    scib_tx_end_addr =0;

    sendAdcDataFlag = 1;    // data update blocking

    for( j = 0; j < 4 ; j++){
        strncpy( str,"9:4:900:1.000e+2:",17); load_scib_tx_mail_box(str);
        strncpy(str,"ch0:",4);
        str[2] += (j+1);
        str[4] = 0;
        load_scib_tx_mail_box(str);

        for( i = 0 ; i < 600 ; i++){
            //scopeData[j][i].INTEGER = 1000 * ( j + 1);
            str[0] = (( scopeData[j][i].byte.MSB     ) & 0x0f) | 0x40 ;
            str[1] = (( scopeData[j][i].byte.LSB >> 4) & 0x0f) | 0x40;
            str[2] = (( scopeData[j][i].byte.LSB     ) & 0x0f) | 0x40;
            str[3] = 0;
            load_scib_tx_mail_box(str);
        }
        strncpy(str,"ch0\r\n",5);
        str[2] += (j+1);
        str[5] = 0;
        load_scia_tx_mail_box(str);
        delay_msecs(200);           // 157msec
    }
    sendAdcDataFlag = 0;
}

interrupt void scibTxFifoIsr(void)
{
    Uint16 i=0;
    static int irqTxCount = 0;

    while( scib_tx_end_addr != scib_tx_start_addr){
 		ScibRegs.SCITXBUF = scib_tx_msg_box[scib_tx_start_addr];
		if(scib_tx_start_addr <  ( SCIB_TX_BUF_MAX - 1) )   scib_tx_start_addr ++;
		else									            scib_tx_start_addr =0;

		irqTxCount ++;

        if( ( irqTxCount >= SCIB_TX_BUF_MAX ) || (scib_tx_end_addr == scib_tx_start_addr)) {
            irqTxCount = 0;
            scib_tx_end_addr = scib_tx_start_addr = 0;
            ScibRegs.SCIFFTX.bit.TXFFIENA = 0;           // Clear SCI Interrupt flagbreak;
            break;
        }
		i++;
		if( i > 3 ) break;
	}
	ScibRegs.SCIFFTX.bit.TXFFINTCLR=1;	// Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x0100;     // IN9 
}

interrupt void scibRxFifoIsr(void)
{
    static Uint32 modebus_start_time=0;
    static int scib_rx_count=0;
    Nop();

    if( ulGetTime_mSec(modebus_start_time) > 10 ){
        modebus_start_time = ulGetNow_mSec( );
        msg_boxB[0] = ScibRegs.SCIRXBUF.all;  // Read data
        scib_rx_count = 0;
        scib_rx_count++;
    }
    else if( scib_rx_count < 15 ){
        msg_boxB[scib_rx_count] = ScibRegs.SCIRXBUF.all;  // Read data
        scib_rx_count++;
    }
    else if( scib_rx_count == 15 ){
        msg_boxB[15] = ScibRegs.SCIRXBUF.all;     // Read data
        scib_rx_count = 0;
        scib_rx_msg_flag =1;
    }
    else{
        msg_boxB[0] = ScibRegs.SCIRXBUF.all;  // Read data
        scib_rx_count++;
    }
    ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=0x0100;     // IN9
}

// read data format   "9:4:123:x.xxxe-x"
// write data format  "9:6:123:1.234e-3"
void scib_cmd_proc( int * sci_cmd, double * sci_ref)
{
	double data,dbtemp;
    int addr,check,temp;
    char str[30]={0};

    TRIP_INFO * TripData;

    * sci_cmd = CMD_NULL;
    * sci_ref = 0.0;
	 
	* sci_cmd = CMD_NULL;
	* sci_ref = 0.0;

	if( scib_rx_msg_flag == 0) return;

	scib_rx_msg_flag = 0;

    strncpy( scib_rx_msg_box,msg_boxB,16);

    if (( scib_rx_msg_box[0] != '9') && ( scib_rx_msg_box[1] != ':')) return;

    addr =  (scib_rx_msg_box[4]- '0')* 100 +(scib_rx_msg_box[5]- '0')*10 + (scib_rx_msg_box[6]- '0');

    scib_rx_msg_box[16]=0;
    data =  atof( & scib_rx_msg_box[8]);
    Nop();
    if( scib_rx_msg_box[2] == '6'){
         if( addr == 900 ){
             check = (int)data;
             if(check == 10){
                 * sci_cmd = CMD_START;
                 * sci_ref = 0.1;           //code_btn_start_ref;
                 load_scib_tx_mail_box("UART CMD_START");
             }
             else if( check == 20 ){
                 * sci_cmd = CMD_STOP;  * sci_ref = 0.0;
                 load_scib_tx_mail_box("UART CMD_STOP");
             }
             else if( check == 30 ){
                 * sci_cmd = CMD_RESET;  * sci_ref = 0.0;
                 load_scib_tx_mail_box("UART CMD_RESET");
             }
             else if( data == 40 ){
                 * sci_cmd = CMD_SAVE;  * sci_ref = 0.0;
                 load_scib_tx_mail_box("UART CMD_SAVE");
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
                   load_scib_tx_mail_box("EEPROM init Start");
                   check = init_eprom_data();      // 0�씠 �븘�땲硫� address value
                   if( check != 0) load_scib_tx_mail_box("EEPROM init Fail");
                   else        load_scib_tx_mail_box("EEPROM init OK \r\n");
            }
            else{
                 load_scib_tx_mail_box("Illegal CMD data");
            }
         }
         else{
             // registor_write_proc(addr,data);
             check = SaveDataProc(addr, data);
             Nop();
         }
     }
//---   read routine
     else if(scib_rx_msg_box[2] == '4'){
         if(addr == 900){    //  monitor state
             check = (int)data;
             if( check >= 100 ){
                 sendAdcDataFlag = 1;
                 loadScibTxBufAdc(check);
                 sendAdcDataFlag = 0;
                 }
             else {
                 scibMonitor();
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
                 gMachineState = STATE_POWER_ON;
                 Nop();
                 asm (" .ref _c_int00"); // ;Branch to start of boot.asm in RTS library
                 asm (" LB _c_int00"); // ;Branch to start of boot.asm in RTS library
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
                 load_scib_tx_mail_box(str); delay_msecs(180);

                 load_scib_tx_mail_box(TripInfoNow.MSG); delay_msecs(220);

                 dbtemp = TripInfoNow.RPM;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,13,"\nFq=%3d[hz]",temp);
                 load_scib_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.VDC;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,13,"\tVDC =%4d",temp);
                 load_scib_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.CURRENT;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,13,"\tI1  =%4d ",temp);
                 load_scib_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.DATA;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,13," \tDATA=%4d\n",temp);
                 load_scib_tx_mail_box(str); delay_msecs(180);
                 free(TripData);
                 return;
             }
             else{
                 TripData = (TRIP_INFO*)malloc(sizeof(TRIP_INFO));
                GetTripInfo(check + 1,TripData);
                 strncpy(gStr1,TripInfoNow.MSG,20);

                 snprintf( str,4,"%03d:",TripData->CODE);
                 load_scib_tx_mail_box(str); delay_msecs(180);

                 load_scib_tx_mail_box(TripData->MSG); delay_msecs(220);

                 dbtemp = TripData->RPM;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10,"Fq=%3d[hz]",temp);
                 load_scib_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripData->VDC;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10," VDC =%4d",temp);
                 load_scib_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripData->CURRENT;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10,"I1  =%4d ",temp);
                 load_scib_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripData->DATA;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10," DATA=%4d",temp);
                 load_scib_tx_mail_box(str); delay_msecs(180);
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
             default:
                 * sci_cmd = CMD_NULL;
                 break;
             }
             return;
         }
         else if (addr == 909 ){
                 temp = (int) rpm;
              snprintf( str,20,"Rpm = %4d : ",temp); load_scib_tx_mail_box(str);
              snprintf( str,20,"Irms = %1e : ",Is_mag_rms); load_scib_tx_mail_box(str);
              snprintf( str,20,"P_total = %1e : ",P_total); load_scib_tx_mail_box(str);
              snprintf( str,20,"refer_out = %1e : ",reference_out); load_scib_tx_mail_box(str);
              load_scib_tx_mail_box(" \r\n");
              delay_msecs(10);
              return;
          }
         else if (addr == 910 ){
              snprintf( str,20,"Ia = %4d : ",adc_result[0]); load_scib_tx_mail_box(str);
              snprintf( str,20,"Ib = %4d : ",adc_result[1]); load_scib_tx_mail_box(str);
              snprintf( str,20,"Vdc= %4d : ",adc_result[2]); load_scib_tx_mail_box(str);
              snprintf( str,20,"Tmp= %4d : ",adc_result[3]); load_scib_tx_mail_box(str);
              snprintf( str,20,"Sen= %4d : ",adc_result[4]); load_scib_tx_mail_box(str);
              snprintf( str,20,"Cmd= %4d : ",adc_result[5]); load_scib_tx_mail_box(str);
              load_scib_tx_mail_box(" \r\n");
              delay_msecs(10);
              return;
          }
// read code proc
         check = get_code_information( addr, CMD_READ_DATA , & code_inform);
         if(check != 0 ){
             snprintf( str,10,"CODE=%4d:",addr); load_scib_tx_mail_box(str);
             load_scib_tx_mail_box("Error Invalid Address \r\n");delay_msecs(10);
             return;
         }
         snprintf( str,10,"CODE=%4d:",addr); load_scib_tx_mail_box(str);
         snprintf( str,20,"Data=%.3e:",code_inform.code_value);
         load_scib_tx_mail_box(str);
         load_scib_tx_mail_box(code_inform.disp);
         load_scib_tx_mail_box("\r\n");delay_msecs(10);
         return;
     }
 }

//==================================
// end of scib.c
//==================================

