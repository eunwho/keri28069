#include	<header.h>
#include	<extern.h>
/*
int COMMON_VECT_CNTL_ParameterVerification()
{
    double  In;         // 무부하 전류 계산

    // 모터 파라미터 검증
    if ( (Rs<2.0e-3) || (Rs>20.0) )
        return  CODE_Rs;
    if ( (Rr<2.0e-3) || (Rr>20.0) )
        return  CODE_Rr;

    // 인덕턴스 : 1.0e-3*mH -> H
    Ls=1.0e-3*Ls_mH;
    Lr=1.0e-3*Lr_mH;
    Lm=1.0e-3*Lm_mH;

    if ( (Ls<2.0e-3) || (Ls>1.0) )
        return  CODE_Ls_mH;
    if ( (Lr<2.0e-3) || (Lr>1.0) )
        return  CODE_Lr_mH;
    if ( (Lm<2.0e-3) || (Lm>1.0) )
        return  CODE_Lm_mH;
    if ( (Lm>(0.985*Ls)) || (Lm>(0.985*Lr)) )
        return  CODE_Lm_mH;

    // 인덕턴스(Ls, Lr)의 검증
    In=Vs_rat/(we_rat*Ls);                              // 무부하 전류 계산
    if ( (In<(0.1*Is_rat)) || (In>(0.8*Is_rat)) )       // 무부하 전류가 정격전류의 10% ~ 80%이 아닌 경우
        return  CODE_Ls_mH;

    if ( (Lr<(0.9*Ls)) || (Lr>(1.1*Ls)) )
        return  CODE_Lr_mH;

    // 시정수
    Tr=Lr/Rr;
    if ( (Tr<0.02) || (Tr>2.0) )                        // 시정수 : 0.02 ~ 2.0초
        return  ERR_Tr_Over;

    // 고정자 저항
    if ( (Rs<(0.5*Rr)) || (Rs>(20.0*Rr)) )
        return  CODE_Rs;

    // 누설 인덕턴스의 검증
    sigma_Ls=Ls-(Lm*Lm)/Lr;
    sigma=sigma_Ls/Ls;
    if (sigma<0.02)
            return  ERR_sigma_Under;                    // 누설자속이 작게 추정된 경우
    else if (sigma>0.2)
            return  ERR_sigma_Over;                     // 누설자속이 크게 추정된 경우

    // 기타 파라미터 계산
    inv_Tr=1.0/Tr;
    inv_Ls=1.0/Ls;
    inv_Lm=1.0/Lm;
    SlipCoeff=Ls/Tr;
    sigma_Tr=sigma*Tr;
    inv_sigma_Tr=1.0/sigma_Tr;
    sigma_minus_1_div_sigma_Ls=(sigma-1.0)/sigma_Ls;
    inv_sigma_Ls=1.0/sigma_Ls;
    inv_Ls_plus_sigma_Ls=1.0/(sigma_Ls+Ls);             // 전류 상한값 계산
    sigma_Ls_div_1_plus_sigma=sigma_Ls/(1.0+sigma);     // 전류 상한값 계산
    Lm_div_Lr=Lm/Lr;
    Lr_div_Lm=Lr/Lm;

    // 전류제어기
    if ( (K_Damp_Is<0.1) || (K_Damp_Is>1.0) )
        return  CODE_K_Damp_Is;
    if ( (PM_Is<(PI/20.0)) || (PM_Is>(5.0*PI/12.0)) )
        return  CODE_PM_Is;
    if ( (GM_Is<2.5) || (GM_Is>10.0) )
        return  CODE_GM_Is;

    // 전류 제어기 설정
    inv_GM_Is_square_minus_1=1.0/(GM_Is*GM_Is-1.0);         // 1.0/(GM*GM-1.0)
    inv_GM_Is=1.0/GM_Is;
    wp_Is_Coeff=(GM_Is*PM_Is+PI_1_2*GM_Is*(GM_Is-1.0))*inv_GM_Is_square_minus_1;
    Kp_Is_Coeff=sigma_Ls*inv_GM_Is;

    wp_Is=wp_Is_Coeff*inv_Ts;                   // Td_Is=Ts
    Kp_Is=Kp_Is_Coeff*wp_Is;
    Ki_Is=Kp_Is*(2.0*wp_Is-inv_PI_1_4*wp_Is*wp_Is*Ts+(Rs+Rr)*inv_sigma_Ls);

    if (Ki_Is<=10.0)
        return  ERR_Ki_Is_Under;            // 전류제어기 설정 오류
    if (Kp_Is>Ki_Is)
        return  ERR_Kp_Is_Over;
    else if (Kp_Is<0.0)
        return  ERR_Kp_Is_Under;


    // 파라미터 오류가 없다.
    return  0;
}
*/

