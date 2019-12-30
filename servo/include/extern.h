#ifndef     __VARIABLES_
#define     __VARIABLES_


extern int adcCurrentA;
extern int adcCurrentB;
extern int adcVdc;

// pmsmCtrl.c

extern Uint16 encoderMaxCount;
extern double inv_encoderMaxCount;
extern double inv_QepTime;
extern int32 POSCNT_old;

extern double KP_POSITION;
extern double KP_SPEED;
extern double KI_SPEED;
extern double KP_CURRENT_Q;
extern double KI_CURRENT_Q;
extern double KP_CURRENT_D;
extern double KI_CURRENT_D;

extern double POS_REF;
extern double POS_REAL;
extern double POS_REAL_delay1;
extern double POS_ERR;
extern double POS_REF_OFFSET;
extern double SPEED_REF;
extern double SPEED_REAL;
extern double SPEED_ERR;

extern double MAX_SPEED;

extern double uspeed_kp;
extern double speed_err_ki;
extern double speed_err_ki_delay1;
extern double speed_anti_windup;
extern double uspeed_ki;
extern double uspeed_ki_delay1;
extern double uspeed_IP;
extern double torque_real;

extern double ud_kp;
extern double ud_ki;
extern double ud_ki_delay1;
extern double ud_IP;
extern double Id_err;
extern double Id_err_delay1;
extern double Id_real;
extern double Id_ref;
extern double Id_err_ki;
extern double Id_err_ki_delay1;
extern double d_current_anti_windup;

// extern double Vs_MAX = 310.0; //'300.0/sqrt(3)*0.95
// extern double Vq_MAX = 290.0;//156.7641541; //'sqrt(Vs_MAX^2-Vd_MAX^2)
extern double uq_kp;
extern double uq_ki;
extern double uq_ki_delay1;
extern double uq_IP;
extern double Iq_err;
extern double Iq_err_delay1;
extern double Iq_ref;
extern double Iq_err_ki;
extern double Iq_err_ki_delay1;
extern double q_current_anti_windup;
extern double Vq_real;

extern double Torque_MAX;
extern double ACC_MAX;

extern Uint16 enc_flag;

extern double POS_REF_OLD;
extern double POS_REF_NEW;
extern double POS_INIT;
extern double prof_t1;
extern double prof_t2;
extern double prof_t3;
extern double profile_gen_time;
extern int profile_FLAG;
extern int SIGN_FLAG;
extern int cal_FLAG;
extern double Dist_New;
extern double Dist_min;
extern double init_t1;
extern double init_t2;
extern double SPEED_M;

extern double SPD_REF_PLC;

extern Uint16 POS_INIT_FLAG;



// testing
extern int lpfadcIa;
extern int lpfadcIb;

extern double exSensRef;

extern double dAdcIa;
extern double dAdcIb;
extern double dAdcVdc;
extern double dAdcTemp;
extern double dAdcSens;
extern double dAdcCmd;

extern double * scopePoint[50];

// control and flag
extern CODE_INFO code_inform;
extern union PROTECT_FLAG protect_reg;
extern union DIGITAL_FUNCTION func_flag;
extern union DIGITAL_OUT_FUNC relay_flag;
extern TRIP_INFO TripInfo;
extern TRIP_INFO TripInfoNow;
extern int terminal_input_state;
extern char MonitorMsg[25];

// flag
extern int init_charge_flag;
extern int gRunFlag;
extern int gTripFlag;
extern int gTripSaveFlag;
extern int gTripSavePoint;
extern int gPWMTripCode;
extern int Flag_TripDataBackup;
extern int EepromSaveFlag;

extern int gMachineState;
extern int gControlMode;
extern int gDeChargeFlag;

extern int sendAdcDataFlag;
extern int scopeCount;
extern UNION16 scopeData[4][SCOPE_MAX_NUMBER];

// reference
extern double  reference_in;
extern double  reference_out;
extern double  analog_ref;
extern double  AnaCmdReference;
extern double  IncScanRef;
extern double  IncRef;
extern double  DecRef;

