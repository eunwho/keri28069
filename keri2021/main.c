// main.c 2018.0613
// powerPack

#define DELAY   50000L
#include	"header.h"
#include	"extern.h"
#include	"global.h"

#pragma CODE_SECTION(MainPWM, "ramfuncs");
#pragma CODE_SECTION(adcIsr, "ramfuncs");
#pragma CODE_SECTION(lpf2nd, "ramfuncs");
//#pragma CODE_SECTION(fieldWeakenVoltageLoopCtrl, "ramfuncs");
#pragma CODE_SECTION(SpaceVectorModulation, "ramfuncs");
#pragma CODE_SECTION(VoltageEstimation, "ramfuncs");
#pragma CODE_SECTION(MotorControlProc, "ramfuncs");
#pragma CODE_SECTION( CheckIGBTFault, "ramfuncs");
#pragma CODE_SECTION( CheckOverCurrent, "ramfuncs");

//#pragma CODE_SECTION( trip_recording, "ramfuncs");
//#pragma CODE_SECTION(Adc_Isr, "ramfuncs");
//#pragma CODE_SECTION(AD2LPF, "ramfuncs");

#pragma CODE_SECTION(LPF1, "ramfuncs");

extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
Uint16 RamfuncsLoadSize;

void InitWatchDog();

// double Vdc_fnd_data;

double tmpTheta,tmp;

int32 sinV[600];
int32 cosV[600];
double test,SinT,CosT;
int i;
void main( void )
{
    int trip_code,cmd;
	double ref_in0;

	InitSysCtrl();
	InitGpio( );

	GATE_DRIVER_ENABLE;
	G_INIT_CLEAR;

    MAIN_CHARGE_OFF; TRIP_OUT_OFF; RUN_OUT_OFF;

	init_charge_flag = 0;
	DINT;
	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);

	InitFlash(); InitPieCtrl();
	IER = 0x0000;   IFR = 0x0000;
	InitPieVectTable();

	scia_fifo_init();
   // scib_fifo_init();

	I2CA_Init();	// Initalize I2C serial eeprom and Real Time Clock;

	InitCpuTimers();   // For this example, only initialize the Cpu Timers

    ConfigCpuTimer(&CpuTimer0, 90, 250);  // debug 2021.02.01 for SCR trigger
    //ConfigCpuTimer(&CpuTimer0, 90, 50);  // debug 2021.02.01 for SCR trigger
	StartCpuTimer0();

    gfRunTime = 0.0;
    protect_reg.all = gDeChargeFlag = 0;
	gMachineState = STATE_POWER_ON;

	PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // Enable INT 1.1 in the PIE

	EALLOW;  // This is needed to write to EALLOW protected registers
	  	PieVectTable.TINT0 		= &cpu_timer0_isr;
		PieVectTable.WAKEINT 	= &wakeint_isr;
		PieVectTable.EPWM1_INT 	= &MainPWM;

		PieVectTable.ADCINT1	= &adcIsr;
        PieVectTable.SCIRXINTA = &sciaRxFifoIsr;
        PieVectTable.SCITXINTA = &sciaTxFifoIsr;

        //PieVectTable.SCIRXINTB = &scibRxFifoIsr;
        //PieVectTable.SCITXINTB = &scibTxFifoIsr;
	    PieVectTable.EQEP1_INT = &eqep1_isr;
       // PieVectTable.XINT1 = &xint1_isr;
  	EDIS;    // This is needed to disable write to EALLOW protected registers

  	InitAdc();
    GATE_DRIVER_CLEAR;

  	EALLOW;
     SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    PieCtrlRegs.PIEIER1.bit.INTx6 = 1; // Enable Adc irq
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1; // Timer0 irq
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // Enable INT 1.1 in the PIE ADCINT1
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1; //
    PieCtrlRegs.PIEIER5.bit.INTx1 = 1; // Enable EQEQ1 INTn in the PIE: Group 5 interrupt 1
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1; // Enable the PIE block

    IER |= M_INT1; // Enable CPU INT1 which is connected to CPU-Timer 0:
    IER |= M_INT3;
    IER |= M_INT5; // Enable CPU INT5 which is connected to EQEP1 INT
	IER |= M_INT8; // scic irq
	IER |= M_INT9; //CAN, SCI_A,SCI_B

    EINT;   // Enable Global interrupt INTM
	ERTM;	// Enable Global realtime interrupt DBGM

    InitWatchDog();
    ADC_SOC_CNF();
    strncpy(MonitorMsg,"POWER_ON",20);
    gPWMTripCode = 0;		//
    Init_EQep( );  // code_encoderPulse;