int COMMON_S_VECT_CNTL_ParameterVerification()
{
    int ErrCode;

    // 벡터제어에 필요한 파라미터를 읽고 검증한다.
    ErrCode=COMMON_VECT_CNTL_ParameterVerification();
    if (ErrCode!=0)
        return  ErrCode;


    // 엔코드 파라미터
    if (code_encoderPulse < 50) return  CODE_EncoderPulse;

    ROTOR_ANGLE_PER_PULSE = PI_2/(4.0*code_encoderPulse);             // 4채배 => 한개의 펄스당 기계각 증가분


    if ( (Default_wr_FilterPole<20.0) || (Default_wr_FilterPole>500.0) )
        return  CODE_Default_wr_FilterPole;
    wr_FilterPole=Default_wr_FilterPole;                    // 속도 추정기의 필터 폴


    //  자속제어기 설정    및 약계자 프로파일
    if ( (Fr_CntlPeriodIndex<1) || (Fr_CntlPeriodIndex>30) )
        return  CODE_Fr_CntlPeriodIndex;
    if ( (FW_VoltageCoeff<0.2) || (FW_VoltageCoeff>1.2) )           // 약계자 시작 전압 계수
        return  CODE_FW_VoltageCoeff;
    if ( (Base_Flux_Coeff<0.1) || (Base_Flux_Coeff>2.5) )               // Base Flux < 250%
        return  CODE_Base_Flux_Coeff;
    if ( (ExcitationTime<0.1) || (ExcitationTime>3.0) )
        return  CODE_ExcitationTime;

    if ( (K_Damp_Fr<0.0) || (K_Damp_Fr>1.0) )
        return  CODE_K_Damp_Fr;
    if ( (GM_Fr<2.5) || (GM_Fr>25.0) )
        return  CODE_GM_Fr;
    if ( (PM_Fr<(PI/12.0)) || (PM_Fr>(5.0*PI/12.0)) )
        return  CODE_PM_Fr;

    Fr_rat=sqrt(Fs_rat*Fs_rat-0.75*0.75*sigma_Ls*sigma_Ls*Is_rat*Is_rat)/(Lm/Lr+sigma_Ls/Lm);
    Fr_B=Base_Flux_Coeff*Fr_rat;
    inv_Fr_B=1.0/Fr_B;
    Fr_ref=Fr_B;
    HalfExcitationTime=0.5*ExcitationTime;

    // 약계자 시작 주파수
    we_FW_Coeff = 1.0/  sqrt(Ls*Ls*(Fr_B/Lm)*(Fr_B/Lm)+sigma_Ls*sigma_Ls*(Is_max*Is_max-(Fr_B/Lm)*(Fr_B/Lm))) ;
    we_FW1_Coeff = sqrt((Ls*Ls+sigma_Ls*sigma_Ls)/(2.0*Ls*Ls*sigma_Ls*sigma_Ls))/Is_max ;

    // 자속 제어기
    inv_GM_Fr_square_minus_1=1.0/(GM_Fr*GM_Fr-1.0);     // 1.0/(GM*GM-1.0)
    inv_GM_Fr=1.0/GM_Fr;
    wp_Fr_Coeff=(GM_Fr*PM_Fr+PI_1_2*GM_Fr*(GM_Fr-1.0))*inv_GM_Fr_square_minus_1;
    Kp_Fr_Coeff=(Tr/Lm)*inv_GM_Fr;

    wp_Fr=wp_Fr_Coeff/(Fr_CntlPeriodIndex*Ts);          // Td_Is=(Fr_CntlPeriodIndex*Ts)
    Kp_Fr=Kp_Fr_Coeff*wp_Fr;
    Ki_Fr=Kp_Fr*(2.0*wp_Fr-inv_PI_1_4*wp_Fr*wp_Fr*(Fr_CntlPeriodIndex*Ts)+Tr);

    if (Ki_Fr<=1.0e-6)
        return  ERR_Ki_Fr_Under;                        // 자속제어기 설정 오류


    // 파라미터 오류가 없다.
    return  0;
}


