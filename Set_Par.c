#include	<header.h>
#include	<extern.h>

int HardwareParameterVerification()
{
	if ( codeRatePower >(0.99*sqrt(3.0) * codeRateVolt * codeRateCurrent)){
		trip_recording( CODE_rate_power, codeRatePower,"POWER FACTOR OVER");
		return	CODE_rate_power;
	}	

	if (codeRatePower<(0.2*sqrt(3.0)* codeRateVolt * codeRateCurrent)){
		trip_recording( CODE_rate_power, codeRatePower,"POWER FACTOR UNDER");
		return	CODE_rate_power;
	}

	if (codeRateRpm < (0.85*120.0 * codeRateHz / codeMotorPole)){
		trip_recording( CODE_rate_rpm, codeRateRpm,"RATE RPM UNDER");
		return	CODE_rate_rpm;
	}
	Vs_rat=sqrt(2.0)/sqrt(3.0)* codeRateVolt;			// �������� ��ũ ��

	Is_rat=sqrt(2.0)*codeRateCurrent;

	inv_Is_rat=1.0/Is_rat;
	Freq_rat = codeRateHz;
	we_rat=PI_2*Freq_rat;

	inv_Freq_rat=1.0/Freq_rat;

	inv_motor_rate_hz = 1.0 / codeRateHz; //   csk_check 2009.10.30
	wr_rat=PI_2*codeMotorPole*codeRateRpm/120.0;			// rpm -> rad/sec
	wm_rat=wr_rat*(2.0/codeMotorPole);
	Te_rat= codeRatePower/wm_rat;

	inv_Te_rat=1.0/Te_rat;
	Fs_rat=Vs_rat/we_rat;

	Kt=(3.0/2.0)*(codeMotorPole/2.0);
	inv_Kt=1.0/Kt;
	P_pair=(codeMotorPole/2.0);
	inv_P_pair=1.0/P_pair;
	rpm_Coeff=60.0*inv_P_pair/PI_2;
	
	S_rat=(we_rat-wr_rat)/we_rat;
	S_lin=(codeMotorPole/PI)*(S_rat*Freq_rat)/Te_rat;
	Freq_slip_rat=S_rat*Freq_rat;

	inv_Ts = codePwmFreq;
	Ts = 1.0 / codePwmFreq;	// debug

	Is_max = Is_rat * Is_Max_Coeff ;	// added 2009.11.01	
	OverCurLimit = Is_max *2;			// added 2009.11.01  _debug

	return	0;	
}
