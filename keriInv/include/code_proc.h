#ifndef		__CODE_PROC_H_
#define		__CODE_PROC_H_	

#define TYPE_INTEGER		0
#define TYPE_float			1
//--- define constant

//======================================
// Code address
//======================================
#define CODE_set_vdc                    1
#define CODE_protect_off                2

#define CODE_motorId                    5
#define CODE_adc_Vdc_low                6
#define CODE_adc_Vdc_high               7
#define CODE_Vdc_calc_low               8
#define CODE_Vdc_calc_high              9

#define CODE_RampTest                   11
#define CODE_posi_duration_time         12
#define CODE_zero_duration_time         13
#define CODE_nega_duration_time         14
#define CODE_test_accel_time            15
#define CODE_test_decel_time            16
//--- da graph setting
#define CODE_scopeLoopCount             20
//--- ch1
#define CODE_scopePointCh1              21
#define CODE_scopeScaleCh1              22
#define CODE_scopeOffsetCh1             23
//--- ch2
#define CODE_scopePointCh2              24
#define CODE_scopeScaleCh2              25
#define CODE_scopeOffsetCh2             26
//--- ch3
#define CODE_scopePointCh3              27
#define CODE_scopeScaleCh3              28
#define CODE_scopeOffsetCh3             29
//--- ch4
#define CODE_scopePointCh4              30
#define CODE_scopeScaleCh4              31
#define CODE_scopeOffsetCh4             32

//---vector control
#define CODE_wr_FilterPoleCoeff         40
#define CODE_wn_wr_Coeff                41
#define CODE_Max_wn_wr                  42
#define CODE_K_Damp_wr                  43
#define CODE_wr_DampingRatio            44
#define CODE_wr_CntlPeriodIndex         45
#define CODE_FW_VoltageCoeff            46
#define CODE_Base_Flux_Coeff            47
#define CODE_ExcitationTime             48

#define CODE_K_Damp_Is                  51
#define CODE_K_Damp_Fr                  52
#define CODE_GM_Fr                      53
#define CODE_PM_Fr                      54
#define CODE_Default_wr_FilterPole      55
#define CODE_SlipCompCoeff              56
#define CODE_GammaLambda                57
#define CODE_GammaLambda_R_Constant     58
#define CODE_Max_DeltaLambda            59

#define CODE_GammaTheta_M               60
#define CODE_GammaTheta_R               61
#define CODE_Max_DeltaTheta             62
#define CODE_KiWrCoef                   63
#define CODE_FwCoef                     64
#define CODE_Fw2Coef                    65
#define CODE_Fr_CntlPeriodIndex         66

#define CODE_VF_DeadTimeGain            70
#define CODE_VF_ExcitationTime          71
#define CODE_VF_Fs_Coeff                72
#define CODE_VF_Freq_TrqBoost           73
#define CODE_VF_Vs_Coeff_TrqBoost       74
#define CODE_VF_Rs_ThermalCoeff         75
#define CODE_VF_IR_Comp_FilterPole      76
#define CODE_VF_Slip_Comp_FilterPole    77
#define CODE_VF_Rs                      78

#define CODE_AT_Freq_Leq_Req            80
#define CODE_AT_Time_Leq_Req            81
#define CODE_AT_Is_Coeff_Leq_Req        82
#define CODE_AT_Is_Coeff_Rs             83
#define CODE_AT_Time_Rs                 84
#define CODE_AT_DeadTimeGain            85
#define CODE_AT_Ls_Vs_RAMP              86
#define CODE_AT_Freq_Ls                 87
#define CODE_AT_Time_Ls                 88
//#define CODE_AT_Ls_DMB_OpenTime         59
//---
#define CODE_OPERAND_END                90

//--- motor parameter

#define CODE_rate_power                 101
#define CODE_rate_volt                  102
#define CODE_rate_current               103
#define CODE_rate_effiency              104
#define CODE_rate_rpm                   105
#define CODE_rate_hz                    106
#define CODE_motor_pole                 107
#define CODE_MotorCtrMode               108

#define CODE_IaOffset                   111
#define CODE_IbOffset                   112
#define CODE_u_phase_I_sense_span       113
#define CODE_v_phase_I_sense_span       114
#define CODE_I_sense_value              115
#define CODE_I_over                     116
#define CODE_Kp_IsTemp                  117
#define CODE_Ki_IsTemp                  118
#define CODE_KpIs                       119
#define CODE_KiIs                       120

#define CODE_Rs                         121
#define CODE_Rr                         122
#define CODE_Ls                         123
#define CODE_Lr                         124
#define CODE_Lm                         125
#define CODE_Jm                         126

#define CODE_accel_time1                131
#define CODE_decel_time1                132
#define CODE_speed1                     133
#define CODE_speed2                     134
#define CODE_pwm_freq                   135
#define CODE_start_ref                  136
#define CODE_EncoderPulse               137
//---
#define CODE_END                        138

#define CODE_Data_Check					800
#define CODE_Data_Backup				801
#define CODE_Data_Load					802
#define CODE_Data_Init					803
#define CODE_get_adc_offset				804

#define CODE_get_adc_vdc_low			805
#define CODE_get_adc_vdc_high			806

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
