#include	<header.h>
#include	<extern.h>


void initPmsmCtrl(){

    d_current_anti_windup=0.0;
    Id_err_ki_delay1=0.0;
    ud_ki_delay1=0.0;

    q_current_anti_windup=0.0;
    Iq_err_ki_delay1=0.0;
    uq_ki_delay1=0.0;

    speed_anti_windup=0.0;
    speed_err_ki_delay1=0.0;
    speed_ki_delay1=0.0;

    Freq_rat = codeRateHz;
    Vs_rat = sqrt(2.0)/sqrt(3.0) * codeRateVolt;
    we_rat = PI_2 * Freq_rat;

    Fs_B = Vs_rat / we_rat * Base_Flux_Coeff;
    wr_FilterPole = wr_FilterPoleCoeff * wn_wr;

    Kt = ( 3.0 / 2.0 ) * ( codeMotorPole/2.0 );
    inv_Kt = 1.0 / Kt;

    Kp_wr = ( Jm * 2.0 * wr_DampingRatio * wn_wr ) * (inv_Kt /Fs_B) * codeKpWrCoef;
    Ki_wr = ( Jm * wn_wr * wn_wr ) * ( inv_Kt / Fs_B) * codeKiWrCoef;
}

int pmsmCtrlLoop(double cmd_ref)
{
    int LoopCtrl;
    int iTripCode=0;
    int iCommand;
    double fReference;

    commonVariableInit();
    iTripCode = HardwareParameterVerification();
    initPmsmCtrl();

    if( iTripCode !=0 ) return iTripCode;

    IER &= ~M_INT3;      // debug for PWM
    InitEPwm_ACIM_Inverter();   // debug
    EPwm1Regs.ETSEL.bit.INTEN = 1;                      // Enable INT
    IER |= M_INT3;      // debug for PWM

    searchPosFlag = 1;
    Is_DQ_ref[DS] = -0.5* Is_rat;
    Is_DQ_ref[QS] = 0.0;

    gfRunTime = 0.0;
    gMachineState = STATE_INIT_RUN;
    while (gfRunTime < 3.0 ){
        iTripCode = trip_check();
        if( iTripCode !=0 ) break;
    }
    gMachineState = STATE_READY;
    posCountOrigin = EQep1Regs.QPOSCNT;

    searchPosFlag = 0; gRunFlag =1; gfRunTime = 0.0;
    while (gfRunTime < 0.2 ){
        iTripCode = trip_check();
        if( iTripCode !=0 ) break;
    }

    gfRunTime = 0.0; LoopCtrl = 1; gMachineState = STATE_INIT_RUN;
    while(LoopCtrl == 1)
    {
        if(gPWMTripCode != 0){
            iTripCode = gPWMTripCode; LoopCtrl = 0;
            break;
        }
        get_command(&iCommand,&fReference);
        monitor_proc();

        // if( iCommand == CMD_START)      reference_in = fReference;
        if( iCommand == CMD_STOP)  reference_in = 0.0;

        switch( gMachineState )
        {
        case STATE_RUN:
            strncpy(MonitorMsg," RUN ",20);
            if       (  iCommand == CMD_NULL )          ramp_proc( reference_in, &reference_out);
            else if(( iCommand == CMD_SPEED_UP1   ) && (reference_in <  3.0  )) reference_in += 0.01;
            else if(( iCommand == CMD_SPEED_UP   ) && (reference_in <  3.0  )) reference_in += 0.1;
            else if(( iCommand == CMD_SPEED_DOWN ) && ( reference_in > 0.01 )) reference_in -= 0.1;
            else if(  iCommand == CMD_STOP ) {
                reference_in = 0.0; gMachineState = STATE_GO_STOP;
            }
            else if(  iCommand == CMD_START ) ramp_proc( reference_in, &reference_out);
            else{
                reference_in = 0.0; gMachineState = STATE_GO_STOP;
            }
            break;

        case STATE_GO_STOP:
            if( iCommand == CMD_START ) { strncpy(MonitorMsg,"RUN ",20);
                gMachineState = STATE_RUN; reference_in = fReference;
            } else if( fabs( reference_out ) < 0.01 ){
                strncpy(MonitorMsg,"READY ",20);
                gMachineState = STATE_READY;
                commonVariableInit();
                LoopCtrl =0;
            } else {
                reference_in = 0.0;
                ramp_proc(reference_in, &reference_out);
            }
            break;
        }
    }
    return iTripCode;
}

