// FILE:	digital_inout.h
// Project:	inv28069 by Soonkil Jung
// Date     : 2019.12.12

#ifndef		__DIGITAL_INOUT_H_
#define		__DIGITAL_INOUT_H_

//--- 3 relay out
#define INIT_CHARGE_OFF         (GpioDataRegs.GPACLEAR.bit.GPIO9 = 1)
#define INIT_CHARGE_ON          (GpioDataRegs.GPASET.bit.GPIO9 = 1)

#define MAIN_CHARGE_OFF         (GpioDataRegs.GPACLEAR.bit.GPIO10 = 1)
#define MAIN_CHARGE_ON          (GpioDataRegs.GPASET.bit.GPIO10 = 1)

#define TRIP_OUT_OFF            (GpioDataRegs.GPACLEAR.bit.GPIO8 = 1)
#define TRIP_OUT_ON             (GpioDataRegs.GPASET.bit.GPIO8 = 1)

//
#define PWM_SIGNAL_OFF          (GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1)
#define PWM_SIGNAL_ON           (GpioDataRegs.GPBSET.bit.GPIO39 = 1)

// old version
#define RUN_OUT_ON          Nop()       // Run out relay
#define RUN_OUT_OFF          Nop()       // Run out relay
#define GATE_DRIVER_SET   Nop()   //
#define GATE_DRIVER_CLEAR   Nop()   //

// v0.0
#define EMG_STOP                             (GpioDataRegs.GPADAT.bit.GPIO10)    // IG2 J1-34 PIN
#define RUN_INPUT                             (GpioDataRegs.GPADAT.bit.GPIO11)    // IG2 J1-34 PIN
//#define EMG_STOP                             (GpioDataRegs.GPBDAT.bit.GPIO53)    // emg stop J1-24 PIN

// 2019.12.02 inv_069
// trip input

#define RUN_STOP_CLEAR              (GpioDataRegs.GPACLEAR.bit.GPIO11   = 1)
#define RUN_STOP_SET                (GpioDataRegs.GPASET.bit.GPIO11     = 1)

#define FAULT_GATE_DRIVER           (GpioDataRegs.GPADAT.bit.GPIO9)    // active high gateDriverFault
#define FAULT_UNDER_VOLT_DRIVER     (GpioDataRegs.GPBDAT.bit.GPIO43)    // active high under volt gate driver
#define FAULT_NTC_TEMP              (GpioDataRegs.GPBDAT.bit.GPIO44)    // fault over temperature


#define BACKUP_DISABLE              (GpioDataRegs.GPASET.bit.GPIO17= 1)
#define BACKUP_ENABLE               (GpioDataRegs.GPACLEAR.bit.GPIO17= 1)

// pilot led
#define LED_GREEN_RUN_SET           Nop()
#define LED_GREEN_RUN_CLEAR         Nop()

// #define LED_GREEN_RUN_SET           (GpioDataRegs.GPBCLEAR.bit.GPIO57= 1)
// #define LED_GREEN_RUN_CLEAR         (GpioDataRegs.GPBSET.bit.GPIO57= 1)

#define LED_RED_FAULT_SET           (GpioDataRegs.GPBCLEAR.bit.GPIO58= 1)
#define LED_RED_FAULT_CLEAR         (GpioDataRegs.GPBSET.bit.GPIO58= 1)

#define LED_RED_CPURUN_CLEAR      (GpioDataRegs.GPBCLEAR.bit.GPIO57= 1)
#define LED_RED_CPURUN_SET        (GpioDataRegs.GPBSET.bit.GPIO57= 1)

#define PERIOD_ADC_IRQ_CLEAR        (GpioDataRegs.GPBCLEAR.bit.GPIO50= 1)
#define PERIOD_ADC_IRQ_SET          (GpioDataRegs.GPBSET.bit.GPIO50= 1)

#define PERIOD_PWM_IRQ_CLEAR        (GpioDataRegs.GPBCLEAR.bit.GPIO52= 1)
#define PERIOD_PWM_IRQ_SET          (GpioDataRegs.GPBSET.bit.GPIO52= 1)

#endif
// End of digital_inout.h
