// FILE		: switching_irq.c
// Company  : Eunwho Power Electonics
// date		: 2018.0608	by soonkil jung

#include        <header.h>
#include        <extern.h>


#define testAngle       0.0052359867            // 3.141592 / 600

void MotorControlProc( )
{
    int temp;

    temp = (int)(floor(codeMotorCtrlMode+0.5));
    switch( temp )
    {
    case 0: vf_simple_control(); break;
    case 1: slip_comp_scalar_ctrl();break;
    case 3: SL_SpeedCntl_SFRF( );   break;
    case 4: SL_TorqueCntl_SFRF( );  break;
    case 5:
        switch(AutoTuningFlag)
        {
        case 0: Vs_dq_ref[ds] = 0.0; Vs_dq_ref[qs] = 0.0; break;
        case ID_AT_LEQ_REQ: estim_ReqLeq_pwm ( );   break;
        case ID_AT_RS:  estim_Rs_pwm( );            break;
        case ID_AT_LS:  estim_Ls_pwm( );            break;
        default:    Vs_dq_ref[ds] = 0.0; Vs_dq_ref[qs] = 0.0; break;
        }
        break;
    }
}

interrupt void MainPWM(void)
{
    static int sampleScopeCount = 0;
    static int pwmOn = 0;
    static int startCount = 0;

    PERIOD_PWM_IRQ_SET;     // channel 1
 //  IGBT Trip check and EMG_INPUT

/*
    VoltageEstimation();
    MotorControlProc( );
    SpaceVectorModulation(Vs_dq_ref);

    goto _PWM_TRIP;
*/

    if(gPWMTripCode == 0 ){
        //--- check pwm error
        if( TRIP_UH == 0){
            trip_recording( ERR_IGBT_UH, 0.0,"Trip UH"); gPWMTripCode = ERR_IGBT_UH;
        } else if( TRIP_UL == 0){
            trip_recording( ERR_IGBT_UL, 0.0,"Trip UL"); gPWMTripCode = ERR_IGBT_UL;
        } else if( TRIP_VH == 0){
            trip_recording( ERR_IGBT_VH, 0.0,"Trip VH"); gPWMTripCode = ERR_IGBT_VH;
        } else if( TRIP_VL == 0){
            trip_recording( ERR_IGBT_VL, 0.0,"Trip VL"); gPWMTripCode = ERR_IGBT_VL;
        } else if( TRIP_WH == 0){
            trip_recording( ERR_IGBT_WH, 0.0,"Trip WH"); gPWMTripCode = ERR_IGBT_WH;
        } else if( TRIP_WL == 0){
            trip_recording( ERR_IGBT_WL, 0.0,"Trip WL"); gPWMTripCode = ERR_IGBT_WL;
        } else if( TRIP_DB == 0){
            trip_recording( ERR_IGBT_DB, 0.0,"Trip DB"); gPWMTripCode = ERR_IGBT_DB;
        }
    }

    if ( gMachineState != STATE_POWER_ON)  gPWMTripCode = tripCheckPWM();

    if(gPWMTripCode){
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT;
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT;
        // PWM_OFF( );
        ePwmPortOff( );
        goto _PWM_TRIP;
    }

    switch(gMachineState)
    {

    case STATE_TRIP:
        ePwmPortOff( );
        startCount = 0;
        pwmOn =0;
        break;
    case STATE_READY:
    case STATE_POWER_ON:
        startCount =0;
        pwmOn = 0;
       EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT ;
       EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT;
       EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT ;
         break;
    case STATE_INIT_RUN:
        if( startCount < 30){
            startCount ++;
            pwmOn = 0;
            break;
        } else {
            if( pwmOn == 0  ){
                pwmOn = 1;
                ePwmEnable();
                EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1 ;
                EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
                EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT >>1;
            }
        }
    case STATE_RUN:
    case STATE_GO_STOP:
    case STATE_WAIT_BREAK_OFF:
        if(gPWMTripCode !=0){
            gTripSaveFlag = 1; // for Trip History Save to EEPROM in Out irq
            EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
            EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
            EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        } else{
            VoltageEstimation();
            MotorControlProc( );
            SpaceVectorModulation(Vs_dq_ref);

            EPwm1Regs.CMPA.half.CMPA = DutyCount[u];
            EPwm2Regs.CMPA.half.CMPA = DutyCount[v];
            EPwm3Regs.CMPA.half.CMPA = DutyCount[w];
        }
        break;
    default:
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT;
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT;
        break;
    }

_PWM_TRIP:

    if( sendAdcDataFlag == 0 )
    {
        if( sampleScopeCount < scopeLoopCount )
        {
            sampleScopeCount ++;
        }
        else
        {
            sampleScopeCount = 0;
            scopeData[0][scopeCount].INTEGER = (int)( ( * scopePoint[scopePointCh1]-codeScopeOffsetCh1) * invCodeScopeScaleCh1 * 204.8 + 2048);
            scopeData[1][scopeCount].INTEGER = (int)( ( * scopePoint[scopePointCh2]-codeScopeOffsetCh2) * invCodeScopeScaleCh2 * 204.8 + 2048);
            scopeData[2][scopeCount].INTEGER = (int)( ( * scopePoint[scopePointCh3]-codeScopeOffsetCh3) * invCodeScopeScaleCh3 * 204.8 + 2048);
            scopeData[3][scopeCount].INTEGER = (int)( ( * scopePoint[scopePointCh4]-codeScopeOffsetCh4) * invCodeScopeScaleCh4 * 204.8 + 2048);
            if ( scopeCount < ( SCOPE_MAX_NUMBER-1 )) scopeCount ++;
            else scopeCount = 0 ;
        }
    }

    EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    PERIOD_PWM_IRQ_CLEAR;     // channel 1
}

 // end of switching_irq.c 

