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

//--- digital out
#define GATE_EN_HIGH            (GpioDataRegs.GPACLEAR.bit.GPIO11 = 1)
#define GATE_EN_LOW             (GpioDataRegs.GPASET.bit.GPIO11 = 1)

#define BACKUP_DISABLE              (GpioDataRegs.GPASET.bit.GPIO17= 1)
#define BACKUP_ENABLE               (GpioDataRegs.GPACLEAR.bit.GPIO17= 1)

//--- digital input
#define START_INPUT             ( GpioDataRegs.GPADAT.bit.GPIO12 ) // INPUT1
#define EX_TRIP_INPUT           ( GpioDataRegs.GPADAT.bit.GPIO13 ) // INPUT2
#define EX_DIO_INPUT1           ( GpioDataRegs.GPADAT.bit.GPIO14 ) // INPUT3
#define EX_DIO_INPUT2           ( GpioDataRegs.GPADAT.bit.GPIO15 ) // INPUT4

#define EMG_STOP                EX_TRIP_INPUT

//--- pwm trip input
#define TRIP_UH                 ( GpioDataRegs.GPADAT.bit.GPIO18 )
#define TRIP_UL                 ( GpioDataRegs.GPADAT.bit.GPIO19 )
#define TRIP_VH                 ( GpioDataRegs.GPADAT.bit.GPIO26 )
#define TRIP_VL                 ( GpioDataRegs.GPADAT.bit.GPIO27 )
#define TRIP_WH                 ( GpioDataRegs.GPADAT.bit.GPIO30 )
#define TRIP_WL                 ( GpioDataRegs.GPADAT.bit.GPIO31 )
#define TRIP_DB                 ( GpioDataRegs.GPBDAT.bit.GPIO34 )


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
