#ifndef		__GLOBAL_VARIABLES_
#define		__GLOBAL_VARIABLES_

int ctrlMode;
double dbTs;
double ctrlKp;
double ctrlKi;

#if USE_GRAPH
int graphCount=0;
int y1_data[GRAPH_NUMBER];
int y2_data[GRAPH_NUMBER];
#endif

char monitOut1[30];
char monitOut2[30];
char monitOut3[30];
char monitOut4[30];

double under_volt_set;
double nativeI_out;
double nativeI_pri;
//--- PI control

double ctrlError;
double ctrlIntegral;
double preIntegral;
double phaseShiftRatio;

int code_run_input_select;
double OC_Timer;
double ovpTimer;

double nativeIout;
double nativeIpri;
double nativeVout;
double nativeVdc;

double Pout;
double Ipri;
double Iout;
double Vout;

int adcIpri;
int adcIout;
int adcVout;
int adcVdc;

double monitor[5]={0.0};
int debug_count;
int test_pulse_count;

unsigned int igbt_fault_input;
unsigned int digital_input;

int timer0_count;

unsigned int debug1;
int init_charge_flag = 0;

int scib_rx_msg_flag = 0;
int scic_rx_msg_flag = 0;

double analog_ref_a;
double analog_ref_b;
//---
double * dac_point[200];
double dac_ch0_unit_count_value;
double dac_ch1_unit_count_value;
double dac_ch2_unit_count_value;
double dac_ch3_unit_count_value;

double	inv_code_dac_scale_ch1;
double	inv_code_dac_scale_ch2;
double	inv_code_dac_scale_ch3;
double	inv_code_dac_scale_ch4;
//===================

int dayRun ;
int hourRun ;
int secRun;

double phaseVref;
double VdcScale;
double VdcOffset;
double VoutScale;
double VoutOffset;

double ref_time;
CODE_INFO code_inform = {0,0,0,0,0,0,{0}};

union PROTECT_FLAG protect_reg;

int terminal_input_state;

// PWM
double	DutyRatio[3];
Uint16 DutyCount[3];

double	Ts;
double	inv_Ts;
double 	gfRunTime=0;
int timer0_count;
double	Vdc=0.0;
double	Vs_max=0.0;

double refer_in0;
double	reference_in=0.0;
double	reference_out=0.0;
//--- Sci.c
char gStr1[50] = {0};
char gStr2[10] = {0};
int gSciInFlag;
char gSciaRxBuf[SCIA_RX_BUF_MAX+1];
char gSciaTxBuf[SCIA_TX_BUF_MAX+1];
int gMachineState=0;
int	gPWMTripCode;
int adc_result[4]={0};
int	giAdcVdc	;
TRIP_INFO TripInfo = {0,0,0,0,0," No Trip Data       "};
TRIP_INFO TripInfoNow = {0,0,0,0,0," No Trip Data       "};

int gTripFlag = 0;
Uint16	MAX_PWM_CNT;

char MonitorMsg[30]={0};

int gRunFlag=0;
int gTripSaveFlag=0;
int EepromSaveFlag = 0;
int Flag_TripDataBackup = 0;
double OverCurLimit;

double codeVdcOffset;
double codeVdcSpan;
double codeVoutOffset;
double codeVoutSpan;

double code_Ki=50.0;
double code_Kp=0.2;

double code_integLimit=1.0;
double code_phaseMax=0.7;

double codeVdcOffset;
double codeVdcSpan;
double codeVoutOffset;
double codeVoutSpan;

double code_adc_vdc_low;
double code_adc_vdc_high;
double code_Vdc_calc_low;
double code_Vdc_calc_high;

double code_adc_Vout_low;
double code_adc_Vout_high;
double code_Vout_calc_low;
double code_Vout_calc_high;

int code_protect_uv_off = 0;
int code_protect_ov_off = 0;
int code_protect_Iadc_off = 0;
int code_protect_over_I_off = 0;
int code_protect_IGBT_off =0;
int code_protect_ex_trip_off=0;

//============================================
//   CODE variable 
//============================================
double code_I_out_ref;        // 0
double code_Vout;             // 1
double code_VoutLimit;        // 2
double code_ovpTime;          // 3
double codeOcTime;           // 4
double codePwmPhaseInit;      // 5
double codeInitTime;          // 6

double code_ctrl_mode;        // 10
double codeSetPulseNumber;    // 11
double code_testPwmPhase;     // 12
double code_set_Vdc_on;       // 13
double codeIoutAdcOffset;     // 14
double codeIpriAdcOffset;     // 15
double codeIoutScale;         // 16
double codeIpriScale;         // 17
double code_protect_inhibit_on;   // 18

double Data_Check;				// 800
double Data_Backup;				// 801
double Data_Load;				// 802
double Data_Init;				// 803
//=====================================================
#endif

