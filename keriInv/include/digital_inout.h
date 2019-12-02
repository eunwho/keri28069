// FILE:	digital_inout.h
// Project:	dcPower , dcPower G0801
// date     : 2018.0503
#ifndef		__DIGITAL_INOUT_H_
#define		__DIGITAL_INOUT_H_

#define EX_TRIP_INPUT       ( GpioDataRegs.GPADAT.bit.GPIO8 )
#define RUN_INPUT           ( GpioDataRegs.GPADAT.bit.GPIO12 )

#define GATE_DRIVER_SET     (GpioDataRegs.GPASET.bit.GPIO7 = 1)
#define GATE_DRIVER_CLEAR   (GpioDataRegs.GPACLEAR.bit.GPIO7= 1)
#define MAIN_CHARGE_OFF     (GpioDataRegs.GPACLEAR.bit.GPIO10 = 1)
#define MAIN_CHARGE_ON      (GpioDataRegs.GPASET.bit.GPIO10   = 1)
#define TRIP_OUT_ON         (GpioDataRegs.GPASET.bit.GPIO11   = 1)
#define TRIP_OUT_OFF        (GpioDataRegs.GPACLEAR.bit.GPIO11   = 1)

#define BACKUP_ENABLE       (GpioDataRegs.GPACLEAR.bit.GPIO17 = 1)
#define BACKUP_DISABLE      (GpioDataRegs.GPASET.bit.GPIO17   = 1)

#define PWM0_HIGH_FAULT     (GpioDataRegs.GPADAT.bit.GPIO18)    // gateDriverFault
#define PWM0_LOW_FAULT      (GpioDataRegs.GPADAT.bit.GPIO19)    // gateDriverFault
#define PWM1_HIGH_FAULT     (GpioDataRegs.GPADAT.bit.GPIO26)    // gateDriverFault
#define PWM1_LOW_FAULT      (GpioDataRegs.GPADAT.bit.GPIO27)    // gateDriverFault

#endif
//--- End of digital_inout.h
