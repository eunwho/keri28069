#include	<header.h>
#include	<extern.h>

int windPowerLoop(double cmd_ref)
{
    Uint32 RunTimeMsec=0 ;
    static unsigned long StartTimeMsec = 0 ;
    static unsigned long StartTimeMsec2 = 0 ;
    int iTemp;
    double data,dbtemp;
    int check;
    char str[40]={0};


	int LoopCtrl;
	int trip_code=0;
	int command;
	double ref_in0;

//	simple_scalar_control_variable_init();

	commonVariableInit();
	trip_code = HardwareParameterVerification();
	reference_in = cmd_ref;

	if( trip_code !=0 ) return trip_code;

	IER &= ~M_INT3;      // debug for PWM
	InitEPwm_ACIM_Inverter(); 	// debug
	EPwm1Regs.ETSEL.bit.INTEN = 1;    		            // Enable INT
	IER |= M_INT3;      // debug for PWM

	gRunFlag =1;
	strncpy(MonitorMsg,"INIT_RUN",20);
	gfRunTime = 0.0; 
	LoopCtrl = 1;		
	gMachineState = STATE_INIT_RUN;

	while(LoopCtrl == 1)
	{

	    RunTimeMsec = ulGetTime_mSec( StartTimeMsec);

	    if(RunTimeMsec > 1000){
	        StartTimeMsec = ulGetNow_mSec( );
	        // add wattHour and kWattHour
	        iTemp =  (int)(windEnergy / 3600.0 );
	        windEnergy -= iTemp * 3600.0;
	        wattHour += iTemp;

	        kWattHour += ( wattHour / 1000 );
	        wattHour = (wattHour % 1000);
	    }

	    // 10 min period save kWattHour and wattHour
        RunTimeMsec = ulGetTime_mSec( StartTimeMsec2);
        if(RunTimeMsec > 60000){
            StartTimeMsec2 = ulGetNow_mSec( );
            // add wattHour and kWattHour
            data = (double) ( wattHour);
            wattHour = (wattHour % 1000);
            check = SaveDataProc(CODE_kWattHour, data);
            if(check){
                load_scia_tx_mail_box(TripInfoNow.MSG); delay_msecs(20);
                snprintf( str,12,"\nCODE=%3d",TripInfoNow.CODE)    ;
                load_scia_tx_mail_box(str);delay_msecs(20);

                dbtemp = TripInfoNow.DATA;
                iTemp = (int)(floor(dbtemp +0.5));
                snprintf( str,13," \tDATA=%4d\n",iTemp);
                load_scia_tx_mail_box(str); delay_msecs(20);

            }

            data = (double) ( kWattHour);
            wattHour = (wattHour % 1000);
            check = SaveDataProc(CODE_kWattHour, data);
            if(check){
                load_scia_tx_mail_box(TripInfoNow.MSG); delay_msecs(20);
                snprintf( str,12,"\nCODE=%3d",TripInfoNow.CODE)    ;
                load_scia_tx_mail_box(str);delay_msecs(20);

                dbtemp = TripInfoNow.DATA;
                iTemp = (int)(floor(dbtemp +0.5));
                snprintf( str,13," \tDATA=%4d\n",iTemp);
                load_scia_tx_mail_box(str); delay_msecs(20);

            }
        }

	    Nop();
		trip_code = trip_check();
		if( trip_code !=0 ){
		    LoopCtrl = 0;
		}
		get_command( & command, & ref_in0);	            //
		if( command == CMD_START ) reference_in = ref_in0;

		switch( gMachineState )
		{
		case STATE_INIT_RUN:
			if( command == CMD_STOP){
                strncpy(MonitorMsg,"READY",20); gMachineState = STATE_READY; LoopCtrl= 0;
		    } else if( gfRunTime < 0.2 ){
				Freq_ref=0.0;	rpm_ref=0.0; reference_out = 0.0;
			} else {
			    if ( Vdc > UNDER_VOLT_LEVEL ){
			        strncpy(MonitorMsg,"RUN",20);
			        gMachineState = STATE_RUN;
			        reference_out = 0.5;
			    }
			}
			break;
		case STATE_RUN:
		    reference_in = 1.0;
            if ( Vdc < (UNDER_VOLT_LEVEL - 30.0) ){
                strncpy(MonitorMsg,"INIT_RUN",20);
                gMachineState = STATE_INIT_RUN;
                reference_out = 0.0;
            }else if ( command == CMD_NULL ){
			    ramp_proc(reference_in, & reference_out);
			} else if( command == CMD_STOP ) {
				strncpy(MonitorMsg,"GO_STOP",20); gMachineState = STATE_GO_STOP; reference_in = 0.0;
			} else if( command == CMD_SPEED_UP ){
				reference_in += 0.05;
				if( reference_in > 1.0 ) reference_in = 1.0;
			} else if( command == CMD_SPEED_DOWN ){
				reference_in -= 0.05;
				if( reference_in < -1.0 ) reference_in = -1.0;
			} else if( command == CMD_START ){
				ramp_proc(reference_in, & reference_out);
			}
			break;
		case STATE_GO_STOP:
			if( command == CMD_START ) {
				strncpy(MonitorMsg,"RUN",20); gMachineState = STATE_RUN;
				// reference_in = reference_out; 
			} else {
                strncpy(MonitorMsg,"READY",20);	gMachineState = STATE_READY; reference_out = Freq_out = 0.0; LoopCtrl = 0;
			}
			break;
		}
	}
	return trip_code;
}		

void windPowerCtrl()
{
    Freq_out = codeRateHz;
    // rpm_Coeff = 60.0 * inv_P_pair / PI_2;
    we = PI_2 * Freq_out;
    rpm = rpm_Coeff * we;   //  rpm = rpm_Coeff * wr

    theta += we * Ts;

    if (theta>PI)       theta-=PI_2;
    else if (theta<-PI) theta+=PI_2;

    SinTheta = sin(theta);
    CosTheta = cos(theta);

    Vs_ref = fabs( Vs_rat * reference_out );// debug

    Vs_dq_ref[ds] = Vs_ref * CosTheta;
    Vs_dq_ref[qs] = Vs_ref * SinTheta;

    Is_DQ[DS] =  CosTheta * Is_dq[ds] + SinTheta * Is_dq[qs];
    Is_DQ[QS] = -SinTheta * Is_dq[ds] + CosTheta * Is_dq[qs];

    Vs_DQ[DS] =  CosTheta * Vs_dq[ds] + SinTheta * Vs_dq[qs];
    Vs_DQ[QS] = -SinTheta * Vs_dq[ds] + CosTheta * Vs_dq[qs];
}
// End of file.