// 센스리스 토크제어에 필요한 파라미터
int S_TORQUE_CNTL_Parameter()
{
    int ErrCode;

    // 벡터제어에 필요한 파라미터를 읽고 검증한다.
    ErrCode=COMMON_S_VECT_CNTL_ParameterVerification();
    if (ErrCode!=0)
        return  ErrCode;

    // 파라미터 오류가 없다.
    return  0;
}


// 센스리스 속도제어에 필요한 파라미터
int S_SPEED_CNTL_Parameter()
{
    int ErrCode;

    // 벡터제어에 필요한 파라미터를 읽고 검증한다.
    ErrCode=COMMON_S_VECT_CNTL_ParameterVerification();
    if (ErrCode!=0)
        return  ErrCode;

    // 속도제어기
    if ( (wr_CntlPeriodIndex<1) || (wr_CntlPeriodIndex>30) )
        return  CODE_wr_CntlPeriodIndex;

    if ( (K_Damp_wr<0.05) || (K_Damp_wr>1.0) )
        return  CODE_K_Damp_wr;

    if ( (wr_DampingRatio<0.6) || (wr_DampingRatio>1.5) )
        return  CODE_wr_DampingRatio;

    if ( (wr_FilterPoleCoeff<5.0) || (wr_FilterPoleCoeff>30.0) )
        return  CODE_wr_FilterPoleCoeff;

    if ( (wn_wr_Coeff<2.0) || (wn_wr_Coeff>30.0) )
        return  CODE_wn_wr_Coeff;

    if ( (Max_wn_wr<(2.0*PI*0.5)) || (Max_wn_wr>(2.0*PI*20.0)) )
        return  CODE_Max_wn_wr;

    if ( (Jm<0.0001) || (Jm>300.0) )
        return  CODE_Jm;

    //  속도제어기 설정
    inv_Te_rat=1.0/Te_rat;

    wn_wr=wn_wr_Coeff*( (P_pair*Te_rat/wr_rat)/Jm );    // speed rising time=(P/2.0)*(Te_rat/wr_rat)/Jm
    if (wn_wr>Max_wn_wr)    wn_wr=Max_wn_wr;    // max_wn_wr*10.0 ==> measurement noise cutoff frequency

    wr_FilterPole=wr_FilterPoleCoeff*wn_wr;         // 속도 추정기의 필터 폴
    Kp_wr=(Jm*2.0*wr_DampingRatio*wn_wr)*(Lr_div_Lm*inv_Kt/Fr_B);
    Ki_wr=(Jm*wn_wr*wn_wr)*(Lr_div_Lm*inv_Kt/Fr_B);

    // 파라미터 오류가 없다.
    return  0;
}