// count and time

extern int     timer0_count;
extern Uint16  MAX_PWM_CNT;
extern double  inv_MAX_PWM_CNT;
extern Uint16  DutyCount[3];
extern double  DutyRatio[3];
extern double  GainUpdateTimer;

extern double  Ts;
extern double  inv_Ts;
extern double  gfRunTime;
extern double  ref_time;
extern unsigned long   gulStartCount;
extern unsigned int    gStartInitFinish;

// frequency
extern double  P_pair;
extern double  inv_P_pair;

extern double  Freq_rat;
extern double  inv_Freq_rat;
extern double  inv_motor_rate_hz;
extern double  Freq_ref;
extern double  Freq_set;
extern double  frequency;
extern double  Freq_out;

extern double  Freq_slip_rat;
extern double  Freq_slip;

extern double  rpmOut;
extern double  rpm;
extern double  rpm_ref;
extern double  rpm_err;
extern double  rpm_Coeff;
extern double  rpm_m;

// angle
extern double  we_rat;
extern double  we;
extern double  we0;
extern double  we_in;
extern double  we_FW;
extern double  we_FW1;

extern int     wr_ctrl_index;
extern int     wr_CycleIndex;
extern double  wr;
extern double  wr_rat;
extern double  wr_ref;
extern double  wr_ref0;
extern double  wr_err;
extern double  wr_ErrInt;

extern double  wr_Cycle;
extern double  w_sl;
extern double  w_sl0;
extern double  Delta_wr;
extern double  Delta_wr_Filter_Pole;

extern double  wm_rat;
extern double  wr_m;
extern double  wr_m0;

extern double  theta;
extern double  theta_m;
extern double  SinTheta;
extern double  CosTheta;
extern double  SinTheta1;
extern double  CosTheta1;
extern double  SinDeltaTheta;
extern double  CosDeltaTheta;
extern double  SinCosDeltaTheta;
extern double  inv_SinCosDeltaTheta;
extern double  DeltaLambda;
extern double  DeltaTheta;

// Current
extern double  OverCurLimit;
extern double  Is_rat;
extern double  inv_Is_rat;
extern double  Is_max;
extern double  Is_mag;
extern double  Is_mag_rms;
extern double  LPF_Ia;
extern double  sgn_Is[3];
extern double  sgn_I_QS;

extern double  Is_abc[3];
extern double  Is_dq[2];
extern double  Is_dq_ref[2];
extern double  Is_dq_ErrInt[2];

extern double  Is_DQ[2];
extern double  Is_DQ_ref[2];
extern double  Is_DQ_max[2];
extern double  Is_DQ_ErrInt[2];
extern double  prev_I_QS;
extern double  I_DS0;
extern double  I_DS0_0;
extern double  I_DS_err;
extern double  Is_Leq_Req;

// Voltage
extern double  Vs_rat;
extern double  Vdc;
extern double  Vs_ref;
extern double  sensVdc;
extern double  Vdc_factor;          // 2010 01 13
extern double  Vdc_calc_offset;     // 2010 01 13 for Vdc calc
extern double  Vs_Coeff_Leq_Req;

extern double  Vs_abc_ref[3];
extern double  Vs_abc[3];
extern double  Us_dq[2];
extern double  Vs_dq[2];
extern double  Vs_DQ[2];

extern double  Vs_max;
extern double  Vs_abc[3];
extern double  Vs_abc_ref[3];
extern double  Vs_dq[2];
extern double  Vs_dq_ref[2];
extern double  Vo;                 // zero sequence
extern double  Us_dq[2];
extern double  Vs_DQ[2];
extern double  Vs_DQ_max[2];
extern double  Vs_DQ_ref[2];
extern double  Vs_DQ_comp[2];
extern double  Vs_max_FW;
extern double  Vs_DQ_ref_P[2];
extern double  Vs_DQ_ref_PI[2];
extern double  Vs_IR_comp;
extern double  del_Vs_comp;