int pmsmCtrlInitLoop( )
{
    int LoopCtrl;
    int trip_code=0;
    int command;
    double ref_in0;

    commonVariableInit();
    trip_code = HardwareParameterVerification();
    initPmsmCtrl();

    if( trip_code !=0 ) return trip_code;

    IER &= ~M_INT3;      // debug for PWM
    InitEPwm_ACIM_Inverter();   // debug
    EPwm1Regs.ETSEL.bit.INTEN = 1;                      // Enable INT
    IER |= M_INT3;      // debug for PWM

    gRunFlag =1;
    strncpy(MonitorMsg," RUN ",20);
    gfRunTime = 0.0;
    LoopCtrl = 1;

    Is_DQ_ref[DS] = -0.5* Is_rat;
    Is_DQ_ref[QS] = 0.0;

    searchPosFlag = 1;

    gMachineState = STATE_INIT_RUN;

    while( (LoopCtrl == 1) && (gfRunTime < 5.0 )){
        trip_code = trip_check();
        if( trip_code !=0 ) LoopCtrl = 0;

        get_command( & command, & ref_in0);             //
        switch( gMachineState )
        {
        case STATE_RUN:
            strncpy(MonitorMsg," RUN ",20);
            if( command == CMD_STOP ) {
                gMachineState = STATE_READY;
                reference_out = Freq_out = 0.0;
                ePwmPortOff( );
                commonVariableInit( );
                gMachineState = STATE_GO_STOP; reference_in = 0.0;
            }
            break;
        }
    }

    if( gfRunTime >= 3.0 ){
        posCountOrigin = EQep1Regs.QPOSCNT;
        gMachineState = STATE_READY;
        reference_out = Freq_out = 0.0;
        ePwmPortOff( );
        commonVariableInit( );
        searchPosFlag = 0;
    }
    return trip_code;
}

//=============================================
//
//
//=============================================
#define pmsmVsKi 100.0

inline void pmsmCalcMaxVI(){

    Is_DQ[DS] = CosTheta*Is_dq[ds] + SinTheta*Is_dq[qs];
    Is_DQ[QS] = -SinTheta*Is_dq[ds] + CosTheta*Is_dq[qs];
    Isd_Square = Is_DQ[DS] * Is_DQ[DS];
    Isq_Square = Is_DQ[QS] * Is_DQ[QS];
    Is_Square = Isd_Square + Isq_Square;
    Is_Scalar = sqrt(Is_Square);
    // Is_Scalar = Is_mag;          // debug 2020.0202

    Vs_DQ[DS] = CosTheta*Vs_dq[ds] + SinTheta*Vs_dq[qs];
    Vs_DQ[QS] = -SinTheta*Vs_dq[ds] + CosTheta*Vs_dq[qs];
    Vsd_Square = Vs_DQ[DS] * Vs_DQ[DS];
    Vsq_Square = Vs_DQ[QS] * Vs_DQ[QS];
    Vs_Square = Vsd_Square + Vsq_Square;
    lpfVsIn[0] = sqrt(Vs_Square);
    lpf2nd( lpfVsIn, lpfVsOut, lpfVsK);
    Vs_Scalar = lpfVsOut[0];
}


inline double d_axis_current_controller( double Id_ref)
{
    double Id_err, ud_kp, ud_ki, temp_Vd, Vd_ref, Vd_max;

    Id_err = Id_ref - Is_DQ[DS];
    ud_kp = codeKpIs * Id_err;
    //Id_err_ki = Id_err- d_current_anti_windup;
    Is_DQ_ErrInt[DS] = Id_err - d_current_anti_windup;
    ud_ki = 0.5 * codeKpIs * Ts * (Is_DQ_ErrInt[DS] + Id_err_ki_delay1 ) + ud_ki_delay1; //'Bilinear, s=(2/Ts)*((z+1)/(z-1))

    temp_Vd = ud_kp+ud_ki;

    Vd_max = Vs_max;
    if (temp_Vd >= Vd_max)      Vd_ref =  Vd_max;
    else if(temp_Vd<=-Vd_max)   Vd_ref = -Vd_max;
    else                        Vd_ref =  temp_Vd;

    ud_ki_delay1 = ud_ki;
    Id_err_ki_delay1 = Is_DQ_ErrInt[DS];
    d_current_anti_windup = (temp_Vd -Vd_ref);
    return Vd_ref;
}

