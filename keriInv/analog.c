//
// analog.c  project : dcPower
// Eunwho Power Electronics by Cheoung Soon Gil
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

    AdcRegs.ADCSOC0CTL.bit.CHSEL= 0;        // I_u
    AdcRegs.ADCSOC1CTL.bit.CHSEL= 1;        // I_v
    AdcRegs.ADCSOC2CTL.bit.CHSEL= 8;        // Vdc
    AdcRegs.ADCSOC3CTL.bit.CHSEL= 9;        // V_out  IGBT_Temp

    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL = 5;

    AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC1CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC2CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC3CTL.bit.ACQPS = 6;
//    AdcRegs.ADCSAMPLEMODE.all = 0;      // Simultaneous sample mode
    EDIS;
}

#define ADC_IOUT_OFFSET     2048
#define ADC_IPRI_OFFSET     2048
#define ADC_VOUT_OFFSET     2048
#define ADC_VDC_OFFSET     2048

//--- 전류의 계산 : 66mV / A  :  3.3V -> 50A, 1 count = 50 / 4096 = 0.012207
#define I_RATIO         0.012207
//      vout scale = 20.0V / ( 4096/2 )
#define IOUT_SCALE      0.48828        // 1000A / 2048
#define IPRI_SCALE      0.097656        //  200A / 2048
#define VOUT_SCALE      0.009765       // 20.0 / (2048)
#define VDC_SCALE       0.39062        // 800V  / 2048

#define VDC_OFFSET      0.0
#define VOUT_OFFSET     0.0
#define IOUT_OFFSET     0.0
#define IPRI_OFFSET     0.0

interrupt void adcIsr(void)
{
//    TRIP_OUT_ON;
    //    int temp;
    adc_result[0] = adcIout = AdcResult.ADCRESULT0;           // Iout
    adc_result[1] = adcIpri = AdcResult.ADCRESULT1;           // Ipri
    adc_result[2] = adcVdc  = AdcResult.ADCRESULT2; // Vdc
    adc_result[3] = adcVout = AdcResult.ADCRESULT3; // Vout

    nativeIout = -IOUT_SCALE * ( adcIout-codeIoutAdcOffset ) * codeIoutScale;
    nativeIpri = -IPRI_SCALE * ( adcIpri-codeIoutAdcOffset ) * codeIpriScale;
    nativeVout = VoutScale * ( adcVout)  + VoutOffset;
    nativeVdc  = VdcScale  * ( adcVdc)  +  VdcOffset;

    lpfIoutIn[0] = nativeIout;
    lpf2nd( lpfIoutIn, lpfIoutOut, lpfIoutK);
    Iout = lpfIoutOut[0];

    lpfVoutIn[0] = nativeVout;
    lpf2nd( lpfVoutIn, lpfVoutOut, lpfVoutK);
    Vout = lpfVoutOut[0];

    lpfVdcIn[0] = nativeVdc;
    lpf2nd( lpfVdcIn, lpfVdcOut, lpfVdcK);

    if( gMachineState == STATE_READY){ Iout = 0.0; Vout = 0.0;}

    if( code_set_Vdc_on > 0.5 ) Vdc = 520;          // 2018.09.09
    else                        Vdc = lpfVdcOut[0];

    Pout = Vout * Iout ;

    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
//    TRIP_OUT_OFF;
    return;
}

int check_sensor_trip()
{
	int TripCode;
	Nop();
	if( ( TripCode = CheckOverCurrent()) != 0 ) return TripCode ;	// debug
	if( ( TripCode = CheckOverVolt()   ) != 0 ) return TripCode ;
	if( ( TripCode = CheckUndeVolt()   ) != 0 ) return TripCode ;	//
	return 0;
}
	
// end of file

