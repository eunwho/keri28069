#include	<header.h>
#include	<extern.h>
// include <scia,h>

#if	USE_UART_A

#define CPU_FREQ    90E6
#define LSPCLK_FREQ CPU_FREQ/4
// #define SCI_FREQ    115200
#define SCI_FREQ    38400
#define SCI_PRD     (LSPCLK_FREQ/(SCI_FREQ*8))-1

#define UARTA_BAUD_RATE          SCI_PRD     // 115200

int scia_rx_start_addr=0;
int scia_rx_end_addr=0;
int sciRxPoint=0;

int scia_tx_start_addr=0;
int scia_tx_end_addr=0;
int scia_rx_msg_flag = 0;

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

void load_scia_tx_mail_box( char * st)
{
	int i;
	char * str;

	str = st;

	SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag

	for( i = 0 ; i < SCIA_TX_BUF_MAX ; i++){
        if( *str == '\0')  break;
 		scia_tx_msg_box[scia_tx_end_addr ++] = *str ++;
 		if(scia_tx_end_addr >= SCIA_TX_BUF_MAX ) scia_tx_end_addr = 0;
		if(scia_tx_end_addr == scia_tx_start_addr){
		    scia_tx_start_addr++;
			if(scia_tx_start_addr >= (SCIA_TX_BUF_MAX-1)) scia_tx_start_addr = 0;
		}
	}
	SciaRegs.SCIFFTX.bit.TXFFIENA = 1;	// Clear SCI Interrupt flag
}
		