#if GATE_ACTIVE_LOW
    GATE_DRIVER_ENABLE;             // gate pulse enable
#else
    GATE_DRIVER_ENABLE;
    delay_msecs(5);
    GATE_DRIVER_CLEAR;
#endif

    if( load_code2ram() != 0 ) tripProc();

    commonVariableInit();
	if(HardwareParameterVerification() !=0 ) tripProc();

	lpf2ndCoeffInit( 100.0, Ts, lpfVdcIn, lpfVdcOut, lpfVdcK);
	lpf2ndCoeffInit( codeLpfFreq, Ts, lpfIaIn, lpfIaOut, lpfIrmsK);
    lpf2ndCoeffInit( codeLpfFreq, Ts, lpfIbIn, lpfIbOut, lpfIrmsK);
    lpf2ndCoeffInit( 100.0, Ts, lpfVsIn, lpfVsOut, lpfVsK);
    lpf2ndCoeffInit( 200.0, Ts, lpfIsqIn, lpfIsqOut, lpfIsqK);
    lpf2ndCoeffInit( 50.0, Ts, lpfVsdIn, lpfVsdOut, lpfVsdK);

	IER &= ~M_INT3;      // debug for PWM
	InitEPwm_ACIM_Inverter(); 	// debug
	EPwm1Regs.ETSEL.bit.INTEN = 1;    		            // Enable INT
	IER |= M_INT3;      // debug for PWM

	gfRunTime = 0.0; 
    init_charge_flag = 1;

    ref_in0 = codeRateVolt * 1.4 * 0.68;
    while(( gfRunTime < 10.0) && ( Vdc < ref_in0 )) {
		get_command( & cmd, & ref_in0);
		monitor_proc();
		Nop();
	}

   init_charge_flag=0;
	gMachineState = STATE_READY; 

	if( gPWMTripCode !=0 )	tripProc();
	strncpy(MonitorMsg,"READY",20);delay_msecs(20);
	strncpy(gStr1,"READY \r\n",20);
	load_sci_tx_mail_box(gStr1); delay_msecs(20);
	MAIN_CHARGE_ON;
	for( ; ; )
    {
        if( gPWMTripCode !=0 )  tripProc();
        gPWMTripCode = trip_check();
        if( gPWMTripCode !=0 )  tripProc();
        get_command( & cmd, & ref_in0);
//      analog_out_proc( );
        if(cmd == CMD_READ_ALL ){
            readAllCodes();
        }
        // monitor_proc();
        if(cmd == CMD_START)    // if( cmd == CMD_START )
        {
            trip_code = 0;
            switch( (int)(floor(codeMotorCtrlMode+0.5)) ) // Control Method
            {
            case 0: trip_code = vf_loop_control(ref_in0)        ; break;
            case 9: trip_code = vf_loop_control(ref_in0)        ; break;
            // case 1: trip_code = vf_loop_control(ref_in0)        ; break;        //
//           case 8 : pwm_pulse_test( ); break;
//           case 9 : vf_conv_test(ref_in0); break;
            }
            if( trip_code !=0 ) tripProc();
        }
    }
}

interrupt void wakeint_isr(void)
{
	static int WakeCount = 0; 

	WakeCount++;
	
	// Acknowledge this interrupt to get more from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

void InitWatchDog()
{
	// Enable watch dog
// Write to the whole SCSR register to avoid clearing WDOVERRIDE bit

   EALLOW;
   SysCtrlRegs.SCSR = BIT1;
   EDIS;

// Enable WAKEINT in the PIE: Group 1 interrupt 8
// Enable INT1 which is connected to WAKEINT:
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER1.bit.INTx8 = 1;   // Enable PIE Gropu 1 INT8
   IER |= M_INT1;                       // Enable CPU int1
   EINT;                                // Enable Global Interrupts

   ServiceDog();

   EALLOW;
   SysCtrlRegs.WDCR = 0x0028;   
   EDIS;
}

__interrupt void
xint1_isr(void)
{

   ePwmPortOff( );
   gPWMTripCode = ERR_PWM;
    trip_recording( ERR_PWM, Is_abc[as],"Trip GateDriver");
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//=========================================
// No more.
//=========================================

