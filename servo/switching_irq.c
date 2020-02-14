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
    case 3: fieldWeakenVoltageLoopCtrl( );   break;
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

    if( codeProtectOff < 0.5 ) {
        if(gPWMTripCode == 0 ) gPWMTripCode = CheckIGBTFault();
        if(gPWMTripCode == 0 ) gPWMTripCode = CheckOverCurrent();

        if((gPWMTripCode == 0 ) && EX_DIO_INPUT1 ){
            gPWMTripCode = ERR_EXT_TRIP; trip_recording( ERR_EXT_TRIP, 0.0,"ERR EXT TRIP");
        }
        if(gPWMTripCode){
            EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT;
            EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT;
            EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT;
            ePwmPortOff( );
            goto _PWM_TRIP;
        }
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
        ePwmPortOff( );
        startCount =0;
        pwmOn = 0;
       EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT ;
       EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT;
       EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT ;
         break;
    case STATE_INIT_RUN:
        if( startCount < 10){
            startCount ++;
            pwmOn = 0;
            EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT ;
            EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT;
            EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT ;
        } else {
            if( pwmOn == 0  ){
                pwmOn = 1;
                ePwmEnable();
                EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT >> 1 ;
                EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT >> 1;
                EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT >> 1;
                gMachineState = STATE_RUN;
                reference_in = codeStartRef;
            }
        }
        break;
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

            //EPwm1Regs.CMPA.half.CMPA = DutyCount[u];	// for keriInv
            //EPwm2Regs.CMPA.half.CMPA = DutyCount[v];
            //EPwm3Regs.CMPA.half.CMPA = DutyCount[w];
            EPwm3Regs.CMPA.half.CMPA = DutyCount[u];		// for powerPack
            EPwm2Regs.CMPA.half.CMPA = DutyCount[v];
            EPwm1Regs.CMPA.half.CMPA = DutyCount[w];
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

void InitEPwm_ACIM_Inverter()
{  
	EPwm1Regs.ETSEL.bit.INTEN = 0;    		        // Enable INT
	MAX_PWM_CNT = (Uint16)( ( F_OSC * DSP28_PLLCR / codePwmFreq ) * 0.5 * 0.5 * 0.5 * 0.5);
	inv_MAX_PWM_CNT = 1.0 / MAX_PWM_CNT;
//--- PWM Module1
    EPwm1Regs.TBCTR = 0x0000;
	EPwm1Regs.TBPRD                 =  MAX_PWM_CNT;			// Set timer period
	EPwm1Regs.TBPHS.half.TBPHS      = 0x0000; // Phase is 0
    EPwm1Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN;  //
    EPwm1Regs.TBCTL.bit.PHSEN       = TB_DISABLE;   // 2018.07.19 change TB_ENABLE
    EPwm1Regs.TBCTL.bit.PRDLD       = TB_SHADOW;    // 2017.09.05
    EPwm1Regs.TBCTL.bit.SYNCOSEL    = TB_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;	// Load registers every ZERO
	EPwm1Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;
	EPwm1Regs.AQCTLA.bit.CAU        = AQ_CLEAR;
	EPwm1Regs.AQCTLA.bit.CAD        = AQ_SET;
	EPwm1Regs.DBCTL.bit.OUT_MODE 	= DB_FULL_ENABLE;
	EPwm1Regs.DBCTL.bit.POLSEL 	    = DB_ACTV_LOC;
	EPwm1Regs.DBRED                 = DEAD_TIME_COUNT; // debug set to 4usec
	EPwm1Regs.DBFED                 = DEAD_TIME_COUNT;
//--- Set PWM2
	EPwm2Regs.TBPRD                 =  MAX_PWM_CNT;				// Set timer period
    EPwm2Regs.TBPHS.half.TBPHS      = 0x0000;            // Phase is 0
    EPwm2Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN;      // Count up
    EPwm2Regs.TBCTL.bit.PHSEN       = TB_ENABLE;
    EPwm2Regs.TBCTL.bit.PRDLD       = TB_SHADOW;          // 2017.09.05
    EPwm2Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm2Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;
    EPwm2Regs.AQCTLA.bit.CAU        = AQ_CLEAR;
    EPwm2Regs.AQCTLA.bit.CAD        = AQ_SET;
	EPwm2Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;
	EPwm2Regs.DBCTL.bit.POLSEL      = DB_ACTV_LOC;
	EPwm2Regs.DBRED                 = DEAD_TIME_COUNT;
	EPwm2Regs.DBFED                 = DEAD_TIME_COUNT;
//Set PWM3 
	EPwm3Regs.TBPRD                 =  MAX_PWM_CNT;			// Set timer period
    EPwm3Regs.TBPHS.half.TBPHS      = 0x0000;               // Phase is 0
	EPwm3Regs.TBCTL.bit.CTRMODE 	= TB_COUNT_UPDOWN; 	// Count up
	EPwm3Regs.TBCTL.bit.PHSEN 		= TB_ENABLE;
    EPwm3Regs.TBCTL.bit.PRDLD       = TB_SHADOW;          // 2017.09.05
    EPwm3Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm3Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;
    EPwm3Regs.AQCTLA.bit.CAU        = AQ_CLEAR;
    EPwm3Regs.AQCTLA.bit.CAD        = AQ_SET;
    EPwm3Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;
    EPwm3Regs.DBCTL.bit.POLSEL      = DB_ACTV_LOC;
	EPwm3Regs.DBRED 				= DEAD_TIME_COUNT;
	EPwm3Regs.DBFED 				= DEAD_TIME_COUNT;

//Set PWM4 
	EPwm4Regs.TBPRD =  MAX_PWM_CNT;			// Set timer period

	EPwm4Regs.TBCTL.bit.PHSDIR 		= TB_UP;				// Count up
	EPwm4Regs.TBCTL.bit.CTRMODE 	= TB_COUNT_UPDOWN; 	// Count up
	EPwm4Regs.TBCTL.bit.HSPCLKDIV 	= TB_DIV1;		// 
	EPwm4Regs.TBCTL.bit.CLKDIV 		= TB_DIV1;			// Slow so we can observe on the scope

	EPwm4Regs.TBPHS.half.TBPHS 		= 0x0000;           	// Phase is 0
	EPwm4Regs.TBCTL.bit.PHSEN 		= TB_ENABLE; 
	EPwm4Regs.TBCTL.bit.SYNCOSEL 	= TB_SYNC_IN;        	

	EPwm4Regs.CMPA.half.CMPA 		= MAX_PWM_CNT;

	EPwm4Regs.AQCTLA.bit.CAU 		= AQ_SET;	 
	EPwm4Regs.AQCTLA.bit.CAD 		= AQ_CLEAR;

	EPwm4Regs.DBCTL.bit.OUT_MODE 	= DB_FULL_ENABLE;
	EPwm4Regs.DBCTL.bit.POLSEL 		= DB_ACTV_HIC;

	EPwm4Regs.DBCTL.bit.IN_MODE 	= DBA_ALL;
	EPwm4Regs.DBRED 				= DEAD_TIME_COUNT;
	EPwm4Regs.DBFED 				= DEAD_TIME_COUNT;
	EPwm4Regs.ETSEL.bit.INTEN 		= 0;                  

    EPwm1Regs.CMPA.half.CMPA        = MAX_PWM_CNT>>1;
    EPwm2Regs.CMPA.half.CMPA        = MAX_PWM_CNT>>1;
    EPwm3Regs.CMPA.half.CMPA        = MAX_PWM_CNT>>1;

	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;	// Select INT on Zero event
	EPwm1Regs.ETPS.bit.INTPRD = 1;   // Generate interrupt on the 1st event
	EPwm1Regs.ETCLR.bit.INT = 1;     //  

//	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;// Enable SOCA from ePWM to start SEQ1
//	AdcRegs.ADCTRL3.all = 0x00FE;  // Power up bandgap/reference/ADC circuits

	EPwm1Regs.ETSEL.bit.SOCAEN = 1;   // Enable SOC on A group
	EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;//
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;        // Generate pulse on 1st event

	PieCtrlRegs.PIEIER3.all = M_INT1;	// ePWM
    // PieCtrlRegs.PIEIER3.bit.INTx1 = PWM1_INT_ENABLE;
}

 // end of switching_irq.c 