void S_SpeedCntl_RFO()
{
	double 	IntegralLimit;
	
	// 속도 검출 : 엔코더 사용
	wr=wr_m0;
	
	// 속도제어
	wr_ref=wr_rat * reference_out;
	
	wr_CycleIndex++;
	wr_Cycle+=Ts;
	if (wr_CycleIndex>=wr_CntlPeriodIndex)
	{
		wr_err=wr_ref-wr;
		wr_ErrInt+=Ki_wr*wr_err*inv_P_pair*wr_Cycle;
		IntegralLimit=Kp_wr*fabs(K_Damp_wr*wr_ref-wr)*inv_P_pair + Is_DQ_max[QS];
		if (wr_ErrInt>IntegralLimit)	
			wr_ErrInt=IntegralLimit;
		else if (wr_ErrInt<-IntegralLimit)	
			wr_ErrInt=-IntegralLimit;

		// Q-축 전류 명령	
		Is_DQ_ref[QS]=Kp_wr*(K_Damp_wr*wr_ref-wr)*inv_P_pair+wr_ErrInt;
		
		// 초기 자속형성시에는 속도제어기의 적분기를 사용하지 않는다.
		if (gfRunTime<0.05)
			wr_ErrInt=0.0;
		
		wr_Cycle=0.0;
		wr_CycleIndex=0;
	}	
	
	// Q-축 전류 명령 => 센스사용 간접 벡터제어
	S_VectCntl_RFO();	
}

void S_TorqueCntl_RFO()
{
	// 토크 Ref.
	Te_ref=Te_rat*reference_out;
	inv_Fr_ref=1.0/Fr_ref;
	Is_DQ_ref[QS]=(inv_Kt*Lr_div_Lm)*(Te_ref*inv_Fr_ref);
	
	// Q-축 전류 명령 => 센스사용 간접 벡터제어
	S_VectCntl_RFO();	
}


//***********************************************************

