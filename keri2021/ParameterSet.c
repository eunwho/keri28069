// project : inverter for Electrical Vechile by Soongil Jung 2020.0208
#include	<header.h>
#include	<extern.h>

void commonVariableInit()
{
    double x1,x2,y1,y2;
    setScopePoint();

    we1FieldWeak = we_rat * codeFw1WeCoef  ;
    codeKpIs = codeKpIsCoeff * codeKpIsTemp;
    codeKiIs = codeKiIsCoeff * codeKiIsTemp;


    KpVsw = codeKpVsw * 0.001;
    KiVsw = codeKpVsw * 0.001/Ts;

    inveIrmsScale = 1.0 / codeISensorValue;

    if      ( codeRatePower <  10000.0) invePowerScale =  1/10000.0;
    else if ( codeRatePower <  50000.0) invePowerScale =  1/50000.0;
    else if ( codeRatePower < 100000.0) invePowerScale = 1/100000.0;
    else                                invePowerScale = 1/500000.0;

    scopeLoopCount = (int)(codeScopeLoopCount);

    scopePointCh1 = (int)(floor(codeScopePointCh1+0.5));
    scopePointCh2 = (int)(floor(codeScopePointCh2+0.5));
    scopePointCh3 = (int)(floor(codeScopePointCh3+0.5));
    scopePointCh4 = (int)(floor(codeScopePointCh4+0.5));

    invCodeScopeScaleCh1 = 2.0 / codeScopeScaleCh1;
    invCodeScopeScaleCh2 = 2.0 / codeScopeScaleCh2;
    invCodeScopeScaleCh3 = 2.0 / codeScopeScaleCh3;
    invCodeScopeScaleCh4 = 2.0 / codeScopeScaleCh4;

    graphPointCh1 = (int)(floor(codeGraphPointCh1+0.5));
    graphPointCh2 = (int)(floor(codeGraphPointCh2+0.5));
    graphPointCh3 = (int)(floor(codeGraphPointCh3+0.5));
    graphPointCh4 = (int)(floor(codeGraphPointCh4+0.5));

    invGraphScaleCh1 = 1.0 / ( codeGraphScaleCh1 * 5 );
    invGraphScaleCh2 = 1.0 / ( codeGraphScaleCh2 * 5 );
    invGraphScaleCh3 = 1.0 / ( codeGraphScaleCh3 * 5 );
    invGraphScaleCh4 = 1.0 / ( codeGraphScaleCh4 * 5 );

    x1 = code_adc_Vdc_low;      y1 = code_Vdc_calc_low;
    x2 = code_adc_Vdc_high;     y2 = code_Vdc_calc_high;

    Vdc_factor = ( y2-y1) / ( x2 - x1 );
    Vdc_calc_offset = (( y1 * x2 - y2 * x1 )/ (x2- x1));

    Vdc_factor = ( y2-y1) / ( x2 - x1 );
    Vdc_calc_offset = (( y1 * x2 - y2 * x1 )/ (x2- x1));

    C_ce_nF=(3.5-0.8)/(1000.0-100.0)*(2.0*Is_rat-100.0)+0.8;    // 1000A -> 3.5nF, 100A -> 0.8nF
    C_ce=1.0e-9*C_ce_nF;
    inv_C_ce=1.0/C_ce;

    // reference
    reference_in=0.0;
    reference_out=0.0;  // new
    Freq_ref=0.0;

    // time, count, flag
    DutyRatio[u] = DutyRatio[v] = DutyRatio[w] = 0.5; //2018.0627
    gfRunTime=0.0;

    Kt=(3.0/2.0)*(codeMotorPole/2.0);
    inv_Kt=1.0/Kt;
    P_pair=(codeMotorPole/2.0);
    inv_P_pair=1.0/P_pair;

    inv_Ts = codePwmFreq;
    Ts = 1.0 / codePwmFreq;  // pwm switching frequency
    Freq_rat = codeRateHz;
    inv_Freq_rat=1.0/Freq_rat;
    inv_motor_rate_hz = 1.0 / codeRateHz; //   csk_check 2009.10.30.

    frequency=0.0;

    theta=0.0;
    SinTheta=0.0;
    CosTheta=1.0;
    CosDeltaTheta=0.0;
    SinDeltaTheta=1.0;

    we_rat = PI_2 * codeRateHz;
    wr_rat = PI_2* codeMotorPole * codeRateRpm/120.0;
    wm_rat = wr_rat*(2.0/codeMotorPole);
    Te_rat = codeRatePower / wm_rat;
    inv_Te_rat=1.0/Te_rat;

    we_in=0.0;
    we=0.0;
    we0=0.0;

    wr_Cycle=0.0;
    wr_CycleIndex=0;
    wr_m0=0.0;
    wr_m=0.0;               // 쩍횉횁짝 쩌횙쨉쨉�횉 횉횎횇횒쨍쨉 횄횎짹창째짧 = 쩍횉횁짝 쩌횙쨉쨉
    wr=0.0;
    wr_ref=0.0;
    wr_ref=0.0;
    wr_err=0.0;
    wr_ErrInt=0.0;              // 쩌횙쨉쨉횁짝쩐챤짹창�횉 �청쨘횖쨌짰
    w_sl=0.0;
    w_sl0=0.0;

    rpm=0.0;
    rpm_m=0.0;
    theta_m=0.0;
    rpm_ref=0.0;
    rpm_err=0.0;
    rpm_Coeff = 60.0 * inv_P_pair/PI_2;             //

    // �쟾瑜�
    Is_rat=sqrt(2.0)*codeRateCurrent;
    inv_Is_rat=1.0/Is_rat;

    Is_dq[ds]=Is_dq[qs]=0.0;
    Is_mag=0.0;
    Is_mag_rms=0.0;
    sgn_Is[as]=sgn_Is[bs]=sgn_Is[cs]=0.0;

    Is_DQ[DS]=Is_DQ[QS]=0.0;
    Is_DQ_max[DS]=Is_DQ_max[QS]=0.0;
    Is_DQ_ref[DS]=Is_DQ_ref[QS]=0.0;
    prev_I_QS=0.0;
    Is_DQ_ErrInt[DS]=Is_DQ_ErrInt[QS]=0.0;          // �체쨌첫횁짝쩐챤짹창�횉 �청쨘횖쨌짰

    // �쟾�븬
    Vs_rat = sqrt(2.0)/sqrt(3.0) * codeRateVolt;         // �긽�쟾�븬�쓽 �뵾�겕 媛�
    Vs_max=0.0;
    Vs_ref = 0.0;
    Vs_abc[as]=Vs_abc[bs]=Vs_abc[cs]=0.0;
    Vs_abc_ref[as]=Vs_abc_ref[bs]=Vs_abc_ref[cs]=0.0;
    Vs_dq_ref[ds]=Vs_dq_ref[qs]=0.0;
    Vs_dq[ds]=Vs_dq[qs]=0.0;
    Vo=0.0;
    Us_dq[ds]=Us_dq[qs]=0.0;
    Vs_DQ[DS]=Vs_DQ[QS]=0.0;
    Vs_DQ_max[DS]=Vs_DQ_max[QS]=0.0;
    Vs_DQ_ref[DS]=Vs_DQ_ref[QS]=0.0;
    Vs_DQ_comp[DS]=Vs_DQ_comp[QS]=0.0;
    Vs_max_FW=0.0;
    Vs_DQ_ref_P[DS]=Vs_DQ_ref_P[QS]=0.0;
    Vs_DQ_ref_PI[DS]=Vs_DQ_ref_PI[QS]=0.0;

    // torque
    Te_max=0.0;
    Te_ref=0.0;
    Te=0.0;

    // flux
    Fs_rat=Vs_rat/we_rat;
    Fs_ref0=0.0;
    Fs_ref=0.0;
    inv_Fs_ref=0.0;
    Fs_dq[ds]=Fs_dq[qs]=0.0;
    Fs=0.0;
    inv_Fs=0.0;
    Fr_ref=0.0;
    Fr_ref0=0.0;
    inv_Fr_ref=0.0;
    Fr=0.0;
    inv_Fr=0.0;
    Fr_Err=0.0;
    Fr_ErrInt=0.0;

    // VVVF-Control
    Vs_ref=0.0;
    Freq_ref=0.0;
    Freq_slip=0.0;
    Freq_out=0.0;
    Slip=0.0;
    Power_core=0.0;
    Power_core_rat=0.0;
    Power_gap=0.0;
    Vs_IR_comp=0.0;
    del_Vs_comp=0.0;

    Pf=0.0;
    sgn_I_QS=0.0;
    Delta_wr=0.0;
    I_DS0_0=0.0;
    I_DS0=0.0;
    I_DS_err=0.0;

    GainUpdateTimer=0.0;
    AutoTuningFlag=0;
    LPF_Is_Square=0.0;
    LPF_Is=0.0;
    LPF_Re_Power=0.0;
    LPF_Vs_Square=0.0;
    Vs_Coeff_Leq_Req=0.0;
    Is_dq_ref[ds]=Is_dq_ref[qs]=0.0;
    Is_dq_ErrInt[ds]=Is_dq_ErrInt[qs]=0.0;

    Freq_set=0.0;
    Re_Power=0.0;
    Im_Power=0.0;
    ref_time = 0.0; //new

    S_rat=(we_rat-wr_rat)/we_rat;
    S_lin=(codeMotorPole/PI)*(S_rat* codeRateHz)/Te_rat;             // ==> V/f �젣�뼱 : �뒳由� 蹂댁긽
    Freq_slip_rat=S_rat* codeRateHz;
    IsD_Ref = 0.0;
    IsQ_Ref = 0.0;

    Vsw_ErrInt = 0.0;
    Vsd_ErrInt = 0.0;

    wr_ErrInt = 0.0;
    I_DS0_0 = 0.0;
}

//-----------------------------------
//  End of ParameterSect.c
//-----------------------------------