inline double q_axis_current_controller(double Iq_ref)
{
    double Iq_err, Iq_err_ki,uq_kp, uq_ki, temp_Vq, Vq_ref,Vq_max;

    Iq_err = Iq_ref - Is_DQ[QS];
    uq_kp = codeKpIs * Iq_err;

    Iq_err_ki = Iq_err-q_current_anti_windup;

    uq_ki = 0.5 * codeKiIs * Ts * (Iq_err_ki + Iq_err_ki_delay1 ) + uq_ki_delay1; //'Bilinear, s=(2/Ts)*((z+1)/(z-1))
    temp_Vq = uq_kp+uq_ki;

    Vq_max = 2.0 * Vs_max;
    if (temp_Vq >= Vq_max)      Vq_ref =  Vq_max;
    else if(temp_Vq<=-Vq_max)   Vq_ref = -Vq_max;
    else                        Vq_ref =  temp_Vq;

    uq_ki_delay1 = uq_ki;
    Iq_err_ki_delay1 = Iq_err_ki;
    q_current_anti_windup = (temp_Vq - Vq_ref);
    return Vq_ref;
}


void pmsmSpeedCtrl(){

    double speed_err_ki, temp2_Tref, Iq_max;

    Iq_max = 0.5 * Is_rat;

    wr_ref = wr_rat * reference_out;
    wr_err = wr_ref-wr;

    speed_err_ki = wr_err - speed_anti_windup;

    wr_ErrInt = 0.5 * Ki_wr * Ts * (speed_err_ki + speed_err_ki_delay1) + speed_ki_delay1;

    temp2_Tref = Kp_wr * wr_err + wr_ErrInt;

    Iq_max = 0.5 * Is_rat;

    if      (temp2_Tref >  Iq_max ) Is_DQ_ref[QS] =  Iq_max;
    else if (temp2_Tref < -Iq_max ) Is_DQ_ref[QS] = -Iq_max;
    else                             Is_DQ_ref[QS] =  temp2_Tref;

    speed_ki_delay1 = wr_ErrInt;
    speed_err_ki_delay1 = speed_err_ki;
    speed_anti_windup = (temp2_Tref - Is_DQ_ref[QS]);

    Is_DQ_ref[DS] = 0;
    pmsmCtrl( );
}

/*
void pmsmSpeedCtrl( ){
    double isqRef;
    double IntegralLimit;

    wr_ref = wr_rat * reference_out;
    wr_err = wr_ref-wr;

    wr_ErrInt += 0.5 * Ki_wr*wr_err * Ts;

    IntegralLimit = 0.5 * Kp_wr*fabs(K_Damp_wr*wr_ref-wr) + 0.5 * Is_rat;

    if      (wr_ErrInt >  IntegralLimit) wr_ErrInt =  IntegralLimit;
    else if (wr_ErrInt < -IntegralLimit) wr_ErrInt = -IntegralLimit;

    lpfIsqIn[0] = Kp_wr * ( K_Damp_wr * wr_ref - wr ) * inv_P_pair + wr_ErrInt;
    lpf2nd( lpfIsqIn, lpfIsqOut, lpfIsqK);

    Is_DQ_ref[QS] = lpfIsqOut[0];
    Is_DQ_ref[DS] = 0;
    pmsmCtrl( );
}
*/

void pmsmCtrl()
{
    double theta;
    Vs_max=0.57735*Vdc;   // 1.0/sqrt(3.0)=0.57735027
    // Vs_max = Vs_rat * codeFwCoef1;   // 1.0/sqrt(3.0)=0.57735027

    theta = (searchPosFlag ) ? 0.0 : theta_m;

    CosTheta = cos(theta);
    SinTheta = sin(theta);

    pmsmCalcMaxVI();

    Vs_DQ_ref[DS] = d_axis_current_controller(Is_DQ_ref[DS]);
    Vs_DQ_ref[QS] = q_axis_current_controller(Is_DQ_ref[QS]);

    Vs_dq_ref[ds] = (CosTheta*Vs_DQ_ref[DS] - SinTheta*Vs_DQ_ref[QS]);
    Vs_dq_ref[qs] = (SinTheta*Vs_DQ_ref[DS] + CosTheta*Vs_DQ_ref[QS]);

    Freq_out    = wr_m * inv_PI_2;
    rpm         = rpm_Coeff * wr_m;
    // Te          = Kt * Fs * Is_DQ[QS];
    Te          = Kt * Is_DQ[DS] * Is_DQ[QS];       // debug
    P_total     = Te * wr_m;
}
// end of pmsm.c
