// keri2021
//###########################################################################
//
// FILE:	digital_inout.h
//
// Project:	keri015Inv F28069  2021-0129 by Soonkil cheoung


#ifndef		__DIGITAL_INOUT_H_
#define		__DIGITAL_INOUT_H_

/*
MC1_ON --> MAIN_OUT -- inverter run
MC2_ON --> RUN_OUT  --- direct run
MC4_ON --> TRIP_OUT --- on state


*/
// Set Output High
#define LED1_CLEAR        (GpioDataRegs.GPBCLEAR.bit.GPIO54 = 1)
#define LED1_SET          (GpioDataRegs.GPBSET.bit.GPIO54   = 1)

#define LED2_CLEAR        (GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1)
#define LED2_SET          (GpioDataRegs.GPBSET.bit.GPIO55   = 1)

#define RUN_OUT_ON          (GpioDataRegs.GPASET.bit.GPIO8 = 1)
#define RUN_OUT_OFF         (GpioDataRegs.GPACLEAR.bit.GPIO8 = 1)

#define MAIN_CHARGE_OFF     (GpioDataRegs.GPACLEAR.bit.GPIO10 = 1)
#define MAIN_CHARGE_ON      (GpioDataRegs.GPASET.bit.GPIO10   = 1)

// G-init charge
#define G_INIT_SET        (GpioDataRegs.GPASET.bit.GPIO11 = 1)
#define G_INIT_CLEAR       (GpioDataRegs.GPACLEAR.bit.GPIO11 = 1)

#define TRIP_OUT_ON         (GpioDataRegs.GPASET.bit.GPIO12 = 1)    // relayTripOut
#define TRIP_OUT_OFF        (GpioDataRegs.GPACLEAR.bit.GPIO12 = 1)  // relayTripOut

//--- y-delta MC control
#define MC1_ON              MAIN_CHARGE_ON
#define MC1_OFF             MAIN_CHARGE_OFF
#define MC2_ON              TRIP_OUT_ON
#define MC2_OFF             TRIP_OUT_OFF
#define MC4_ON              RUN_OUT_ON
#define MC4_OFF             RUN_OUT_OFF

#define MAIN_CHARGE_OFF     (GpioDataRegs.GPACLEAR.bit.GPIO10 = 1)
#define MAIN_CHARGE_ON      (GpioDataRegs.GPASET.bit.GPIO10   = 1)

// G-init charge
#define G_INIT_SET        (GpioDataRegs.GPASET.bit.GPIO11 = 1)
#define G_INIT_CLEAR       (GpioDataRegs.GPACLEAR.bit.GPIO11 = 1)

#define TRIP_OUT_ON         (GpioDataRegs.GPASET.bit.GPIO12 = 1)    // relayTripOut
#define TRIP_OUT_OFF        (GpioDataRegs.GPACLEAR.bit.GPIO12 = 1)  // relayTripOut




#define digital_out0_on()	(GpioDataRegs.GPASET.bit.GPIO13 = 1)	// relayOutAux1
#define digital_out0_off()	(GpioDataRegs.GPACLEAR.bit.GPIO13 = 1)	// relayOutAux1

#define GATE_DRIVER_ENABLE  (GpioDataRegs.GPASET.bit.GPIO7 = 1)
#define GATE_DRIVER_CLEAR   (GpioDataRegs.GPACLEAR.bit.GPIO7= 1)

#define BACKUP_ENABLE       (GpioDataRegs.GPACLEAR.bit.GPIO17 = 1)
#define BACKUP_DISABLE      (GpioDataRegs.GPASET.bit.GPIO17   = 1)

// 2017.09.01--2011.06.25
#define EX_DIO_INPUT1       GpioDataRegs.GPADAT.bit.GPIO14    // dsp pcb CON4-3 trip input
// #define EX_TRIP_INPUT       GpioDataRegs.GPADAT.bit.GPIO15    // dsp pcb CON4-3
#define EX_DIO_INPUT2       GpioDataRegs.GPADAT.bit.GPIO15    // dsp pcb CON4-4
#define START_INPUT         GpioDataRegs.GPADAT.bit.GPIO12    // exInput1
#define RUN_INPUT           (START_INPUT)                     // run input

#define GATE_DRIVER_FAULT   (GpioDataRegs.GPADAT.bit.GPIO16)    // gateDriverFault
// #define DB_FAULT     (GpioDataRegs.GPADAT.bit.GPIO17)

struct DIGIT_FUNCTION_BITS {      
	Uint16 DRIVE_ENABLE:1;      // 
	Uint16 MULTI_STEP_BIT0:1;	// 
	Uint16 MULTI_STEP_BIT1:1;	// 
	Uint16 MULTI_STEP_BIT2:1;	// 
	Uint16 MULTI_STEP_BIT3:1;	// 
	Uint16 FAULT_RESET:1;		// 
	Uint16 JOG:1;				//
	Uint16 AI_REF_ACTIVE:1;		//
	Uint16 AI_LOCAL_REMOTE:1;	//
	Uint16 EXT_FAULT_A:1;		//
	Uint16 EXT_FAULT_B:1;		//
	Uint16 MOTOR_SELECT:1;		//
	Uint16 MB_BRAKE_STATE:1;	//
	Uint16 ACCEL_DECEL_SWITCH:1;	//
	Uint16 REF_TUNING_INC:1;	//
	Uint16 REF_TUNING_DEC:1;	//
	Uint16 ACC_DEC_BYP:1;		//
	Uint16 PID_CNTL_ENABLE:1;	//
	Uint16 AUTO_PID_MODE:1;		//
	Uint16 PID_GAIN_SEL:1;		//
	Uint16 PID_I_RESET:1;		//
	Uint16 TRQ_REF_OPT_BYP:1;	//
	Uint16 TRQ_SIGN:1;			//
	Uint16 TRQ_OUT_ZERO:1;		//
	Uint16 TIMER_RUN_ENABLE:1;	//
	Uint16 SLAVE_RUN_STATUS:1;	//
	Uint16 SYNC_CTRL_OPT_BPY:1;	//
	Uint16 FLYING_START:1;		//
	Uint16 DISABLE_PROFIBUS:1;	//
	Uint16 INVERT_DIR:1;		//
	Uint16 INVERT_RUN:1;		//
};

struct DIGITAL_OUT_BITS{
	Uint16 DRIVE_READY:1;	// driver ready
	Uint16 FAULT_OUT_A:1;
	Uint16 FAULT_OUT_B:1;
	Uint16 MOTOR_BRAKE:1;
	Uint16 RUN_STOP:1;
	Uint16 WARNING:1;
	Uint16 DIRECTION:1;
	Uint16 JOG_INPUT:1;
	Uint16 VC_LIMIT:1;
	Uint16 FREE:1;
};

union DIGITAL_OUT_FUNC{
	Uint16	all;
	struct DIGITAL_OUT_BITS bit;
};

union DIGITAL_FUNCTION
{
   Uint32               	  all;
   struct DIGIT_FUNCTION_BITS  bit;
} ;

#endif

// End of digital_inout.h
