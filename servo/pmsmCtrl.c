#include    <header.h>
#include    <extern.h>

void servoCtrlInit(void)
{

    Id_err_ki = 0.0;
    Id_err_ki_delay1 = 0.0;

    ud_ki = 0.0;
    ud_ki_delay1 = 0.0;
    Id_ref = 0.0;

    Iq_err_ki = 0.0;
    Iq_err_ki_delay1 = 0.0;
    uq_ki = 0.0;
    uq_ki_delay1 = 0.0;
    Iq_ref = 0.0;

    speed_err_ki = 0.0;
    speed_err_ki_delay1 = 0.0;
    uspeed_ki = 0.0;
    uspeed_ki_delay1 = 0.0;

    Is_rat=sqrt(2.0)*codeRateCurrent;
    Is_max = Is_rat * 1.0;
    inv_Is_rat=1.0/Is_rat;
    Vs_DQ_max[QS] = Is_max;
}

#define codeMotorPole   2.0

int servoParaVerification(){

    Vs_rat= ROOT2 * INV_ROOT3 * codeRateVolt;
    Is_rat=codeRatePower * INV_ROOT3 / codeRateVolt;
    inv_Is_rat=1.0/Is_rat;
    we_rat =PI_2*codeMotorPole*codeRateRpm/120.0;
    wr_rat = we_rat;
    wm_rat = wr_rat * ( 2.0 / codeMotorPole );
    Te_rat= codeRatePower / wm_rat;
    Kt=(3.0/2.0)*(codeMotorPole/2.0);
    inv_Kt=1.0/Kt;
    P_pair=(codeMotorPole/2.0);
    inv_P_pair=1.0/P_pair;
    rpm_Coeff=60.0*inv_P_pair/PI_2;

    Fs_rat=Vs_rat/we_rat;

    inv_Ts = codePwmFreq;
    Ts = 1.0 / codePwmFreq; // debug

    Is_max = Is_rat * Is_Max_Coeff ;    // added 2009.11.01
    OverCurLimit = Is_max *2;           // added 2009.11.01  _debug
    return 0;
}
//void position_controller(void)
void servoPosiCtrl()
{
    float temp_speed;

    pos_ref_gen();
    POS_ERR = POS_REF - POS_REAL;  // [rad]

    temp_speed =  code_kpPosi * POS_ERR;

    if      (temp_speed >= MAX_SPEED)   SPEED_REF = MAX_SPEED;
    else if (temp_speed <=-MAX_SPEED)	SPEED_REF = -MAX_SPEED;
    else                                SPEED_REF = temp_speed;

    if (profile_gen_time <= prof_t3)    SPEED_REF = SPD_REF_PLC;
}

