#ifndef		__CODE_PROC_H_
#define		__CODE_PROC_H_	


#define TYPE_INTEGER		0
#define TYPE_float			1

//======================================
// Code address
//======================================
#define CODE_motor_direction_change		1
#define CODE_accel_time1				2
#define CODE_decel_time1				3
#define CODE_MotorCtrMode               4
#define CODE_speed1						5
#define CODE_speed2						6
#define CODE_set_vdc                    7
#define CODE_protect_off                8
#define CODE_pwm_freq                   9

#define CODE_rate_power			        10
#define CODE_rate_current               11
#define CODE_rate_rpm                   12
#define CODE_rate_effiency              13
#define CODE_rate_hz				    14
#define CODE_rate_volt                  15
#define CODE_motor_pole					16
#define CODE_presSensRef                17

#define CODE_IaOffset                   20
#define CODE_IbOffset                   21

#define CODE_I_sense_value              22
#define CODE_u_phase_I_sense_span       23
#define CODE_v_phase_I_sense_span       24
#define CODE_vdc_sense_zero             25
#define CODE_vdc_sense_span             26

#define CODE_adc_Vdc_low                35
#define CODE_adc_Vdc_high               36
#define CODE_Vdc_calc_low               37
#define CODE_Vdc_calc_high              38

#define CODE_VF_DeadTimeGain            40
#define CODE_VF_ExcitationTime          41
#define CODE_VF_Fs_Coeff                42
#define CODE_VF_Freq_TrqBoost           43
#define CODE_VF_Vs_Coeff_TrqBoost       44
#define CODE_VF_Rs_ThermalCoeff         45
#define CODE_VF_IR_Comp_FilterPole      46
#define CODE_VF_Slip_Comp_FilterPole    47
#define CODE_VF_Rs                      48


#define CODE_wattHour                   50
#define CODE_kWattHour                  51

#define CODE_scopeLoopCount             60

#define CODE_scopePointCh1              61
#define CODE_scopeScaleCh1              62
#define CODE_scopeOffsetCh1             63

#define CODE_scopePointCh2              64
#define CODE_scopeScaleCh2              65
#define CODE_scopeOffsetCh2             66

#define CODE_scopePointCh3              67
#define CODE_scopeScaleCh3              68
#define CODE_scopeOffsetCh3             69

#define CODE_scopePointCh4              70
#define CODE_scopeScaleCh4              71
#define CODE_scopeOffsetCh4             72

#define CODE_END                        73

#define CODE_Data_Check						800
#define CODE_Data_Backup					801
#define CODE_Data_Load						802
#define CODE_Data_Init						803
#define CODE_get_adc_offset					804

#define CODE_get_adc_vdc_low				805
#define CODE_get_adc_vdc_high				806

//--- end of code address

struct CODE_INFO_DEFINE {
	int		type;	
	int	  	open_level	;
	double	code_min ;
	double   code_max ;
	double   code_default;
	double   code_value;
	char   disp[40];
};
typedef struct CODE_INFO_DEFINE CODE_INFO;

#endif