interrupt void sciaTxFifoIsr(void)
{
    Uint16 i=0;

	while( scia_tx_end_addr != scia_tx_start_addr){

 		SciaRegs.SCITXBUF = scia_tx_msg_box[scia_tx_start_addr];

		if(scia_tx_start_addr < ( SCIA_TX_BUF_MAX-1)) scia_tx_start_addr ++;
		else											scia_tx_start_addr=0;

		if(scia_tx_end_addr == scia_tx_start_addr) break;

		i++;
		if( i > 3 ) break;
	}

	if(scia_tx_end_addr == scia_tx_start_addr) SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag

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
	double data,dbtemp;
    int addr,check,temp;
    char str[41]={0};

    TRIP_INFO * TripData;

    * sci_cmd = CMD_NULL;
    * sci_ref = 0.0;
	 
	* sci_cmd = CMD_NULL;
	* sci_ref = 0.0;

//	if( scia_rx_msg_flag == 0) return;

//	scia_rx_msg_flag = 0;

    strncpy( scia_rx_msg_box,msg_box,16);

    if (( scia_rx_msg_box[0] != '9') && ( scia_rx_msg_box[1] != ':')) return;

    addr =  (scia_rx_msg_box[4]- '0')* 100 +(scia_rx_msg_box[5]- '0')*10 + (scia_rx_msg_box[6]- '0');

    scia_rx_msg_box[16]=0;
    data =  atof( & scia_rx_msg_box[8]);

    if( scia_rx_msg_box[2] == '6'){
         if( addr == 900 ){
             check = (int)data;
             if(check == 10){
                 * sci_cmd = CMD_START;
                 * sci_ref = 0.1;           //code_btn_start_ref;
                 load_scia_tx_mail_box("\x02UART CMD_START\x03\r\n");
             }
             else if( check == 20 ){
                 * sci_cmd = CMD_STOP;  * sci_ref = 0.0;
                 load_scia_tx_mail_box("\x02UART CMD_STOP\x03\r\n");
             }
             else if( check == 30 ){
                 * sci_cmd = CMD_RESET;  * sci_ref = 0.0;
                 load_scia_tx_mail_box("\x02UART CMD_RESET\x03\r\n");
             }
             else if( data == 40 ){
                 * sci_cmd = CMD_SAVE;  * sci_ref = 0.0;
                 load_scia_tx_mail_box("\x02UART CMD_SAVE\x03\r\n");
             }
             else if( data == 50 ){
                   * sci_cmd = CMD_READ_ALL;  * sci_ref = 0.0;
                   load_scia_tx_mail_box("\x02UART CMD_READ_ALL\0x03\r\n");
            }
            else if( data == 80 ){
                   * sci_cmd = CMD_NULL;  * sci_ref = 0.0;
                   get_adc_offset();
            }
            else if( data == 90 ){
                   * sci_cmd = CMD_NULL;  * sci_ref = 0.0;
                   load_scia_tx_mail_box("\x02 EEPROM init Start\x03\r\n");
                   check = init_eprom_data();      // 0이 아니면 address value
                   if( check != 0) load_scia_tx_mail_box("\0x02 3EEPROM init Fail\x03\r\n");
                   else        load_scia_tx_mail_box("\x02 3EEPROM init OK\x03\r\n");
            }
            else{
                 load_scia_tx_mail_box("\x02 3Illegal CMD data\x03\r\n");
            }
         }
         else{
             // registor_write_proc(addr,data);
             check = SaveDataProc(addr, data);
             Nop();
         }
     }

 //==================
 //   read routine
 //====================
     else if(scia_rx_msg_box[2] == '4'){
         if(addr == 900){    //  monitor state
             check = (int)data;
             monitor_proc();
             load_scia_tx_mail_box(monitOut1); delay_msecs(10);
             load_scia_tx_mail_box(monitOut2); delay_msecs(10);
             load_scia_tx_mail_box(monitOut3); delay_msecs(10);
             load_scia_tx_mail_box(monitOut4); delay_msecs(10);
             Nop();
             return;
         }
         else if(addr == 901){    //  monitor state
             check = (int)data;
             if(check==0){
                 readAllCodes();
                 load_scia_tx_mail_box("\x02ok! read code all\x03\r\n");
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
                 snprintf( str,4,"%03d:",TripInfoNow.CODE);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 load_scia_tx_mail_box(TripInfoNow.MSG); delay_msecs(220);

                 dbtemp = TripInfoNow.VOUT;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,20,"Vo=%3d[A]",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.VDC;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,20," VDC =%4d",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.CURRENT;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10,"I1  =%4d ",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.DATA;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10," DATA=%4d",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);
             }
             else{

                TripData = (TRIP_INFO*)malloc(sizeof(TRIP_INFO));
                GetTripInfo(check + 1,TripData);

                 strncpy(gStr1,TripInfoNow.MSG,20);

                 snprintf( str,4,"%03d:",TripData->CODE);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 load_scia_tx_mail_box(TripData->MSG); delay_msecs(220);

                 dbtemp = TripData->VOUT;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10,"Vo=%3d[A]",temp);
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
             case 0: * sci_cmd = CMD_START; break;
             case 1: * sci_cmd = CMD_STOP;      * sci_ref = 0.0; break;
             case 2: * sci_cmd = CMD_SPEED_UP;   break;
             case 3: * sci_cmd = CMD_SPEED_DOWN; break;
             default: * sci_cmd = CMD_NULL; break;
             }
             return;
         }
         else if ( addr == 980){
             sprintf( str,"\x02 2Iout=%04d :Ipri:%04d \x03\r\n",adc_result[0],adc_result[1]);
             load_scia_tx_mail_box(str); delay_msecs(100);
             sprintf( str,"\x02 3Vdc =%04d :Vout:%04d \x03\r\n",adc_result[2],adc_result[3]);
             load_scia_tx_mail_box(str); delay_msecs(100);
             return;
         }

         check = get_code_information( addr, CMD_READ_DATA , & code_inform);
         if( check == 0 ){
             sprintf( str,"\x02 1%s \x03\r\n",code_inform.disp);
             load_scia_tx_mail_box(str); delay_msecs(10);
             sprintf( str,"\x02 2CODE=%3d \x03\r\n",addr);
             load_scia_tx_mail_box(str); delay_msecs(10);
             sprintf( str,"\x02 3DATA=%.3e \x03\r\n",code_inform.code_value);
             load_scia_tx_mail_box(str); delay_msecs(10);
         } else{
             load_scia_tx_mail_box("\x02Error Invalid Address\x03\r\n");delay_msecs(10);
         }
         return;
     }
 }
#endif

//==================================
// End of file.
//==================================