// power and torque
extern double Te_rat;
extern double inv_Te_rat;
extern double Kt;
extern double inv_Kt;
extern double S_lin;
extern double S_rat;
extern double  Pf;
extern double  Slip;
extern double  Power_core;
extern double  Power_core_rat;
extern double  Power_gap;

extern double  Re_Power;
extern double  Im_Power;
extern double  P_total;

extern double  Te_max;
extern double  Te_ref;
extern double  Te;
extern double  LPF_Te;
extern double  Max_Trq_Coeff;


// Flux
extern double  Fs_rat;
extern double  Fs_ref;
extern double  Fs_ref0;
extern double  inv_Fs_ref;
extern double  Fs;
extern double  inv_Fs;
extern double  Fs_dq[2];
extern double  Fs1;
extern double  Fr;
extern double  inv_Fr;
extern double  Fr_ref;
extern double  inv_Fr_ref;
extern double  Fr_ref0;
extern double  Fr_Err;
extern double  Fr_ErrInt;

// Dead Time
extern double  C_ce_nF;
extern double  C_ce;
extern double  inv_C_ce;

// Motor Name Plate Parameter

extern double  inv_motor_rat_hz;
extern double  wr_rat;
extern double  wm_rat;
extern double  Te_rat;
extern double  inv_Te_rat;
extern double  Fs_rat;
extern double  Fr_rat;
extern double  Kt;
extern double  inv_Kt;
extern double  P_pair;
extern double  inv_P_pair;
extern double  rpm_Coeff;

// Machine Parameter
extern double  sigma;
extern double  sigma_Ls;
extern double  SlipCoeff;
extern double  inv_sigma_Tr;
extern double  sigma_Tr;
extern double  sigma_minus_1_div_sigma_Ls;
extern double  inv_sigma_Ls;
extern double  inv_Ls;
extern double  Tr;
extern double  inv_Tr;
extern double  inv_Ls_plus_sigma_Ls;
extern double  sigma_Ls_div_1_plus_sigma;
extern double  Lm_div_Lr;                      // Lm/Lr
extern double  Lr_div_Lm;                      // Lr/Lm

// Vector Control with/out sensor
extern double  wn_wr;
extern double  I_QS_rat;
extern double inv_I_QS_rat;

// V/F
extern double  S_rat;
extern double  S_lin;
extern double  Freq_slip_rat;

//
extern double  Kp_wr;
extern double  Ki_wr;

extern double  Fs_B;
extern double  inv_Fs_B;

extern double  wr_FilterPole;
extern unsigned AutoTuningFlag;
extern double  Jm_SampleData[2];
extern double  Jm_ID_wr[4];
extern double  Jm_ID_Te[4];
extern double  Jm_ID_t[4];

extern double  Req;
extern double  Leq;

extern double  GainUpdateTimer;
extern double  Vs_Coeff_Leq_Req;

extern double LPF_Is;
extern double LPF_Is_Square;
extern double LPF_Vs_Square;
extern double LPF_Re_Power;

extern double  Is_Leq_Req;
extern double Freq_rat;
extern double inv_Freq_rat;

// Sci.c
extern int scib_rx_msg_flag;
extern int scic_rx_msg_flag;

extern int scia_tx_start_addr;
extern int scia_tx_end_addr;
extern int scia_rx_msg_flag;

extern char gStr1[50];
extern char gStr2[10];

extern int gSciInFlag;

extern char gSciaRxBuf[NUM_SCI_RX_BUF+1];
extern char gSciaTxBuf[NUM_SCI_TX_BUF+1];

extern int gSciaTxInPoint;
extern int gSciaTxOutPoint;
extern int gSciaTxEndFlag;

extern int giSciCmdFunction;
extern int giSciCmdAddr;
extern double gdouSciCmdData;

