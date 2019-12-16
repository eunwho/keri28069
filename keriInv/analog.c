//
// file name : analog.c
//          songuo ev by soonkil jung
// date         : 2019.0625

#include	<header.h>
#include	<extern.h>

void ADC_SOC_CNF( )
{
    extern void DSP28x_usDelay(Uint32 Count);

    EALLOW;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1; // Enable non-overlap mode
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcRegs.INTSEL1N2.bit.INT1E = 1;        // enable ADC interrupt 1
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0; // set ADCInterrupt 1 to auto clr

    AdcRegs.INTSEL1N2.bit.INT1SEL = 1;      // IntChSel causes ADCInterrupt 1

    AdcRegs.ADCSOC0CTL.bit.CHSEL    = 0;        // A_UC
    AdcRegs.ADCSOC1CTL.bit.CHSEL    = 1;        // A_VC
    AdcRegs.ADCSOC2CTL.bit.CHSEL    = 2;        // EX_A2
    AdcRegs.ADCSOC3CTL.bit.CHSEL    = 3;        // EX_A3
    AdcRegs.ADCSOC4CTL.bit.CHSEL    = 4;        // EX_A4
    AdcRegs.ADCSOC5CTL.bit.CHSEL    = 5;        // EX_A5
    AdcRegs.ADCSOC6CTL.bit.CHSEL    = 6;        // EX_A6
    AdcRegs.ADCSOC7CTL.bit.CHSEL    = 7;        // reserved

    AdcRegs.ADCSOC8CTL.bit.CHSEL    = 8;   // Vdc
    AdcRegs.ADCSOC9CTL.bit.CHSEL    = 9;   // IGBTtemp external sensor, pressor sensor etc
    AdcRegs.ADCSOC10CTL.bit.CHSEL    = 10; // reserved
    AdcRegs.ADCSOC11CTL.bit.CHSEL    = 11; // reserved
    AdcRegs.ADCSOC12CTL.bit.CHSEL    = 12; // reserved
    AdcRegs.ADCSOC13CTL.bit.CHSEL    = 13; // reserved
    AdcRegs.ADCSOC14CTL.bit.CHSEL    = 14; // reserved
    AdcRegs.ADCSOC15CTL.bit.CHSEL    = 15; // reserved

    AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC6CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC7CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC8CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC9CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC10CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC11CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC12CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC13CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC14CTL.bit.TRIGSEL  = 5;
    AdcRegs.ADCSOC15CTL.bit.TRIGSEL  = 5;

    AdcRegs.ADCSOC0CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC1CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC2CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC3CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC4CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC5CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC6CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC7CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC8CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC9CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC10CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC11CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC12CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC13CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC14CTL.bit.ACQPS    = 6;
    AdcRegs.ADCSOC15CTL.bit.ACQPS    = 6;

    EDIS;
}

#define I_RATIO   0.00061      // 두번 확인, 이값이 맞는것 같음
//#define I_RATIO   0.00122      // 두번 확인했음  이 값을 틀린것 같음.

interrupt void adcIsr(void)
{
    double fTemp;
    //int temp;
    PERIOD_ADC_IRQ_SET;     // channel 2
    adc_result[0] = adcCurrentA =  AdcResult.ADCRESULT0; // 2019.0814  U 전류 환원 함
    adc_result[1] = adcCurrentB   = AdcResult.ADCRESULT1;

    //  adc_result[2] =  AdcResult.ADCRESULT2;
    //    adc_result[2] = adcCurrentA =  AdcResult.ADCRESULT2; // 2019.0707 U전류 신호가 없어 교환함

    adc_result[3] = AdcResult.ADCRESULT3;
    adc_result[4] = AdcResult.ADCRESULT4;
    adc_result[5] = AdcResult.ADCRESULT5;
    adc_result[6] = AdcResult.ADCRESULT6;
    adc_result[7] = AdcResult.ADCRESULT7;

    adc_result[8] = adcVdc  = AdcResult.ADCRESULT8;
    adc_result[9]   = adcIgbtTemperature = AdcResult.ADCRESULT9;

    adc_result[10] = AdcResult.ADCRESULT10;
    adc_result[11] = AdcResult.ADCRESULT11;
    adc_result[12] = AdcResult.ADCRESULT12;
    adc_result[13] = AdcResult.ADCRESULT13;
    adc_result[14] = AdcResult.ADCRESULT14;
    adc_result[15] = AdcResult.ADCRESULT15;

    dAdcIa      = (double)(adcCurrentA);
    dAdcIb      = (double)(adcCurrentB);
    dAdcVdc     = (double)(adcVdc);

    dAdcTemp    = (double)(adcIgbtTemperature);
    dAdcSens    = (double)(adcExSensor);
    dAdcCmd     = (double)(adcCmdAnalog);

    sensVdc = Vdc_factor * adcVdc + Vdc_calc_offset;
    lpfVdcIn[0] = sensVdc;
    lpf2nd( lpfVdcIn, lpfVdcOut, lpfVdcK);
    Vdc = (codeSetVdc > 0.5 ) ? 300.0 : lpfVdcOut[0];

    lpfIaIn[0] = -codeISensorValue * ( (double)adcCurrentA - codeIaOffset) * I_RATIO *codeIUSpan;
    lpf2nd( lpfIaIn, lpfIaOut, lpfIrmsK);
//    Is_abc[as] = lpfIaOut[0];
    Is_abc[as] = lpfIaIn[0];


    lpfIbIn[0] = -codeISensorValue * ( (double)adcCurrentB - codeIbOffset) * I_RATIO * codeIVSpan;
    lpf2nd( lpfIbIn, lpfIbOut, lpfIrmsK);
    //    Is_abc[bs] = lpfIbOut[0];
    Is_abc[bs] = lpfIbIn[0];

    Is_abc[cs]= -(Is_abc[as]+Is_abc[bs]);
    Is_dq[ds] = Is_abc[as];
    Is_dq[qs] = 0.577350 * Is_abc[as] + 1.15470 * Is_abc[bs];
    Is_mag = sqrt( Is_abc[as] *Is_abc[as] + Is_abc[bs] *Is_abc[bs]);           //
    Is_mag_rms = 0.707106*Is_mag;
    LPF1(Ts,1.0,fabs(Is_abc[as]),&LPF_Ia);                          // debug

    fTemp = adc_result[4] * 0.000244 ;
    LPF1(Ts,0.01, fTemp, &exSensRef);            // external sensor

    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

    PERIOD_ADC_IRQ_CLEAR;     // channel 2
    return;
}

void analog_out_proc( )
{
}

int check_sensor_trip( )
{
	int TripCode;

	Nop();

	if( ( TripCode = CheckOverCurrent()) != 0 ) return TripCode ;	// debug
	if( ( TripCode = CheckOverVolt()   ) != 0 ) return TripCode ;
	if( ( TripCode = CheckUndeVolt()   ) != 0 ) return TripCode ;	//.
	return 0;
}
// end of file

