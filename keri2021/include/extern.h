#ifndef     __VARIABLES_
#define     __VARIABLES_

extern double Id_err_ki_delay1;
extern double ud_ki_delay1;
extern double d_current_anti_windup;

extern double q_current_anti_windup;
extern double Iq_err_ki_delay1;
extern double uq_ki_delay1;

extern double speed_anti_windup;
extern double speed_err_ki_delay1;
extern double speed_ki_delay1;

extern int searchPosFlag;
extern int32 posCountOrigin;
extern double inv_QepTime;

extern double codeFw1WeCoef;
extern double codeFw2On;

extern double codeKiWrCoef;
extern double codeKpWrCoef;

extern double KpVsw;
extern double KiVsw;

extern double codeFwCoef1;
extern double codeFwCoef2;
extern double codeTestCoef1;
extern double codeTestCoef2;
extern double IsqFw;
extern double lpfVsdIn[3];
extern double lpfVsdOut[3];
extern double lpfVsdK[4];

extern int digitalInputState;
extern int pwmTripState;

extern int graphPointCh1;
extern int graphPointCh2;
extern int graphPointCh3;
extern int graphPointCh4;
extern double invGraphScaleCh1;
extern double invGraphScaleCh2;
extern double invGraphScaleCh3;
extern double invGraphScaleCh4;

extern double inv_Lm;
extern double Is_Scalar;
extern double Is_Square;
extern double Isd_Square;
extern double Isq_Square;

extern double Is_D_Rate;
extern double IsD_Ref;
extern double IsQ_Ref;

extern double Vs_Square;
extern double Vs_Scalar;
extern double Vsd_Square;
extern double Vsq_Square;

extern double Vsw_ErrInt;
extern double Vsd_ErrInt;
extern double we1FieldWeak;

extern double invePowerScale;
extern double inveIrmsScale;

//--- eQep.c
extern Uint32 capture_counter ;
extern Uint16 encoderMaxCount;
extern int32     POSCNT_old;

extern double inv_encoderMaxCount;
extern double Inv_QepTime;

//---  testing
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
//extern double  wr_rat;
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
extern double  Is_rat;
extern double  inv_Is_rat;
extern double  Is_max;
extern double  Is_mag;
extern double  Is_mag_rms;
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

//Sensored vector control
extern double we_FW_Coeff;
extern double we_FW1_Coeff;

extern double Fr_B;
extern double inv_Fr_B;
extern double ROTOR_ANGLE_PER_PULSE;

extern double Fr_Cycle;
extern int Fr_CycleIndex;
extern double HalfExcitationTime;
extern double inv_GM_Fr;
extern double inv_GM_Fr_square_minus_1;
extern double Ki_Fr;
extern double Kp_Fr;
extern double Kp_Fr_Coeff;

extern double wp_Fr_Coeff;
extern double wp_Fr;

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

extern int scib_tx_start_addr;
extern int scib_tx_end_addr;
extern int scib_rx_msg_flag;

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
extern int adc_result[16];
extern int adcCurrentA;
extern int adcCurrentB;
extern int adcVdc;
extern int adcIgbtTemperature;
extern int adcExSensor;
extern int adcCmdAnalog;

//filter
extern double lpfIsqIn[3];
extern double lpfIsqOut[3];
extern double lpfIsqK[4];

extern double lpfVsIn[3];
extern double lpfVsOut[3];
extern double lpfVsK[4];

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

extern double codeKpIs;                   // 83
extern double codeKiIs;                   // 84
extern double fw2Base;
extern double inv_sigma;
extern double inv_we_rat;

extern double invCodeScopeScaleCh1;
extern double invCodeScopeScaleCh2;
extern double invCodeScopeScaleCh3;
extern double invCodeScopeScaleCh4;

//============================================
//   CODE variable 
//============================================
extern double codeSetVdc;
extern double codeProtectOff;

extern double codeIsMaxCoef;
extern double code_motorId;
extern double code_adc_Vdc_low;
extern double code_adc_Vdc_high;
extern double code_Vdc_calc_low;
extern double code_Vdc_calc_high;
//--- code 11
extern double codeRampTest;            // 11
extern double posi_duration_time;
extern double zero_duration_time;
extern double nega_duration_time;
extern double test_accel_time;
extern double test_decel_time;
//--- da graph setting
extern double codeScopeLoopCount;
//---
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

extern double codeGraphPointCh1;
extern double codeGraphScaleCh1;
extern double codeGraphOffsetCh1;

extern double codeGraphPointCh2;
extern double codeGraphScaleCh2;
extern double codeGraphOffsetCh2;

extern double codeGraphPointCh3;
extern double codeGraphScaleCh3;
extern double codeGraphOffsetCh3;

extern double codeGraphPointCh4;
extern double codeGraphScaleCh4;
extern double codeGraphOffsetCh4;

extern double FW_VoltageCoeff;
extern double Base_Flux_Coeff;
extern double codeLpfFreq;
extern double codeLpfOff;

extern double code_KiWrCoef;

//--- code 70
extern double AT_Freq_Leq_Req;
extern double AT_Time_Leq_Req;
extern double AT_Is_Coeff_Leq_Req;
extern double AT_Is_Coeff_Rs;
extern double AT_Time_Rs;
extern double AT_DeadTimeGain;
extern double AT_Ls_Vs_RAMP;
extern double AT_Freq_Ls;
extern double AT_Time_Ls;
extern double codeTestCoeff1;
extern double codeTestCoeff2;

//===========================================
//--- motor and related parameter setting
//===========================================
extern double codeRatePower;          // 1
extern double codeRateVolt;           // 2
extern double codeRateCurrent;        // 3
extern double codeRateEffiency;       // 4
extern double codeRateRpm;            // 5
extern double codeRateHz;             // 6
extern double codeMotorPole;          // 7
extern double codeMotorCtrlMode;      // 8

extern double codeIaOffset;         // 11
extern double codeIbOffset;         // 12
extern double codeIUSpan;           // 13
extern double codeIVSpan;           // 14
extern double codeISensorValue;     // 15
extern double codeIOver;            // 16
extern double codeKpIsTemp;         // 17
extern double codeKiIsTemp;         // 18
extern double codeKpIsCoeff;        // 19
extern double codeKiIsCoeff;        // 20

extern double Rs;                 // 21
extern double Rr;                 // 22
extern double Ls;                 // 23
extern double Lr;                 // 24
extern double Lm;                 // 25
extern double Jm;                 // 26

extern double codeAccelTime1;         // 31
extern double codeDecelTime1;         // 32
extern double codeSpeed1;             // 33
extern double codeSpeed2;             // 34
extern double codePwmFreq;            // 35
extern double codeStartRef;         // 36
extern double code_encoderPulse;      // 37

extern double codeIOver;            //
extern double codeUnderVoltLevel;            //
extern double codeOverVoltLevel;            //

extern double wn_wr_Coeff;
extern double codeVoltPIOn;
extern double codeKpVsw;
extern double codeKiVsw;
extern double codeVswErrLimit;
extern double codeVsdErrLimit;

//--- end of motor related parameter

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