// Indirect Rotor Flux Oriented Vector Control with Sensor
void S_VectCntl_RFO()
{	
	double	I_DS_FW2;
	
	// 최대 출력 전압 
	Vs_max=0.57735*Vdc;
	
	// 속도 검출 : 엔코더 사용
	wr=wr_m0;
	
	//*****************************************
	
	//전류 및 전압의  좌표변환 : 전단계의 각도를 사용  
	Is_DQ[DS] = CosTheta*Is_dq[ds] + SinTheta*Is_dq[qs];
	Is_DQ[QS] = -SinTheta*Is_dq[ds] + CosTheta*Is_dq[qs];
	
	// 회전자 자속 추정
	Fr += inv_Tr*(Lm*Is_DQ[DS]-Fr)*Ts;
	
	// 슬립계산 : 충분한 자속이 형성된 후에 슬립을 발생시킨다.
	if (Fr>(0.01*Fr_B))
	{
		inv_Fr=1.0/Fr;
		w_sl=(Lm*Is_DQ[QS])*(inv_Tr*inv_Fr);
	}		
	else
	{
		inv_Fr=1.0/(0.01*Fr_B);	
		w_sl=inv_Tr*Lm*Is_DQ[QS]*inv_Fr;	
	}		
	
	w_sl0+=250.0*(w_sl-w_sl0)*Ts;
	wr_m0 = wr_m; // debug 필터를 적용할 것
	;
	we=wr_m+w_sl;
	we0=wr_m0+w_sl0;				// 슬립 주파수만 필터링
	
	// 각도 추정 : 필터링된 주파수를 사용하면 안된다.
	theta += we*Ts;
	
	if (theta>PI)		theta-=PI_2;
	else if (theta<-PI)	theta+=PI_2;
	CosTheta=cos(theta + we0*Ts);
	SinTheta=sin(theta + we0*Ts);

	//******************************************************************
	
	// 회전자 자속 프로파일 : 자속 레벨 조정 ==> 약계자 운전, Q-축 전류 상한 값도 결정된다.
	Vs_max = 0.57735*Vdc;													// 1.0/sqrt(3.0)=0.57735027
	Vs_max_FW += 50.0*(FW_VoltageCoeff*(Vs_max-Rs*Is_max) - Vs_max_FW)*Ts;		// DC전압 센서에 존재하는 60Hz 코먼모드 노이즈와 전압 리플을 필터링 한다.	
	
	we_FW=we_FW_Coeff *Vs_max_FW;    	// <==  1.0/  sqrt(Ls*Ls*(Fr_B/Lm)*(Fr_B/Lm)+sigma_Ls*sigma_Ls*(Is_max*Is_max-(Fr_B/Lm)*(Fr_B/Lm)))  * Vs_max_FW
	we_FW1=we_FW1_Coeff *Vs_max_FW;  	// <==  sqrt((Ls*Ls+sigma_Ls*sigma_Ls)/(2.0*Ls*Ls*sigma_Ls*sigma_Ls))/Is_max * Vs_max_FW
		
	if (gfRunTime<0.05)
	{
		Fr_ref=Fr_B;
		Is_DQ_max[DS]=0.75*Is_max;		// D-축 전류는 편의상 최대 전류의 75%이내로 제한한다.	
		Is_DQ_max[QS]=sqrt( fabs(Is_max*Is_max - Is_DQ_ref[DS]*Is_DQ_ref[DS]) );
	}	
	else
	{	
		if (fabs(we0)<we_FW)
		{
			Fr_ref0=Fr_B;
			Is_DQ_max[DS]=0.75*Is_max;		// D-축 전류는 편의상 최대 전류의 75%이내로 제한한다.	
			Is_DQ_max[QS]=sqrt( fabs(Is_max*Is_max - Is_DQ_ref[DS]*Is_DQ_ref[DS]) );
		}		
		else if (fabs(we0)<we_FW1)
		{	
			Fr_ref0=Fr_B*(we_FW1/fabs(we0));		// ==> Lm*sqrt( ((Vs_max_FW*Vs_max_FW)/(we0*we0)-sigma_Ls*sigma_Ls*Is_max*Is_max)/(Ls*Ls-sigma_Ls*sigma_Ls) )
			Is_DQ_max[DS]=0.75*Is_max;		// D-축 전류는 편의상 최대 전류의 75%이내로 제한한다.	
			Is_DQ_max[QS]=sqrt( fabs(Is_max*Is_max - Is_DQ_ref[DS]*Is_DQ_ref[DS]) );
		}		
		else	
		{
			I_DS_FW2=Vs_max_FW/(1.414*fabs(we0)*Ls);
			Fr_ref0=Lm*I_DS_FW2;		
			Is_DQ_max[DS]=I_DS_FW2*sqrt(1.0 + 1.0/(sigma*sigma));	
			Is_DQ_max[QS]=I_DS_FW2/sigma;
		}	
		
		if (Fr_ref0>Fr_B)
				Fr_ref0=Fr_B;
				
		Fr_ref=Fr_ref0;
	}
	
	//***************************************************************

	// 회전자 자속 제어기
	
	Fr_CycleIndex++;
	Fr_Cycle+=Ts;
	if (Fr_CycleIndex>=Fr_CntlPeriodIndex)
	{

		Fr_Err=Fr_ref-Fr;
		Fr_ErrInt+=Ki_Fr*Fr_Err*Fr_Cycle;

		if (Fr_ErrInt>Is_DQ_max[DS])		
				Fr_ErrInt=Is_DQ_max[DS];
		else if (Fr_ErrInt<-Is_DQ_max[DS])	
				Fr_ErrInt=-Is_DQ_max[DS];
		Is_DQ_ref[DS]=Kp_Fr*Fr_Err+Fr_ErrInt;	// + Fr_ref*inv_Lm;
		
		// 제어 주기 인덱스 및 시간 초기화
		Fr_Cycle=0.0;
		Fr_CycleIndex=0;	
	}	
	
	//*********************************************************
	
	// D-축 전류 명령 : Feedforwrd Term + PI Controller Output	
	if (Is_DQ_ref[DS]>Is_DQ_max[DS])	
		Is_DQ_ref[DS]=Is_DQ_max[DS];
	else if (Is_DQ_ref[DS]<-Is_DQ_max[DS])	
		Is_DQ_ref[DS]=-Is_DQ_max[DS];	

	//Q-축 전류 명령		
	if (Is_DQ_ref[QS]>Is_DQ_max[QS])		
		Is_DQ_ref[QS]=Is_DQ_max[QS];
	else if (Is_DQ_ref[QS]<-Is_DQ_max[QS])	
		Is_DQ_ref[QS]=-Is_DQ_max[QS];	

	
	// D-축 전류 제어기 : 자속제어기 -> D-축 전류 Ref.
	Vs_DQ_ref_P[DS]=codeKpIs*(K_Damp_Is*Is_DQ_ref[DS]-Is_DQ[DS]);
	Vs_DQ_max[DS]=Vs_max + fabs(Vs_DQ_ref_P[DS]);						// 적분기의 상한값 조정
	Is_DQ_ErrInt[DS] += codeKiIs*(Is_DQ_ref[DS] - Is_DQ[DS])*Ts;
	if (Is_DQ_ErrInt[DS]>Vs_DQ_max[DS])		
			Is_DQ_ErrInt[DS] = Vs_DQ_max[DS];
	else if (Is_DQ_ErrInt[DS]<-Vs_DQ_max[DS])	
			Is_DQ_ErrInt[DS] = -Vs_DQ_max[DS];
	Vs_DQ_ref_PI[DS]=Vs_DQ_ref_P[DS] + Is_DQ_ErrInt[DS];

	// Q-축 전류 제어기 : 토크 명령 ==> Q-축 전류 명령	
	Vs_DQ_ref_P[QS]=codeKpIs*(K_Damp_Is*Is_DQ_ref[QS]-Is_DQ[QS]);
	Vs_DQ_max[QS]=Vs_max + fabs(Vs_DQ_ref_P[QS]);					// 적분기의 상한값 조정
	Is_DQ_ErrInt[QS] += codeKiIs*(Is_DQ_ref[QS]- Is_DQ[QS])*Ts;
	if (Is_DQ_ErrInt[QS]>Vs_DQ_max[QS])			
			Is_DQ_ErrInt[QS] = Vs_DQ_max[QS];
	else if (Is_DQ_ErrInt[QS]<-Vs_DQ_max[QS])		
			Is_DQ_ErrInt[QS] = -Vs_DQ_max[QS];
	Vs_DQ_ref_PI[QS] = Vs_DQ_ref_P[QS] + Is_DQ_ErrInt[QS];
	
	// 간섭항 및 기전력 보상
	if (gfRunTime<0.05)
	{
		Vs_DQ_ref[DS] = Vs_DQ_ref_PI[DS] - we0*sigma_Ls*Is_DQ_ref[QS];	
		Vs_DQ_ref[QS] = Vs_DQ_ref_PI[QS] + we0*sigma_Ls*Is_DQ_ref[DS] + we0*Lm_div_Lr*Fr;
	}		
	else
	{
		Vs_DQ_ref[DS] = Vs_DQ_ref_PI[DS] - we0*sigma_Ls*Is_DQ_ref[QS];	
		Vs_DQ_ref[QS] = Vs_DQ_ref_PI[QS] + we0*sigma_Ls*Is_DQ_ref[DS] + we0*Lm_div_Lr*Fr_ref;
	}	
	
	// 데드타임 보상 -> 최종 전압 출력
	// 상전압 추정 : 시간지연(Ts) 보상 
	Us_dq[ds]=Vs_dq[ds];
	Us_dq[qs]=Vs_dq[qs];
	CosDeltaTheta=cos(we0*Ts);
	SinDeltaTheta=sin(we0*Ts);
	Vs_dq[ds] = Us_dq[ds]*CosDeltaTheta + Us_dq[qs]*SinDeltaTheta;
	Vs_dq[qs] = -Us_dq[ds]*SinDeltaTheta + Us_dq[qs]*CosDeltaTheta;
	
	// 전류제어기 -> 정지 좌표계 전압 명령 : 역 좌표변환, 데드타임 보상
	Vs_dq_ref[ds] = (CosTheta*Vs_DQ_ref[DS] - SinTheta*Vs_DQ_ref[QS]) + (Vs_dq_ref[ds]-Vs_dq[ds]);
	Vs_dq_ref[qs] = (SinTheta*Vs_DQ_ref[DS] + CosTheta*Vs_DQ_ref[QS]) + (Vs_dq_ref[qs]-Vs_dq[qs]);
	
	//************************************************************************************************
	
	// 간접토크 계산
	Te=Kt*Lm_div_Lr*Fr*Is_DQ[QS];
}