int servoPosiLoop( void )
{
    int LoopCtrl;
    int trip_code=0;
    int command;
    double ref_in0,temp_speed;

    trip_code = servoParaVerification();
    if( trip_code !=0 ) return trip_code;

    servoCtrlInit( );
    IER &= ~M_INT3;      // debug for PWM
    InitEPwm_ACIM_Inverter();   // debug
    EPwm1Regs.ETSEL.bit.INTEN = 1;                      // Enable INT
    IER |= M_INT3;      // debug for PWM

    gRunFlag =1;
    strncpy(MonitorMsg,"INIT_RUN",20);
    gfRunTime = 0.0;
    LoopCtrl = 1;
    gMachineState = STATE_INIT_RUN;

    while(LoopCtrl == 1) {
        Nop();
        trip_code = trip_check();
        if( trip_code !=0 ) return trip_code;

        get_command( & command, & ref_in0);             //

        switch( gMachineState ) {
        case STATE_INIT_RUN:
            if( command == CMD_STOP){
                strncpy(MonitorMsg,"READY",20); gMachineState = STATE_READY; LoopCtrl= 0;
            } else if( gfRunTime < 5.0 ){
                Iq_ref = 0.0;
                Id_ref = -0.5 * Is_rat;
                theta = 0.0;
            } else{
                POS_INIT_FLAG = 1;
                strncpy(MonitorMsg,"RUN",20); gMachineState = STATE_RUN;
            }
            break;
        case STATE_RUN:
            if( command == CMD_NULL ){
                // ramp_proc(reference_in, & reference_out);
                pos_ref_gen();
                POS_ERR = POS_REF-POS_REAL;  // [rad]
               // POS_ERR = 0.017453289*(POS_REF-POS_REAL);  //'(2*pi)/360 [rad]
                temp_speed =  code_kpPosi * POS_ERR;
                if(temp_speed>=MAX_SPEED)           SPEED_REF = MAX_SPEED;
                else if (temp_speed<=-MAX_SPEED)    SPEED_REF = -MAX_SPEED;
                else                                SPEED_REF = temp_speed;

                if (profile_gen_time <= prof_t3)    SPEED_REF = SPD_REF_PLC;

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
            } else if ((fabs(reference_out) <= code_start_ref )){
                strncpy(MonitorMsg,"READY",20); gMachineState = STATE_READY; reference_out = Freq_out = 0.0; LoopCtrl = 0;
            } else {
                reference_in = 0.0;
                ramp_proc(reference_in, &reference_out);
            }
            break;
        }
    }
    return trip_code;
}

int servoSpeedLoop( void )
{
    int LoopCtrl;
    int trip_code=0;
    int command;
    double ref_in0;

    servoCtrlInit( );
    trip_code = servoParaVerification();
    if( trip_code !=0 ) return trip_code;

    IER &= ~M_INT3;      // debug for PWM
    InitEPwm_ACIM_Inverter();   // debug
    EPwm1Regs.ETSEL.bit.INTEN = 1;                      // Enable INT
    IER |= M_INT3;      // debug for PWM

    gRunFlag =1;
    strncpy(MonitorMsg,"INIT_RUN",20);
    gfRunTime = 0.0;
    LoopCtrl = 1;
    gMachineState = STATE_INIT_RUN;

    while(LoopCtrl == 1)
    {
        trip_code = trip_check();
        if( trip_code !=0 ) return trip_code;

        get_command( & command, & ref_in0);             //
        if( command == CMD_START ) reference_in = ref_in0;

        switch( gMachineState )
        {
        case STATE_INIT_RUN:
            if( command == CMD_STOP){
                strncpy(MonitorMsg,"READY",20); gMachineState = STATE_READY; LoopCtrl= 0;
            } else if( gfRunTime < 2.0 ){
                Id_ref = -0.5 * Is_rat; // CURRENT_RATED ;
                Iq_ref = 0.0;
                theta_m = 0;
                Init_EQep(); // qep count = 0;
                POSCNT_old = 0;
            } else{
                strncpy(MonitorMsg,"RUN",20); gMachineState = STATE_RUN;
            }
            break;
        case STATE_RUN:
            if( command == CMD_NULL ){
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
            } else if ((fabs(reference_out) <= code_start_ref )){
                strncpy(MonitorMsg,"READY",20); gMachineState = STATE_READY; reference_out = Freq_out = 0.0; LoopCtrl = 0;
            } else {
                reference_in = 0.0;
                ramp_proc(reference_in, &reference_out);
            }
            break;
        }
    }
    return trip_code;
}

#define ANTI_WINDUP_GAIN    1.0
#define d_anti_gain         1.0
#define q_anti_gain         1.0
#define alpha_speed         1.0
#define alpha               1.0