// analog to digital converter
extern int adc_result[6];
extern int adcIa;
extern int adcIb;
extern int adcVdc;
extern int adcIgbtTemperature;
extern int adcExSensor;
extern int adcCmdAnalog;

//filter
extern double lpfIa;
extern double lpfIb;

extern double lpfIrmsCutOffRreq;
extern double lpfIaIn[3];
extern double lpfIaOut[3];
extern double lpfIrmsK[4];
//double lpfIrmsCutOffRreq = 1.0;
extern double lpfIbIn[3];
extern double lpfIbOut[3];

extern double lpfVdc;
extern double lpfVdcCutoffFreq;
extern double lpfVdcIn[3];
extern double lpfVdcOut[3];
extern double lpfVdcK[4];

//============================================
//   CODE variable 
//============================================
extern double   codeMotorDirection;     // 1
extern double   codeAccelTime1;         // 2
extern double   codeDecelTime1;         // 3
extern double   codeMotorCtrlMode;      // 4
extern double   code_start_ref;         // 5
extern double   codeSpeed1;             // 6
extern double   codeSetVdc;             // 7
extern double   codeProtectOff;         // 8
extern double   codePwmFreq;            // 9

extern double   codeRatePower;          // 10
extern double   codeRateCurrent;        // 11
extern double   codeRateRpm;            // 12
extern double   codeRateVolt;           // 13
extern double   codeRateEffiency;       // 14
extern double   codeRateHz;             // 15
extern double   codeMotorPole;          // 16
extern double   codePresSensRef;        // 17

extern double   codeIaOffset;           // 20
extern double   codeIbOffset;           // 21

extern double I_sense_value;           // 22
extern double u_phase_I_sense_span;    // 23
extern double v_phase_I_sense_span;    // 24
extern double vdc_sense_zero;          // 25
extern double vdc_sense_span;          // 26


extern double code_adc_Vdc_low;        // 36
extern double code_adc_Vdc_high;       // 37
extern double code_Vdc_calc_low;       // 38
extern double code_Vdc_calc_high;      // 39

extern double VF_DeadTimeGain;         // 40
extern double VF_ExcitationTime;       // 41
extern double VF_Fs_Coeff;             // 42
extern double VF_Freq_TrqBoost;        // 43
extern double VF_Vs_Coeff_TrqBoost;    // 44
extern double VF_Rs_ThermalCoeff;      // 45
extern double VF_IR_Comp_FilterPole;   // 46
extern double VF_Slip_Comp_FilterPole; // 47
extern double VF_Rs;                   // 48

extern double code_kpPosi;
extern double code_kpSpeed;
extern double code_kiSpeed;
extern double code_kpIdq;
extern double code_kiIdq;
extern double code_encoderPulse;

extern double codeScopeLoopCount;

extern double codeScopePointCh1;
extern double codeScopeScaleCh1;
extern double codeScopeOffsetCh1;

extern double codeScopePointCh2;
extern double codeScopeScaleCh2;
extern double codeScopeOffsetCh2;

extern double codeScopePointCh3;
extern double codeScopeScaleCh3;
extern double codeScopeOffsetCh3;

extern double codeScopePointCh4;
extern double codeScopeScaleCh4;
extern double codeScopeOffsetCh4;

// end of code
extern double invCodeScopeScaleCh1;
extern double invCodeScopeScaleCh2;
extern double invCodeScopeScaleCh3;
extern double invCodeScopeScaleCh4;

extern int scopeLoopCount;
extern int scopePointCh1;
extern int scopePointCh2;
extern int scopePointCh3;
extern int scopePointCh4;

extern double under_volt_set;          // 302
extern double over_speed_level;        // 303
extern double e_thermal_level;         // 304
extern double pre_charge_time;         // 305
extern double over_I_time;             // 307

extern double code_Vdc_scaler;         // 308  2011.0613
extern double code_Vdc_offseter;       // 309

extern double Data_Check;              // 800
extern double Data_Backup;             // 801
extern double Data_Load;               // 802
extern double Data_Init;               // 803
#endif
