#ifndef		__CODE_PROC_H_
#define		__CODE_PROC_H_	

#define TYPE_INTEGER		0
#define TYPE_float			1
//======================================
// Code address
//======================================

#define CODE_END                        155
#define CODE_Fw1WeCoef              154
#define CODE_Fw2On                    153
#define CODE_KiWrCoef                  152
#define CODE_KpWrCoef                  151

#define CODE_FwCoef2                  150
#define CODE_FwCoef1                  149

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

#define CODE_graphPointCh1              33
#define CODE_graphScaleCh1              34
#define CODE_graphOffsetCh1             35

#define CODE_graphPointCh2              36
#define CODE_graphScaleCh2              37
#define CODE_graphOffsetCh2             38

#define CODE_graphPointCh3              39
#define CODE_graphScaleCh3              40
#define CODE_graphOffsetCh3             41

#define CODE_graphPointCh4              42
#define CODE_graphScaleCh4              43
#define CODE_graphOffsetCh4             44

#define CODE_LpfFreq                    46
#define CODE_LpfOff                     47

#define CODE_AT_Freq_Leq_Req            50
#define CODE_AT_Time_Leq_Req            51
#define CODE_AT_Is_Coeff_Leq_Req        52
#define CODE_AT_Is_Coeff_Rs             53
#define CODE_AT_Time_Rs                 54
#define CODE_AT_DeadTimeGain            55
#define CODE_AT_Ls_Vs_RAMP              56
#define CODE_AT_Freq_Ls                 57
#define CODE_AT_Time_Ls                 58
#define CODE_OPERAND_END                61

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
#define CODE_IsMaxCoef                  116
#define CODE_I_over                     117
#define CODE_UVLevel                    118
#define CODE_OVLevel                    119

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
#define CODE_StartRef                  136
#define CODE_EncoderPulse               137
#define CODE_Base_Flux_Coeff            138
#define CODE_VoltPIOn                   139

#define CODE_wn_wr_Coeff                140
#define CODE_Kp_IsTemp                  141
#define CODE_Ki_IsTemp                  142
#define CODE_KpIs                       143
#define CODE_KiIs                       144

#define CODE_KpVsw                      145
#define CODE_KiVsw                      146
#define CODE_VswErrLimit                147
#define CODE_VsdErrLimit                148

//---

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