void servoSpeedCtrl(){

    double temp2_Tref;
    double temp_Vd;
    double temp_Vq;

    //--- speed_controller();
    //    SPEED_ERR = SPEED_REF - SPEED_REAL;
    SPEED_REF = wm_rat * reference_out;

    SPEED_ERR = SPEED_REF - SPEED_REAL;
    uspeed_kp = alpha_speed * code_kpSpeed * SPEED_ERR;
    speed_err_ki = SPEED_ERR - speed_anti_windup;
    //'Bilinear, s=(2/Ts)*((z+1)/(z-1))
    uspeed_ki = 0.5 * code_kiSpeed * Ts * (speed_err_ki+speed_err_ki_delay1)+uspeed_ki_delay1;

    uspeed_IP = (1-alpha_speed)*code_kpSpeed*SPEED_REAL;

    temp2_Tref = uspeed_kp + uspeed_ki + uspeed_IP;

    Is_DQ_max[QS]=sqrt( fabs(Is_max*Is_max - Is_DQ_ref[DS]*Is_DQ_ref[DS]) );
    // Torque_MAX = Kt * Fs * Is_DQ_max[QS];
    Torque_MAX = Is_rat;            // 2019.08.27 by  정순길

    if (temp2_Tref >= Torque_MAX)       torque_real = Torque_MAX;
    else if(temp2_Tref<=-Torque_MAX)    torque_real = -Torque_MAX;
    else                                torque_real = temp2_Tref;

    uspeed_ki_delay1 = uspeed_ki;
    speed_err_ki_delay1 = speed_err_ki;
    speed_anti_windup = ANTI_WINDUP_GAIN * (temp2_Tref - torque_real);

    Iq_ref = torque_real;

    if (Iq_ref >= Is_rat)        Iq_ref = Is_rat;
    else if(Iq_ref<=-Is_rat)     Iq_ref = -Is_rat;

    SinTheta = sin(theta_m);
    CosTheta = cos(theta_m);

    Is_DQ[DS] =  CosTheta * Is_dq[ds] + SinTheta * Is_dq[qs];
    Is_DQ[QS] = -SinTheta * Is_dq[ds] + CosTheta * Is_dq[qs];

     // d_axis_current_controller();
     Id_err = Id_ref - Is_DQ[DS];
     ud_kp = alpha * code_kpIdq * Id_err;
     Id_err_ki = Id_err - d_current_anti_windup;
     ud_ki = 0.5 * code_kiIdq * Ts * (Id_err_ki + Id_err_ki_delay1 ) + ud_ki_delay1; //'Bilinear, s=(2/Ts)*((z+1)/(z-1))
     ud_IP = (1-alpha) * code_kpIdq * Is_DQ[DS];

     temp_Vd = ud_kp+ud_ki+ud_IP;

     Vs_DQ_max[DS] = INV_ROOT3 * Vdc; // Vs_max = Vdc / sqrt(3) = 0.57735 * Vdc

     if (temp_Vd >= Vs_DQ_max[DS])      Vs_DQ_ref[DS] = Vs_DQ_max[DS];
     else if(temp_Vd<=-Vs_DQ_max[DS])   Vs_DQ_ref[DS] = -Vs_DQ_max[DS];
     else                        Vs_DQ_ref[DS] = temp_Vd;

     ud_ki_delay1 = ud_ki;
     Id_err_ki_delay1 = Id_err_ki;
     d_current_anti_windup = d_anti_gain*(temp_Vd - Vs_DQ_ref[DS]);

     // q_axis_current_controller();
     Vs_max=0.57735*Vdc;

     Iq_err = Iq_ref - Is_DQ[QS];
     uq_kp = alpha*code_kpIdq*Iq_err;
     Iq_err_ki = Iq_err-q_current_anti_windup;
     uq_ki = 0.5 * code_kiIdq * Ts *(Iq_err_ki+Iq_err_ki_delay1)+uq_ki_delay1; //'Bilinear, s=(2/Ts)*((z+1)/(z-1))

     uq_IP = (1-alpha)*code_kpIdq * Is_DQ[QS];
     temp_Vq = uq_kp+uq_ki+uq_IP;

     // Vs_DQ_max[QS]= 2.0 * INV_ROOT3 * Vdc ; // 2.0 * Vs_max;
     // Vq_MAX = 2.0 * INV_ROOT3 * Vdc ; // 2.0 * Vs_max;

     Vs_DQ_max[QS]=2.0*Vs_max;
     if (temp_Vq >= Vs_DQ_max[QS])          Vs_DQ_ref[QS] = Vs_DQ_max[QS];
     else if(temp_Vq<=-Vs_DQ_max[QS])       Vs_DQ_ref[QS] = -Vs_DQ_max[QS];
     else                            Vs_DQ_ref[QS] = temp_Vq;

     uq_ki_delay1 = uq_ki;
     Iq_err_ki_delay1 = Iq_err_ki;
     q_current_anti_windup = q_anti_gain*(temp_Vq - Vs_DQ_ref[QS]);

     Te=Kt* Fs_rat *Is_DQ[QS];  // debug 2.0 N.m( HC-MF23 순시토크)
     P_total = Te * wr_m;
//--- voltage_inverse_transform();
     Vs_dq_ref[ds] = CosTheta * Vs_DQ_ref[DS] - SinTheta*Vs_DQ_ref[QS];
     Vs_dq_ref[qs] = SinTheta * Vs_DQ_ref[DS] + CosTheta*Vs_DQ_ref[QS];
}


