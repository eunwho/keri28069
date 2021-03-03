//
// analog.c
// 2019.12.30 by soonkil jung
#include    <header.h>
#include    <extern.h>

void ADC_SOC_CNF( )
{
    extern void DSP28x_usDelay(Uint32 Count);
    EALLOW;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1; // Enable non-overlap mode
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcRegs.INTSEL1N2.bit.INT1E = 1;        // enable ADC interrupt 1
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0; // set ADCInterrupt 1 to auto clr

    AdcRegs.INTSEL1N2.bit.INT1SEL = 1;      // IntChSel causes ADCInterrupt 1

/*
    AdcRegs.ADCSOC0CTL.bit.CHSEL= 0;        // I_u
    AdcRegs.ADCSOC1CTL.bit.CHSEL= 1;        // I_v
    AdcRegs.ADCSOC2CTL.bit.CHSEL= 2;        // Vdc
    AdcRegs.ADCSOC3CTL.bit.CHSEL= 3;        // G-ANA1
    AdcRegs.ADCSOC4CTL.bit.CHSEL= 4;        // pressSensor
    AdcRegs.ADCSOC5CTL.bit.CHSEL= 5;        // analog-cmd
    AdcRegs.ADCSOC6CTL.bit.CHSEL= 6;        // ana-aux1
*/
    AdcRegs.ADCSOC0CTL.bit.CHSEL= 7;        //
    AdcRegs.ADCSOC1CTL.bit.CHSEL= 6;        //
    AdcRegs.ADCSOC2CTL.bit.CHSEL= 5;        //
    AdcRegs.ADCSOC3CTL.bit.CHSEL= 4;        //
    AdcRegs.ADCSOC4CTL.bit.CHSEL= 3;        //
    AdcRegs.ADCSOC5CTL.bit.CHSEL= 2;        //
    AdcRegs.ADCSOC6CTL.bit.CHSEL= 1;        //
    AdcRegs.ADCSOC7CTL.bit.CHSEL= 0;        //

    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC6CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC7CTL.bit.TRIGSEL = 5;

    AdcRegs.ADCSOC0CTL.bit.ACQPS = 9;
    AdcRegs.ADCSOC1CTL.bit.ACQPS = 9;
    AdcRegs.ADCSOC2CTL.bit.ACQPS = 9;
    AdcRegs.ADCSOC3CTL.bit.ACQPS = 9;
    AdcRegs.ADCSOC4CTL.bit.ACQPS = 9;
    AdcRegs.ADCSOC5CTL.bit.ACQPS = 9;
    AdcRegs.ADCSOC6CTL.bit.ACQPS = 9;
    AdcRegs.ADCSOC7CTL.bit.ACQPS = 9;
    EDIS;
}
#define I_RATIO   0.001487      //
interrupt void adcIsr(void)
{
//    DIGIT1_SET;
    double fTemp;
    adc_result[0] = adcCurrentA   = AdcResult.ADCRESULT7;
    adc_result[1] = adcCurrentB   = AdcResult.ADCRESULT6;
    adc_result[2] = adcVdc  = adcVdc = AdcResult.ADCRESULT5;
    adc_result[3] = adcExSensor  = AdcResult.ADCRESULT4;        // G_ANA1
    adc_result[4] = adcIgbtTemperature = AdcResult.ADCRESULT3;        //adcExSensor
    adc_result[5] = adcCmdAnalog = AdcResult.ADCRESULT2;
    adc_result[6] = anaAux1 = AdcResult.ADCRESULT1;

    dAdcIa      = (double)(adcCurrentA);
    dAdcIb      = (double)(adcCurrentB);
    dAdcVdc     = (double)(adcVdc);
    dAdcTemp    = (double)(adcIgbtTemperature);
    dAdcSens    = (double)(adcExSensor);
    dAdcCmd     = (double)(adcCmdAnalog);
    dAdcAux1    = (double)(anaAux1);

    sensVdc = Vdc_factor * adcVdc + Vdc_calc_offset;
    lpfVdcIn[0] = sensVdc;
    lpf2nd( lpfVdcIn, lpfVdcOut, lpfVdcK);

    Vdc = (codeSetVdc > 0.5 ) ? 300.0 : lpfVdcOut[0];

    lpfIaIn[0] = codeISensorValue * ( (double)(adc_result[0]) - codeIaOffset) * I_RATIO * 0.4;
    lpf2nd( lpfIaIn, lpfIaOut, lpfIrmsK);
    Is_abc[as] = ( codeLpfOff > 0.5 ) ? lpfIaIn[0] : lpfIaOut[0];

    lpfIbIn[0] = codeISensorValue * ( (double)(adc_result[1]) - codeIbOffset) * I_RATIO * 0.4;
    lpf2nd( lpfIbIn, lpfIbOut, lpfIrmsK);
    Is_abc[bs] = ( codeLpfOff > 0.5 ) ? lpfIbIn[0] : lpfIbOut[0];

    Is_abc[cs]= -(Is_abc[as]+Is_abc[bs]);

    Is_dq[ds] = Is_abc[as];
    Is_dq[qs] = 0.577350 * Is_abc[as] + 1.15470 * Is_abc[bs];
    Is_mag = sqrt( Is_abc[as] *Is_abc[as] + Is_abc[bs] *Is_abc[bs]);           // �쟾瑜섑겕湲�

    Is_mag_rms = Is_mag;

    fTemp = adc_result[4] * 0.000244 ;
    LPF1(Ts,0.01, fTemp, &exSensRef);            // external sensor

    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

//    DIGIT1_CLEAR;
    return;
}

void analog_out_proc( )
{
}

int check_sensor_trip()
{
    int TripCode;

    Nop();

    if( ( TripCode = CheckOverCurrent()) != 0 ) return TripCode ;   // debug
    if( ( TripCode = CheckOverVolt()   ) != 0 ) return TripCode ;
    if( ( TripCode = CheckUndeVolt()   ) != 0 ) return TripCode ;   // 占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占싼댐옙.
    return 0;
}

// end of file

