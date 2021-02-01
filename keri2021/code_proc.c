#include	"header.h"
#include	"extern.h"

int getCodeOperation(int address,int cmd , CODE_INFO *  codes);
int getCodeMotorRef(int address,int cmd , CODE_INFO *  codes);

int get_code_information(int address,int cmd , CODE_INFO *  codes)
{
    int returnVal;

    if( address <= CODE_OPERAND_END){
        returnVal =  getCodeOperation(address,cmd , codes);
    } else {
        returnVal = getCodeMotorRef(address, cmd, codes);
    }
    return returnVal;
}

int getCodeOperation(int address,int cmd , CODE_INFO *  codes)
{	
	switch(address)
	{
    case CODE_set_vdc:
        strncpy(codes->disp, "set Vdc 300.0",20);
        if( cmd == CMD_WRITE_RAM ) codeSetVdc = codes->code_value;
        set_code_default(0,1,0,codeSetVdc,0,codes);
        break;

    case CODE_protect_off:
        strncpy(codes->disp, "Protect Off",20);
        if( cmd == CMD_WRITE_RAM ) codeProtectOff = codes->code_value;
        set_code_default(0,1,1,codeProtectOff,0,codes);
        break;

    case CODE_LpfOff:
        strncpy(codes->disp, "codeLpfOff",20);
        if( cmd == CMD_WRITE_RAM ) codeLpfOff = codes->code_value;
        set_code_default( 0.0, 1.0, 0.0, codeLpfOff,0,codes);
        break;

    case CODE_LpfFreq:
        strncpy(codes->disp, "codeLpfFreq",20);
        if( cmd == CMD_WRITE_RAM ) codeLpfFreq = codes->code_value;
        set_code_default( 500.0, 5000.0, 1000.0, codeLpfFreq,0,codes);
        break;


    case CODE_motorId:
        strncpy(codes->disp, "select motor",20);
        if( cmd == CMD_WRITE_RAM ) code_motorId = codes->code_value;
        set_code_default(0,3,0,code_motorId,0,codes);
        break;

    case CODE_adc_Vdc_low:
           strncpy(codes->disp, "adc Vdc low",20);
           if( cmd == CMD_WRITE_RAM ) code_adc_Vdc_low = codes->code_value;
           set_code_default(100.0, 3000.0, 1833.0, code_adc_Vdc_low,0,codes);
           break;

   case CODE_adc_Vdc_high:
       strncpy(codes->disp, "adc Vdc high",20);
       if( cmd == CMD_WRITE_RAM ) code_adc_Vdc_high = codes->code_value;
       set_code_default(500.0, 4000.0, 2852.0, code_adc_Vdc_high,0,codes);
       break;

   case CODE_Vdc_calc_low:
       strncpy(codes->disp, "Vdc calc_low",20);
       if( cmd == CMD_WRITE_RAM ) code_Vdc_calc_low = codes->code_value;
       set_code_default(0.0, 500.0, 100.0, code_Vdc_calc_low,0,codes);
       break;

   case CODE_Vdc_calc_high:
       strncpy(codes->disp, "Vdc calc_high",20);
       if( cmd == CMD_WRITE_RAM ) code_Vdc_calc_high = codes->code_value;
       set_code_default(50.0,999.0, 549.0,code_Vdc_calc_high,0,codes);
       break;

//--- codes for test
   case CODE_RampTest:
       strncpy(codes->disp, "turn Dir On/Off",20);
       if( cmd == CMD_WRITE_RAM ) codeRampTest = codes->code_value;
       set_code_default(0.0,1.0,0.0,codeRampTest,0,codes);
       break;

   case CODE_posi_duration_time:
       strncpy(codes->disp, "posi_duration_time",20);
       if( cmd == CMD_WRITE_RAM ) posi_duration_time = codes->code_value;
       set_code_default(0.0,30.0,3.0,posi_duration_time,0,codes);
       break;

   case CODE_zero_duration_time:
       strncpy(codes->disp, "zero_duration_time",20);
       if( cmd == CMD_WRITE_RAM ) zero_duration_time = codes->code_value;
       set_code_default(0.0,30.0,3.0,zero_duration_time,0,codes);
       break;

   case CODE_nega_duration_time:
       strncpy(codes->disp, "nega_duration_time",20);
       if( cmd == CMD_WRITE_RAM ) nega_duration_time = codes->code_value;
       set_code_default(0.0,30.0,3.0,nega_duration_time,0,codes);
       break;

   case CODE_test_accel_time:
       strncpy(codes->disp, "test_accel_time",20);
       if( cmd == CMD_WRITE_RAM ) test_accel_time = codes->code_value;
       set_code_default(0.0,30.0,3.0,test_accel_time,0,codes);
       break;

   case CODE_test_decel_time:
       strncpy(codes->disp, "test_decel_time",20);
       if( cmd == CMD_WRITE_RAM ) test_decel_time = codes->code_value;
       set_code_default(0.0,30.0,3.0,test_decel_time,0,codes);
       break;

//--- scope channel setting
    case CODE_scopeLoopCount:
        strncpy(codes->disp, "scope Loop Count",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeLoopCount = codes->code_value;
        set_code_default(0.0,100.0,0.0,codeScopeLoopCount,0,codes);
        break;
//--- ch1 Point Scale Offset
    case CODE_scopePointCh1:
        strncpy(codes->disp, "scope Point Ch1",20);
        if( cmd == CMD_WRITE_RAM ) codeScopePointCh1 = codes->code_value;
        set_code_default(0.0,50.0,4.0,codeScopePointCh1,0,codes);
        break;
    case CODE_scopeScaleCh1:
        strncpy(codes->disp, "scope Scale Ch1",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeScaleCh1 = codes->code_value;
        set_code_default(0.1,500.0,5.0,codeScopeScaleCh1,0,codes);
        break;
    case CODE_scopeOffsetCh1:
        strncpy(codes->disp, "scope Offset Ch1",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeOffsetCh1 = codes->code_value;
        set_code_default(0.0,500.0,0.0,codeScopeOffsetCh1,0,codes);
        break;
//--- ch2 Point Scale Offset
    case CODE_scopePointCh2:
        strncpy(codes->disp, "scope Point Ch2",20);
        if( cmd == CMD_WRITE_RAM ) codeScopePointCh2 = codes->code_value;
        set_code_default(0.0,50.0,5.0,codeScopePointCh2,0,codes);
        break;
    case CODE_scopeScaleCh2:
        strncpy(codes->disp, "scope Scale Ch2",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeScaleCh2 = codes->code_value;
        set_code_default(0.1,500.0,5.0,codeScopeScaleCh2,0,codes);
        break;
    case CODE_scopeOffsetCh2:
        strncpy(codes->disp, "scope Offset Ch2",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeOffsetCh2 = codes->code_value;
        set_code_default(0.0,500.0,0.0,codeScopeOffsetCh2,0,codes);
        break;
//--- ch3 Point Scale Offset
    case CODE_scopePointCh3:
        strncpy(codes->disp, "scope Point Ch3",20);
        if( cmd == CMD_WRITE_RAM ) codeScopePointCh3 = codes->code_value;
        set_code_default(0.0,50.0,2.0,codeScopePointCh3,0,codes);
        break;
    case CODE_scopeScaleCh3:
        strncpy(codes->disp, "scope Scale Ch3",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeScaleCh3 = codes->code_value;
        set_code_default(0.1,500.0,5.0,codeScopeScaleCh3,0,codes);
        break;
    case CODE_scopeOffsetCh3:
        strncpy(codes->disp, "scope Offset Ch3",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeOffsetCh3 = codes->code_value;
        set_code_default(0.0,500.0,0.0,codeScopeOffsetCh3,0,codes);
        break;
//--- ch4 Point Scale Offset
    case CODE_scopePointCh4:
        strncpy(codes->disp, "scope Point Ch4",20);
        if( cmd == CMD_WRITE_RAM ) codeScopePointCh4 = codes->code_value;
        set_code_default(0.0,50.0,3.0,codeScopePointCh4,0,codes);
        break;
    case CODE_scopeScaleCh4:
        strncpy(codes->disp, "scope Scale Ch4",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeScaleCh4 = codes->code_value;
        set_code_default(0.1,500.0,5.0,codeScopeScaleCh4,0,codes);
        break;
    case CODE_scopeOffsetCh4:
        strncpy(codes->disp, "scope Offset Ch4",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeOffsetCh4 = codes->code_value;
        set_code_default(0.0,500.0,0.0,codeScopeOffsetCh4,0,codes);
        break;

    case CODE_graphPointCh1:
        strncpy(codes->disp, "Graph Point Ch1",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphPointCh1 = codes->code_value;
        set_code_default(0.0,50.0,42.0,codeGraphPointCh1,0,codes);
        break;
    case CODE_graphScaleCh1:
        strncpy(codes->disp, "graph Scale Ch1",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphScaleCh1 = codes->code_value;
        set_code_default(0.1,500.0,2.0,codeGraphScaleCh1,0,codes);
        break;
    case CODE_graphOffsetCh1:
        strncpy(codes->disp, "graph Offset Ch1",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphOffsetCh1 = codes->code_value;
        set_code_default(0.0,500.0,0.0,codeGraphOffsetCh1,0,codes);
        break;

    case CODE_graphPointCh2:
        strncpy(codes->disp, "Graph Point Ch2",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphPointCh2 = codes->code_value;
        set_code_default(0.0,50.0,27.0,codeGraphPointCh2,0,codes);
        break;
    case CODE_graphScaleCh2:
        strncpy(codes->disp, "graph Scale Ch2",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphScaleCh2 = codes->code_value;
        set_code_default(0.1,500.0,2.0,codeGraphScaleCh2,0,codes);
        break;
    case CODE_graphOffsetCh2:
        strncpy(codes->disp, "graph Offset Ch2",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphOffsetCh2 = codes->code_value;
        set_code_default(0.0,500.0,0.0,codeGraphOffsetCh2,0,codes);
        break;

    case CODE_graphPointCh3:
        strncpy(codes->disp, "Graph Point Ch3",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphPointCh3 = codes->code_value;
        set_code_default(0.0,50.0,7,codeGraphPointCh3,0,codes);
        break;
    case CODE_graphScaleCh3:
        strncpy(codes->disp, "graph Scale Ch3",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphScaleCh3 = codes->code_value;
        set_code_default(0.1,500.0,20.0,codeGraphScaleCh3,0,codes);
        break;
    case CODE_graphOffsetCh3:
        strncpy(codes->disp, "graph Offset Ch3",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphOffsetCh3 = codes->code_value;
        set_code_default(0.0,500.0,300.0,codeGraphOffsetCh3,0,codes);
        break;

    case CODE_graphPointCh4:
        strncpy(codes->disp, "Graph Point Ch4",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphPointCh4 = codes->code_value;
        set_code_default(0.0,50.0,35.0,codeGraphPointCh4,0,codes);
        break;
    case CODE_graphScaleCh4:
        strncpy(codes->disp, "graph Scale Ch4",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphScaleCh4 = codes->code_value;
        set_code_default(0.1,500.0,100.0,codeGraphScaleCh4,0,codes);
        break;
    case CODE_graphOffsetCh4:
        strncpy(codes->disp, "graph Offset Ch4",20);
        if( cmd == CMD_WRITE_RAM ) codeGraphOffsetCh4 = codes->code_value;
        set_code_default(0.0,500.0,0.0,codeGraphOffsetCh4,0,codes);
        break;

// auto tuning
    case CODE_AT_Freq_Leq_Req:
        strncpy(codes->disp, "Freq LeqReq",20);
        if( cmd == CMD_WRITE_RAM ) AT_Freq_Leq_Req = codes->code_value;
        set_code_default(5.0,30.0,15.0,AT_Freq_Leq_Req,0,codes);
        break;

    case CODE_AT_Time_Leq_Req:
        strncpy(codes->disp, "AT_Time_Leq_Req",20);
        if( cmd == CMD_WRITE_RAM ) AT_Time_Leq_Req = codes->code_value;
        set_code_default(3.0,30.0,6.0,AT_Time_Leq_Req,0,codes);
        break;

    case CODE_AT_Is_Coeff_Leq_Req:
        strncpy(codes->disp, "AT_Is_Coeff_LeqReq",20);
        if( cmd == CMD_WRITE_RAM ) AT_Is_Coeff_Leq_Req = codes->code_value;
        set_code_default(0.1,1.0,0.5,AT_Is_Coeff_Leq_Req,0,codes);
        break;

    case CODE_AT_Is_Coeff_Rs:
        strncpy(codes->disp, "AT_Is_Coeff_Rs",20);
        if( cmd == CMD_WRITE_RAM ) AT_Is_Coeff_Rs = codes->code_value;
        set_code_default(0.1,1.0,0.5,AT_Is_Coeff_Rs,0,codes);
        break;

    case CODE_AT_Time_Rs:
        strncpy(codes->disp, "AT_Time_Rs",20);
        if( cmd == CMD_WRITE_RAM ) AT_Time_Rs = codes->code_value;
        set_code_default(3.0,30.0,6.0,AT_Time_Rs,0,codes);
        break;

    case CODE_AT_DeadTimeGain:
        strncpy(codes->disp, "AT_DeadTimeGain",20);
        if( cmd == CMD_WRITE_RAM ) AT_DeadTimeGain = codes->code_value;
        set_code_default(0.0,1.2,1.0,AT_DeadTimeGain,0,codes);
        break;

    case CODE_AT_Ls_Vs_RAMP:
        strncpy(codes->disp, "AT_Ls_Vs_RAMP",20);
        if( cmd == CMD_WRITE_RAM ) AT_Ls_Vs_RAMP = codes->code_value;
        set_code_default(0.01,10.0,5.0,AT_Ls_Vs_RAMP,0,codes);
        break;

    case CODE_AT_Freq_Ls:
        strncpy(codes->disp, "AT_Freq_Ls(Hz)",20);
        if( cmd == CMD_WRITE_RAM ) AT_Freq_Ls = codes->code_value;
        set_code_default(1.5,10.0,4.0,AT_Freq_Ls,0,codes);
        break;

    case CODE_AT_Time_Ls:
        strncpy(codes->disp, "AT_Time_Ls(sec)",20);
        if( cmd == CMD_WRITE_RAM ) AT_Time_Ls = codes->code_value;
        set_code_default(4.0,30.0,7.0,AT_Time_Ls,0,codes);
        break;

	case CODE_END:
		return -2;
			
	default:
		return -1;
	}
	return 0;
}

int getCodeMotorRef(int address,int cmd , CODE_INFO *  codes)
{
    if (address < 100) return -1;
    switch(address){
    case CODE_rate_power:
        strncpy(codes->disp, "Rate_power",20);
        if( cmd == CMD_WRITE_RAM ) codeRatePower = codes->code_value;
        set_code_default(100,2.0e+6,400,codeRatePower,0,codes);
        break;

    case CODE_rate_volt:
        strncpy(codes->disp, "Rate Volt (Vrms)",20);
        if( cmd == CMD_WRITE_RAM ) codeRateVolt = codes->code_value;
        set_code_default(100.0,600.0,220.0,codeRateVolt,0,codes);
        break;

    case CODE_rate_current:
        strncpy(codes->disp, "Rate Current(A)",20);
        if( cmd == CMD_WRITE_RAM ) codeRateCurrent = codes->code_value;
        set_code_default(1.0,2000.0,2.3,codeRateCurrent,0,codes);
        break;

    case CODE_rate_effiency:
        strncpy(codes->disp, "Motor Effiency",20);
        if( cmd == CMD_WRITE_RAM ) codeRateEffiency = codes->code_value;
        set_code_default(0.2,0.99,0.65,codeRateEffiency,0,codes);
        break;

    case CODE_rate_rpm:
        strncpy(codes->disp, "Rate RPM",20);
        if( cmd == CMD_WRITE_RAM ) codeRateRpm = codes->code_value;
        set_code_default(500,80000.0,1690.0,codeRateRpm,0,codes);
        break;

    case CODE_rate_hz:
        strncpy(codes->disp, "Rate hz",20);
        if( cmd == CMD_WRITE_RAM ) codeRateHz = codes->code_value;
        set_code_default(30.0,300.0,60.0,codeRateHz,0,codes);
        break;

    case CODE_motor_pole:
        strncpy(codes->disp, "Motor Pole ",20);
        if( cmd == CMD_WRITE_RAM ) codeMotorPole = codes->code_value;
        set_code_default(2,20,4,codeMotorPole,0,codes);
        break;

    case CODE_MotorCtrMode:
        strncpy(codes->disp, "select Ctrl Mode",20);
        if( cmd == CMD_WRITE_RAM ) codeMotorCtrlMode = codes->code_value;
        set_code_default(0,9,0,codeMotorCtrlMode,0,codes);
        break;

    case CODE_IaOffset:
        strncpy(codes->disp, "Ia Offset",20);
        if( cmd == CMD_WRITE_RAM ) codeIaOffset = codes->code_value;
        set_code_default(1000.0,3000.0,2014.0,codeIaOffset,0,codes);
        break;

    case CODE_IbOffset:
        strncpy(codes->disp, "Ib Offset",20);
        if( cmd == CMD_WRITE_RAM ) codeIbOffset = codes->code_value;
        set_code_default(1000.0,3000.0,2015.0,codeIbOffset,0,codes);
        break;

    case CODE_I_sense_value:
        strncpy(codes->disp, "I_sense_value (A)",20);
        if( cmd == CMD_WRITE_RAM ) codeISensorValue = codes->code_value;
        set_code_default(5.0,2000.0, 100.0,codeISensorValue,0,codes);
        break;

    case CODE_u_phase_I_sense_span:
        strncpy(codes->disp, "u I_sense_span ",20);
        if( cmd == CMD_WRITE_RAM ) codeIUSpan = codes->code_value;
        set_code_default(0.5,1.5,1.0,codeIUSpan,0,codes);
        break;

    case CODE_v_phase_I_sense_span:
         strncpy(codes->disp, "v_I_sense_span ",20);
         if( cmd == CMD_WRITE_RAM ) codeIVSpan = codes->code_value;
         set_code_default(0.5,1.5,1.0,codeIVSpan,0,codes);
         break;

    case CODE_IsMaxCoef:
        strncpy(codes->disp, "IsMaxCoef",20);
        if( cmd == CMD_WRITE_RAM ) codeIsMaxCoef = codes->code_value;
        set_code_default(0.1,4.0,2.0,codeIsMaxCoef,0,codes);
        break;

    case CODE_Kp_IsTemp:
        strncpy(codes->disp, "Kp IsTemp ",20);
        if( cmd == CMD_WRITE_RAM ) codeKpIsTemp = codes->code_value;
        set_code_default(0.1,1000.0,5.0,codeKpIsTemp,0,codes);
        break;

    case CODE_Ki_IsTemp:
        strncpy(codes->disp, "Ki IsTemp ",20);
        if( cmd == CMD_WRITE_RAM ) codeKiIsTemp = codes->code_value;
        set_code_default(0.1,100000.0,3000,codeKiIsTemp,0,codes);
        break;

    case CODE_KpIs:
        strncpy(codes->disp, "Kp Is_Coeff",20);
        if( cmd == CMD_WRITE_RAM ) codeKpIsCoeff = codes->code_value;
        set_code_default(0.1,10.0,0.5,codeKpIsCoeff,0,codes);
        break;

    case CODE_KiIs:
        strncpy(codes->disp, "Ki Is_Coeff",20);
        if( cmd == CMD_WRITE_RAM ) codeKiIsCoeff = codes->code_value;
        set_code_default(0.1,20.0,1.0,codeKiIsCoeff,0,codes);
        break;

    case CODE_Rs:
        strncpy(codes->disp, "Motor State Rs",20);
        if( cmd == CMD_WRITE_RAM ) Rs = codes->code_value;
        set_code_default(0.002,20.0,5.5453, Rs,0,codes);
        break;

    case CODE_Rr:
        strncpy(codes->disp, "Motor Rotor Rr",20);
        if( cmd == CMD_WRITE_RAM ) Rr = codes->code_value;
        set_code_default(0.002,20.0,5.5453, Rr,0,codes);
        break;

    case CODE_Ls:
        strncpy(codes->disp, "Motor State Ls",20);
        if( cmd == CMD_WRITE_RAM ) Ls = codes->code_value;
        set_code_default(0.0001,1.0,0.252, Ls,0,codes);
        break;

    case CODE_Lr:
        strncpy(codes->disp, "Motor State Lr",20);
        if( cmd == CMD_WRITE_RAM ) Lr = codes->code_value;
        set_code_default(0.0001,1.0,0.252, Lr,0,codes);
        break;

    case CODE_Lm:
        strncpy(codes->disp, "Motor Mutual Lm",20);
        if( cmd == CMD_WRITE_RAM ) Lm = codes->code_value;
        set_code_default(0.0001,1.0,0.232, Lm,0,codes);
        break;

    case CODE_Jm:
        strncpy(codes->disp, "Motor Intertia Jm",20);
        if( cmd == CMD_WRITE_RAM ) Jm = codes->code_value;
        set_code_default(1.0e-4,100.0,5.0, Jm,0,codes);
        break;

    case CODE_accel_time1:
        strncpy(codes->disp, "accel_time1 (sec)",20);
        if( cmd == CMD_WRITE_RAM ) codeAccelTime1 = codes->code_value;
        set_code_default(0.0,3000.0,5.0,codeAccelTime1,0,codes);
        break;

    case CODE_decel_time1:
        strncpy(codes->disp, "decel_time1 (sec)",20);
        if( cmd == CMD_WRITE_RAM ) codeDecelTime1 = codes->code_value;
        set_code_default(0.0,3000.0,5.0,codeDecelTime1,0,codes);
        break;

    case CODE_speed1:
        strncpy(codes->disp, "speed1 (p.u)",20);
        if( cmd == CMD_WRITE_RAM ) codeSpeed1 = codes->code_value;
        set_code_default(0.0,0.9,0.25,codeSpeed1,0,codes);
        break;

    case CODE_speed2:
        strncpy(codes->disp, "speed2 (p.u)",20);
        if( cmd == CMD_WRITE_RAM ) codeSpeed2 = codes->code_value;
        set_code_default(0.0,1.2,0.25,codeSpeed2,0,codes);
        break;

    case CODE_pwm_freq:
        strncpy(codes->disp, "PWM Freq",20);
        if( cmd == CMD_WRITE_RAM ) codePwmFreq = codes->code_value;
        set_code_default(500.0,10000.0,2500.0,codePwmFreq,0,codes);
        break;

    case CODE_StartRef:
         strncpy(codes->disp,"start ref",20);
         if( cmd == CMD_WRITE_RAM ) codeStartRef = codes->code_value;
         set_code_default(0.001,1.0,0.01,codeStartRef,0,codes);
         break;

    case CODE_EncoderPulse:                // 11
        strncpy(codes->disp, "encoder pulse",20);
        if( cmd == CMD_WRITE_RAM ) code_encoderPulse = codes->code_value;
        set_code_default(50.0, 8000.0, 80.0, code_encoderPulse, 0 , codes);
        break;

// protection
    case CODE_I_over:
         strncpy(codes->disp, " I over",20);
         if( cmd == CMD_WRITE_RAM ) codeIOver = codes->code_value;
         set_code_default(5,2000,300,codeIOver,0,codes);
         break;

    case CODE_UVLevel:
         strncpy(codes->disp,"Unde Volt Level",20);
         if( cmd == CMD_WRITE_RAM ) codeUnderVoltLevel = codes->code_value;
         set_code_default(0.0,500.0,200.0,codeUnderVoltLevel,0,codes);
         break;

    case CODE_OVLevel:
         strncpy(codes->disp,"Over Volt Level",20);
         if( cmd == CMD_WRITE_RAM ) codeOverVoltLevel = codes->code_value;
         set_code_default(10.0,999.0,370.0,codeOverVoltLevel,0,codes);
         break;

    case CODE_Base_Flux_Coeff:
        strncpy(codes->disp, "Base_Flux_Coeff",20);
        if( cmd == CMD_WRITE_RAM ) Base_Flux_Coeff =codes->code_value;
        set_code_default(0.1,2.5,0.92,Base_Flux_Coeff,0,codes);
        break;

    case CODE_VoltPIOn:
        strncpy(codes->disp, "F Weaken VoltPI ON",20);
        if( cmd == CMD_WRITE_RAM ) codeVoltPIOn =codes->code_value;
        set_code_default(0.0,1.0,0.0,codeVoltPIOn,0,codes);
        break;

    case CODE_wn_wr_Coeff:
        strncpy(codes->disp, "wn_wr_Coeff",20);
        if( cmd == CMD_WRITE_RAM ) wn_wr_Coeff = codes->code_value;
        set_code_default(0.1,30.0,5.0,wn_wr_Coeff,0,codes);
        break;

    case CODE_KpVsw:                // 11
        strncpy(codes->disp, "Kp FW Voltage Ctrl",20);
        if( cmd == CMD_WRITE_RAM ) codeKpVsw = codes->code_value;
        set_code_default(0.0001, 10000.0, 0.01, codeKpVsw, 0 , codes);
        break;

    case CODE_KiVsw:                // 11
        strncpy(codes->disp, "Ki FW Voltage Ctrl",20);
        if( cmd == CMD_WRITE_RAM ) codeKiVsw = codes->code_value;
        set_code_default(0.01, 10000.0, 0.5, codeKiVsw, 0 , codes);
        break;

    case CODE_VswErrLimit:                // 11
        strncpy(codes->disp, "Vsw Int Limit",20);
        if( cmd == CMD_WRITE_RAM ) codeVswErrLimit = codes->code_value;
        set_code_default( 0.01, 1000.0, 5.0, codeVswErrLimit, 0 , codes);
        break;

    case CODE_VsdErrLimit:                // 11
        strncpy(codes->disp, "Vsd Int Limit",20);
        if( cmd == CMD_WRITE_RAM ) codeVsdErrLimit = codes->code_value;
        set_code_default( 0.01, 1000.0, 5.0, codeVsdErrLimit, 0 , codes);
        break;

    case CODE_FwCoef1:
        strncpy(codes->disp, "field weak Coef1",20);
        if( cmd == CMD_WRITE_RAM ) codeFwCoef1 = codes->code_value;
        set_code_default(0.01,10.0,1.0,codeFwCoef1,0,codes);
        break;

    case CODE_FwCoef2:
        strncpy(codes->disp, "Field weak Coef2",20);
        if( cmd == CMD_WRITE_RAM ) codeFwCoef2 = codes->code_value;
        set_code_default(0.00,10000.0,1.0,codeFwCoef2,0,codes);
        break;

    case CODE_KpWrCoef:
        strncpy(codes->disp, "code Kp Wr Coef",20);
        if( cmd == CMD_WRITE_RAM ) codeKpWrCoef = codes->code_value;
        set_code_default(0.0,1000.0,1.0,codeKpWrCoef,0,codes);
        break;

    case CODE_KiWrCoef:
        strncpy(codes->disp, "code Ki Wr Coef ",20);
        if( cmd == CMD_WRITE_RAM ) codeKiWrCoef = codes->code_value;
        set_code_default(0.0,1000.0,1.0,codeKiWrCoef,0,codes);
        break;

    case CODE_Fw2On:
        strncpy(codes->disp, "Field Weak 2 ON ",20);
        if( cmd == CMD_WRITE_RAM ) codeFw2On = codes->code_value;
        set_code_default(0.0,1.0,0.0,codeFw2On,0,codes);
        break;

    case CODE_Fw1WeCoef:
        strncpy(codes->disp, "FW1 we Coef ",20);
        if( cmd == CMD_WRITE_RAM ) codeFw1WeCoef = codes->code_value;
        set_code_default(0.5,2.0,1.0,codeFw1WeCoef,0,codes);
        break;

    case CODE_END:
        return -2;

    default:
        return -1;
    }
    return 0;
}

void set_code_default(double min, double max, double defaults, double value,int open_level, CODE_INFO * codes )
{
	codes->type 		= TYPE_float;
	codes->open_level 	= open_level;
	codes->code_min		= min;
	codes->code_max		= max;
	codes->code_default	= defaults;
	codes->code_value 	= value;
}

void data_under_proc(int address, UNION32 u32data)
{
    int trip_code;
    float trip_data;

    trip_code = address;
    trip_data = u32data.dword;
    trip_recording( trip_code, trip_data,"Data Under");
}

void data_over_proc(int address,UNION32 u32data)
{
    int trip_code;
    float trip_data;

    trip_code = address;
    trip_data = u32data.dword;
    trip_recording( trip_code, trip_data,"Data Over");
}

void invalid_address_proc(int address )
{
    int trip_code;
    float trip_data;

    trip_code = address;
    trip_data = 0.0;
    trip_recording( trip_code, trip_data,"Invalid Address");
}

int check_code_data(int address, UNION32 u32data )
{
    int cmd,check,return_value;

    cmd = CMD_READ_DATA;

    check = get_code_information( address, cmd , & code_inform);
    if( check){
        invalid_address_proc( address );
        return -1;
    }

    if( code_inform.code_min > u32data.dword ){
        data_under_proc(address, u32data);
        return_value = -1;
    }
    else if(code_inform.code_max < u32data.dword ){
        data_over_proc(address, u32data);
        return_value = -1;
    }
    else {
        code_inform.code_value = u32data.dword;
        cmd = CMD_WRITE_RAM;
        check =  get_code_information( address,cmd, & code_inform);
        return_value = 0;
    }
    return return_value;
}

int check_backup_data()
{
	UNION32	data;
	int check,address,cmd;
	
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
    for( address = 0 ; address <= CODE_END; address++){	 // code group �� 6��
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            Flag_TripDataBackup = 1;
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 0;
            check = check_code_data(address, data );	// check min and max boundary
            if(check)  return -1;
        }
    }
	return 0;
}


void save_backup_data()
{
	UNION32	data;
	int check,address,cmd;
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
	for( address = 0 ; address <= CODE_END ; address++){
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 1;
            write_code_2_eeprom( address,data);
            Flag_TripDataBackup = 0;
        }
	}
}

void backup_data_load()
{
	UNION32	data;
	int check,address,cmd;
	
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
    for( address = 0; address <= CODE_END ;address++)
    {
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            Flag_TripDataBackup = 1;
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 0;
            write_code_2_eeprom( address,data);
            code_inform.code_value = data.dword;
            cmd = CMD_WRITE_RAM;
            check = get_code_information( address,cmd, & code_inform);
        }
	}
}
double CheckSum()
{
    return 0.0;
}

int SaveDataProc(int addr, double data)
{
	int cmd,i,return_value;
	char SciBuf[30]={0};
	char str[30];
	UNION32 u32data,u32data2;

	return_value = 0;

	cmd = CMD_READ_DATA;

	i = get_code_information( addr,cmd,&code_inform); 

	if( i != 0 ) goto _SAVE_ERROR_INVALID_ADDR;   

	if( addr >= 800 ){

		if( data < 1.22 ) goto _SAVE_ERROR_INVALID_DATA; 
		if( data > 1.24 ) goto _SAVE_ERROR_INVALID_DATA; 
		switch(addr)
		{
		case CODE_Data_Check: 	return_value = check_backup_data();	break;
		case CODE_Data_Backup:
			strncpy(str,"Wait for Data Backup",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			save_backup_data();
			strncpy(str,"Wait for Error Check",20);
			load_sci_tx_mail_box(str);  delay_msecs(20);

			break;
		case CODE_Data_Load:
			strncpy(str,"Wait for Data Load !",20);
			load_sci_tx_mail_box(str); delay_msecs(20);	
			backup_data_load();
			break;
		case CODE_Data_Init:
			strncpy(str,"Wait For Data Init !",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			init_eprom_data();
			strncpy(str,"Data Init OK !      ",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			break;

		default:
			goto _SAVE_ERROR_INVALID_ADDR;
		}
		return return_value;
	}

    if( code_inform.code_min > data ){
        goto _SAVE_ERROR_DATA_UNDER;
    }
    else if( code_inform.code_max < data ){
        goto _SAVE_ERROR_DATA_OVER;
    }
    else {
        u32data.dword = data;
        read_eprom_data( addr, & u32data2);
        if( u32data.dword != u32data2.dword ){
            write_code_2_eeprom( addr, u32data);
            delay_msecs(1);
            read_eprom_data( addr, & u32data2);

            if( u32data.dword != u32data2.dword ) goto _EEPROM_WRITE_ERROR;

            code_inform.code_value = data;
            cmd = CMD_WRITE_RAM;
            get_code_information( addr,cmd, & code_inform);

            // CheckSum Save
            u32data.dword = CheckSum();
            EepromSaveFlag = 1;
            write_code_2_eeprom(EPROM_ADDR_CHECKSUM, u32data);
            EepromSaveFlag = 0;

            load_sci_tx_mail_box("OK write success") ;
        }
        else{
            load_sci_tx_mail_box("Equal Data write skipped");
        }
        return 0;
    }
_SAVE_ERROR_INVALID_ADDR:
//	strcpy(SciBuf, "ADDR");
	strcpy(SciBuf,"Invalid Address" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_DATA_UNDER:

//	strcpy(SciBuf, "UNDE");

	strcpy(SciBuf,"Input data under" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_DATA_OVER:
//	strcpy(SciBuf, "OVER");
	strcpy(SciBuf,"Input data over" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_INVALID_DATA:
//	strcpy(SciBuf, "DATA");
	strcpy(SciBuf,"Invalid data " );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_EEPROM_WRITE_ERROR:
//	strcpy(SciBuf, "DATA");
	strcpy(SciBuf,"Eeprom write error" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;
}


int init_eprom_data()
{
	UNION32	data,data2;
	int check,address,cmd;
	char str[41] = {0};

	data.dword  = 0.0;

	cmd = CMD_READ_DATA;
    for( address = 0 ; address < CODE_END ; address++ )
    {
        cmd = CMD_READ_DATA;
        check = get_code_information( address, cmd , & code_inform);
        if( check==0 ){
            data.dword = code_inform.code_default;
            read_eprom_data(address, & data2 );
            if( data.dword != data2.dword)  {
                write_code_2_eeprom( address,data);
                delay_msecs(13);
                read_eprom_data(address, & data2 );
                if( data.dword != data2.dword){
                    snprintf( str,40,"Trip Eeprom Init code = %4d \r\n: ",address);
                    load_scia_tx_mail_box(str);
                    delay_msecs(50);
                    return -1;
                }
            } else {
                code_inform.code_value = data.dword;
                cmd = CMD_WRITE_RAM;
                check = get_code_information( address,cmd, & code_inform);
            }
        }
    }

    //  code_motorId = i;
    for( address = 100 ; address < CODE_END ; address++ ){
        cmd = CMD_READ_DATA;
        check = get_code_information( address, cmd , & code_inform);
        if( check==0 ){
            data.dword = code_inform.code_default;
            read_eprom_data(address, & data2 );
            if( data.dword != data2.dword)  {
                write_code_2_eeprom( address,data);
                delay_msecs(13);
                read_eprom_data(address, & data2 );
                if( data.dword != data2.dword){
                    snprintf( str,40,"Trip Eeprom Init code = %4d \r\n: ",address);
                    load_scia_tx_mail_box(str);
                    delay_msecs(50);
                    return -1;
                }
            } else {
                code_inform.code_value = data.dword;
                cmd = CMD_WRITE_RAM;
                check = get_code_information( address,cmd, & code_inform);
            }
        }
    }
	return 0;
}

void readAllCodes()
{
    int check;
    int addr,cmd;
    char * str;
    scia_tx_end_addr = 0;
    scia_tx_start_addr = 0;
    loadSciaTxMailBox("9:4:901:0.000e+0:");
    loadSciaTxMailBox("//Read code data:");
    loadSciaTxMailBox("code  data  Disc:");
    for( addr = 0 ; addr <= CODE_END ; addr++){
        check = get_code_information( addr, cmd , & code_inform);
        if( !check ){
            snprintf( str, 6 ,"%4d,",addr); load_scia_tx_mail_box(str);
            snprintf( str,20,"%.3e,",code_inform.code_value);
            load_scia_tx_mail_box(str);
            load_scia_tx_mail_box(code_inform.disp);
            load_scia_tx_mail_box(" : ");
            delay_msecs(4);
        }
    }
    load_scia_tx_mail_box("endOfReadall.\r\n");
}

int loadDefaultCode()
{
    UNION32 data;
    int check,address,cmd;

    data.dword  = 0.0;

    cmd = CMD_READ_DATA;
    for( address = 0 ; address < CODE_END ; address++ )
    {
        cmd = CMD_READ_DATA;
        check = get_code_information( address, cmd , & code_inform);
        if( check==0 ){
            data.dword = code_inform.code_default;
            code_inform.code_value = data.dword;
            cmd = CMD_WRITE_RAM;
            check = get_code_information( address,cmd, & code_inform);
        }
    }
    return 0;
}

int load_code2ram()
{
    UNION32 data;
    int check;
    int addr,cmd;

    data.dword  = 0.0;
    cmd = CMD_READ_DATA;
    for( addr = 0 ; addr <= CODE_END ; addr++){
        check = get_code_information( addr, cmd , & code_inform);
        if( !check ){
            read_eprom_data( addr, & data);
            check = check_code_data(addr, data);    // check min and max boundary
            if(check)   return -1;
            else{
                code_inform.code_value = data.dword;
                cmd = CMD_WRITE_RAM;
                check = get_code_information( addr,cmd, & code_inform);
            }
        }
    }
    return 0;
}

int code_init()
{
    UNION32 datum;

    int check, cmd, addr;

    cmd = CMD_READ_DATA;
    for( addr = 0; addr < CODE_END; addr++){
        check = get_code_information( addr, cmd , & code_inform);
        if( !check ){
            datum.dword = code_inform.code_value;
            write_code_2_eeprom(addr, datum);
        }
    }
    check = load_code2ram();
    return check;
}


//--- end of code_proc.c