double time_init=0.0;

void pos_ref_gen(void) // Speed Reference generation
{
	float time_min = 0.0;

	POS_REF_NEW = POS_REF;   //
	
	if ((POS_REF_NEW != POS_REF_OLD)&&(profile_FLAG==0)) {
		profile_FLAG = 1;  // ���� ��ġ ��ɰ� ���ο� ��ġ ����� �ٸ� ��� �������� �ð� ������ flag set
		cal_FLAG = 1;
	}
	
	if ((profile_FLAG==1)&&(cal_FLAG==1)) {
	    // �������� �ð� ������ flag�� set �� ��� �������� �û� ���� ��ƾ ����
		//ACC_MAX = Torque_MAX/Jm;          // �ִ� ��ũ�� Inertia �̿��Ͽ� �ִ� ���ӵ� ���
		time_min = MAX_SPEED/ACC_MAX;     // ��ٸ��� ������ �ּ� �ð� ���
		Dist_New = fabs(POS_REF_NEW-POS_REF_OLD);   // �̵��ؾ� �� ���Ÿ� ���
		if ((POS_REF_NEW-POS_REF_OLD)<0.0) SIGN_FLAG = 1;   // ���ο� ��ġ ��ɰ� ���� ��ġ ������� ��������� ���������� falg ����
		else SIGN_FLAG = 0;
		Dist_min = MAX_SPEED*time_min;    // ��ٶ�� �ӵ��� ���� ���ϴ� �ּ� �Ÿ� ��� 
	
		if (Dist_New>Dist_min) {              // �̵��ؾ���  ��� �̵��Ÿ��� ��ٸ��� �ӵ��� ���� �� �ִ� ��� ����Ǵ� ��ƾ
		 	prof_t1 = MAX_SPEED/ACC_MAX;
		 	prof_t2 = (Dist_New-MAX_SPEED*prof_t1)/MAX_SPEED+prof_t1;
		 	prof_t3 = prof_t2+prof_t1;
		 	if (SIGN_FLAG == 0) {               // ���� �������� �̵��� t1 �� t2 �ð� ���� �̵��� ��� �Ÿ� ���
		 		init_t1 = 0.5*ACC_MAX*prof_t1*prof_t1;
		 		init_t2 = MAX_SPEED*(prof_t2-prof_t1)+init_t1;
		 	    }
		 	else {
		 		init_t1 = -0.5*ACC_MAX*prof_t1*prof_t1;       // ���� �������� �̵��� t1 �� t2 �ð� ���� �̵��� ��� �Ÿ� ���
		 		init_t2 = -MAX_SPEED*(prof_t2-prof_t1)+init_t1;
		 	    } 
		    }
		else {                                    // �̵��ؾ���  ��� �̵��Ÿ��� ��ٸ��� �ӵ��� ���� �� ���� ��� ����Ǵ� ��ƾ
		   	prof_t1 = sqrt(Dist_New/ACC_MAX);
		   	prof_t2 = prof_t1;
		   	prof_t3 = 2.0*prof_t1;
		   	SPEED_M = Dist_New/prof_t1;           // ���� ������ �ִ� �ӵ� ���
		   	if (SIGN_FLAG == 0) init_t1 = 0.5*ACC_MAX*prof_t1*prof_t1;  // ���� �������� �̵��� t1 �ð� ���� �̵��� ��� �Ÿ� ���
		   	else init_t1 = -0.5*ACC_MAX*prof_t1*prof_t1;                // ���� �������� �̵��� t1 �ð� ���� �̵��� ��� �Ÿ� ���
		    }
		
		profile_gen_time = 0.0;   // ��ġ ��� ���� �ð� üũ�� ���� �ʱ�ȭ
		cal_FLAG = 0;
	    }  
		
	if (profile_gen_time <= prof_t3) {        // �������� ���� �ð��� ���� �ð� t3�� �Ѿ�� ������ ����Ǵ� ��ƾ      
		if(Dist_New>Dist_min) {               // �̵��ؾ� �� ��� �Ÿ��� ��ٸ��� �ӵ� ����� ���� �� �ִ� ��� ����Ǵ� ��ƾ
			switch(SIGN_FLAG) {               // ������ ���� �������� �Ǻ��ϴ�  ��ƾ
 				case 0 : if (profile_gen_time <= prof_t1)     // ���� �������� �̵��� �����ϴ� ��ƾ
							 SPD_REF_PLC = profile_gen_time*ACC_MAX;
						 else if ((profile_gen_time>prof_t1)&&(profile_gen_time<=prof_t2))
						 	 SPD_REF_PLC = MAX_SPEED;
						 else if ((profile_gen_time>prof_t2)&&(profile_gen_time<=prof_t3)) {
						     SPD_REF_PLC = (MAX_SPEED - MAX_SPEED*(profile_gen_time-prof_t2)/(prof_t3-prof_t2));						    
			                 }
						 break;
				case 1 : if (profile_gen_time <= prof_t1)     // ���� �������� �̵��� �����ϴ� ��ƾ
							 SPD_REF_PLC = -profile_gen_time*ACC_MAX;
						 else if ((profile_gen_time>prof_t1)&&(profile_gen_time<=prof_t2))
						 	 SPD_REF_PLC = -MAX_SPEED;
						 else if ((profile_gen_time>prof_t2)&&(profile_gen_time<=prof_t3)) {
						     SPD_REF_PLC = -(MAX_SPEED - MAX_SPEED*(profile_gen_time-prof_t2)/(prof_t3-prof_t2));						    
			                 }
						 break;
			    }
		}
		 else {
			switch(SIGN_FLAG) {
				case 0 : if (profile_gen_time <= prof_t1)
							 SPD_REF_PLC = profile_gen_time*ACC_MAX;
						 else if ((profile_gen_time>prof_t1)&&(profile_gen_time<=prof_t3)) {
						     SPD_REF_PLC = -(ACC_MAX*prof_t1/(prof_t3-prof_t1))*(profile_gen_time-prof_t3);
			                 }
						 break;
				case 1 :  if (profile_gen_time <= prof_t1)
							 SPD_REF_PLC = -profile_gen_time*ACC_MAX;
						 else if ((profile_gen_time>prof_t1)&&(profile_gen_time<=prof_t3)) {
						     SPD_REF_PLC = (ACC_MAX*prof_t1/(prof_t3-prof_t1))*(profile_gen_time-prof_t3);
			                 }
						 break;
			    }
		 }
		 profile_gen_time += Ts;
		 }
	else {
		POS_REF_OLD = POS_REF_NEW;	// ���� ��ġ ��� ���� ���� ��ġ ��� ������ update(������ġ)
		profile_FLAG = 0;         // �������� �ð� ��� flag reset
	    }
}

// end of pmsmCtrl.c

