#include	<header.h>
#include	<extern.h>

int vf_loop_control(double cmd_ref)
{
	int LoopCtrl;
	int iTripCode=0;
	int iCommand;
	double fReference;

//	simple_scalar_control_variable_init();

	commonVariableInit();
	iTripCode = HardwareParameterVerification();

	reference_out =0.0; Is_mag_rms =0.0, rpm =0.0;
	reference_in = cmd_ref;

	if( iTripCode !=0 ) return iTripCode;

	IER &= ~M_INT3;      // debug for PWM
	InitEPwm_ACIM_Inverter(); 	// debug
	EPwm1Regs.ETSEL.bit.INTEN = 1;    		            // Enable INT
	IER |= M_INT3;      // debug for PWM

//	initPmsmCtrl();
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

void vf_simple_control()
{
    Freq_out = codeRateHz * reference_out;
    we = PI_2 * Freq_out;
    rpm = rpm_Coeff * we;   //  rpm = rpm_Coeff * wr

    theta += we * Ts;       //�쉶�쟾諛⑺뼢 蹂��솚 �젙諛⑺뼢�쓣�븣 +, �뿭諛⑺뼢�쉶�쟾�씪�븣 - �빐以꾧쾬

    if (theta > PI)       theta-=PI_2;
    else if (theta<-PI) theta+=PI_2;

    SinTheta = sin(theta);
    CosTheta = cos(theta);

    if( reference_out > 1.0 ){
        Vs_ref = fabs( Vs_rat / reference_out );// debug 2019.1002
    } else {
        Vs_ref = fabs( Freq_out / codeRateHz * Vs_rat );
    }

    Vs_dq_ref[ds] = Vs_ref * CosTheta;
    Vs_dq_ref[qs] = Vs_ref * SinTheta;

    Is_DQ[DS] =  CosTheta * Is_dq[ds] + SinTheta * Is_dq[qs];
    Is_DQ[QS] = -SinTheta * Is_dq[ds] + CosTheta * Is_dq[qs];
    Vs_DQ[DS] =  CosTheta * Vs_dq[ds] + SinTheta * Vs_dq[qs];
    Vs_DQ[QS] = -SinTheta * Vs_dq[ds] + CosTheta * Vs_dq[qs];
}


void slip_comp_scalar_ctrl()
{
   double   Es_m;
   double   sgn_freq;
   double   Det_slip;
   double   Det_emf;

   CosDeltaTheta=cos(we*Ts);
   SinDeltaTheta=sin(we*Ts);
   Us_dq[ds]=Vs_dq[ds]*CosDeltaTheta + Vs_dq[qs]*SinDeltaTheta;
   Us_dq[qs]=-Vs_dq[ds]*SinDeltaTheta + Vs_dq[qs]*CosDeltaTheta;
   Vs_dq[ds]=Us_dq[ds];
   Vs_dq[qs]=Us_dq[qs];

//   if ( gfRunTime < gExcitationTime)      //
   if( gMachineState == STATE_INIT_RUN){
      Freq_ref = Freq_out= reference_out= we = theta = SinTheta=0.0;
      CosTheta=1.0;
      Vs_ref = VF_Vs_Coeff_TrqBoost * Vs_rat;
   }
   else
   {
      Freq_ref = Freq_rat * reference_out;
      if (Freq_ref > VF_Freq_TrqBoost)
      {
         if (Freq_ref >= 0.0)   sgn_freq =  1.0;
         else                  sgn_freq = -1.0;

         Slip = fabs(Freq_slip)*inv_Freq_rat;
         Power_core_rat = codeRatePower*(1.0-codeRateEffiency/(1.0-S_rat))-1.5*Is_rat*Is_rat*VF_Rs;
         Power_core=0.5*( (1.0+Slip)/(1+S_rat)*(Freq_out*inv_Freq_rat) + (1.0+Slip*Slip)/(1.0+S_rat*S_rat)*(Freq_out*inv_Freq_rat)*(Freq_out*inv_Freq_rat) )*Power_core_rat;
         LPF1(Ts,VF_Slip_Comp_FilterPole,1.5*(Vs_dq[ds]*Is_dq[ds]+Vs_dq[qs]*Is_dq[qs] - VF_Rs_ThermalCoeff*VF_Rs*Is_mag*Is_mag)-Power_core,&Power_gap);
         Det_slip = Freq_ref*Freq_ref + S_lin*Power_gap;

         if (Det_slip < 0.0)
               LPF1(Ts,VF_Slip_Comp_FilterPole,-0.5*sqrt(fabs(S_lin*Power_gap)),&Freq_slip);
         else   LPF1(Ts,VF_Slip_Comp_FilterPole,0.5*(sqrt(Det_slip)-fabs(Freq_ref)),&Freq_slip);

         if (Freq_slip>2.0*Freq_slip_rat)         Freq_slip=2.0*Freq_slip_rat;
         else if (Freq_slip<-2.0*Freq_slip_rat)   Freq_slip=-2.0*Freq_slip_rat;

         Freq_out=Freq_ref + sgn_freq*Freq_slip;

      }
      else
      {
         Freq_out=Freq_ref;
         Power_gap=0.0;
         Freq_slip=0.0;
      }

      we=PI_2*Freq_out;
      theta+=we*Ts;

      if (theta>PI)         theta-=PI_2;
      else if (theta<-PI)   theta+=PI_2;

      SinTheta=sin(theta);      CosTheta=cos(theta);

      Vs_max=0.57735*Vdc;
      Es_m=VF_Fs_Coeff*fabs(Freq_out)*inv_Freq_rat*Vs_rat;
      if (Es_m>Vs_max)   Es_m=Vs_max;

      Is_DQ[DS]= CosTheta*Is_dq[ds] + SinTheta*Is_dq[qs];
      Is_DQ[QS]=-SinTheta*Is_dq[ds] + CosTheta*Is_dq[qs];

      Det_emf=(Es_m*Es_m)-(VF_Rs*Is_DQ[QS])*(VF_Rs*Is_DQ[QS]);  //sqrt占쎈툧占쎌벥 占쎌벉占쎈땾占쎈연�겫占썼�곌퀣沅�
      if ( (Det_emf>0.0) && (fabs(Freq_out)>VF_Freq_TrqBoost) )
            LPF1(Ts,VF_IR_Comp_FilterPole,0.9*(VF_Rs*Is_DQ[DS]+sqrt(Det_emf)-Es_m),&Vs_IR_comp);
      else   LPF1(Ts,VF_IR_Comp_FilterPole,VF_Vs_Coeff_TrqBoost*Vs_rat,&Vs_IR_comp);

      if (Is_mag>Is_max)
      {
         del_Vs_comp=(2.0*Vs_rat*inv_Is_rat)*(Is_mag-Is_max);

         if (del_Vs_comp>0.2*Vs_rat)         del_Vs_comp=0.2*Vs_rat;
         else if (del_Vs_comp<-0.2*Vs_rat)   del_Vs_comp=-0.2*Vs_rat;
      }
      else   del_Vs_comp=0.0;

      // 筌ㅼ뮇伊� 占쎌읈占쎈릍 筌뤿굝議�
      Vs_ref = Es_m + Vs_IR_comp - del_Vs_comp;      // IR癰귣똻湲�, 占쎌읈�몴�꼹寃뺞묾占� 占쎌젫占쎈립
      if (Vs_ref>Vs_max)   Vs_ref=Vs_max;
   }
   // �빊�뮆�젾 占쎌읈占쎈릍
   Vs_dq_ref[ds]=Vs_ref*CosTheta + VF_DeadTimeGain*(Vs_dq_ref[ds]-Vs_dq[ds]);
   Vs_dq_ref[qs]=Vs_ref*SinTheta + VF_DeadTimeGain*(Vs_dq_ref[qs]-Vs_dq[qs]);

   rpm = 60 * Freq_out * inv_P_pair ;
}
// End of file.
