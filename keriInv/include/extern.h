#ifndef		__VARIABLES_
#define		__VARIABLES_

extern int ctrlMode;
extern double dbTs;
extern double ctrlKp;
extern double ctrlKi;

extern int dayRun;
extern int hourRun;
extern int secRun;

#if USE_GRAPH
extern int graphCount;
extern int y1_data[GRAPH_NUMBER];
extern int y2_data[GRAPH_NUMBER];
#endif

// extern char monitOut[61];

extern char monitOut1[30];
extern char monitOut2[30];
extern char monitOut3[30];
extern char monitOut4[30];

extern double nativeI_out;
extern double nativeI_pri;
extern double nativeI2nd;
extern double nativeI3rd;

//--- PI control variable
extern double ctrlError;
extern double ctrlIntegral;
extern double preIntegral;
extern double phaseShiftRatio;

extern int code_run_input_select;

extern int adcIpri;
extern int adcIout;
extern int adcVout;
extern int adcVdc;

extern double nativeIout;
extern double nativeIpri;
extern double nativeVout;
extern double nativeVdc;

extern double Pout;
extern double Ipri;
extern double Iout;
extern double Vout;

extern double OC_Timer;
extern double ovpTimer;		// 2014.1016

extern double monitor[5];
extern int debug_count;
extern int test_pulse_count;

extern int convert_state;
extern unsigned int igbt_fault_input;
extern unsigned int digital_input;

extern unsigned int DIGITAL_INPUT_START;
extern double  DCLINK_LIMIT;
extern double  UNDER_DC_LINK_LIMIT;

extern int timer0_count;

// hjkim
//'all pass Filter

//''''''''''''''''''''''''''
#define  DF(x_in, x_in1, x_in2, y_out, y_out1, y_out2, b1, b2, a0, a1, a2) \
            (y_out) = - (b1)*(y_out1) - (b2)*(y_out2) + (a0)*(x_in) + (a1)*(x_in1) + (a2)*(x_in2); \
            (y_out2) = (y_out1); \
            (y_out1) = (y_out); \
            (x_in2) = (x_in1); \
            (x_in1) = (x_in)

extern unsigned int Fault_Code;

extern int init_charge_flag;
extern double lpfIoutIn[3], lpfIoutOut[3],lpfIoutK[4];
extern double lpfVoutIn[3], lpfVoutOut[3],lpfVoutK[4];
extern double lpfVdcIn[3],  lpfVdcOut[3], lpfVdcK[4];

extern unsigned int Fault_Code;
extern double * dac_point[200];

extern int scib_rx_msg_flag;
extern int scic_rx_msg_flag;

extern double analog_ref_a;
extern double analog_ref_b;

extern double phaseVref;
extern double VdcScale;
extern double VdcOffset;

extern double VoutScale;
extern double VoutOffset;

extern double ref_time;	// 2009.10.28

extern CODE_INFO code_inform;
extern union PROTECT_FLAG protect_reg;
extern char TripMessage[25];
// PWM
extern double	DutyRatio[3];
extern Uint16 DutyCount[3];
extern double 	gfRunTime;
extern double	Ts;
extern double	inv_Ts;
extern int timer0_count;
// Ref.
extern double   refer_in0;
extern double	reference_in;
extern double	reference_out;
extern double	Vdc;
// Sci.c
extern char gStr1[50];
extern char gStr2[10];
extern int gSciInFlag;
extern int scia_rx_msg_flag;
extern char gSciaRxBuf[SCIA_RX_BUF_MAX+1];
extern char gSciaTxBuf[SCIA_TX_BUF_MAX+1];

extern int gMachineState;
extern int	gPWMTripCode;
extern int adc_result[4];
extern int giAdcVdc	;

extern TRIP_INFO TripInfo;
extern TRIP_INFO TripInfoNow;

extern int gTripFlag;
extern Uint16	MAX_PWM_CNT;
extern char MonitorMsg[30];
extern int gRunFlag;
extern int gTripSaveFlag;
extern double OverCurLimit;
extern int EepromSaveFlag;
extern int Flag_TripDataBackup;

extern double	inv_code_dac_scale_ch1;
extern double	inv_code_dac_scale_ch2;
extern double	inv_code_dac_scale_ch3;
extern double	inv_code_dac_scale_ch4;

extern double code_adc_vdc_low;          // 710
extern double code_adc_vdc_high;     // 711
extern double code_Vdc_calc_low;     // 712
extern double code_Vdc_calc_high;        // 713

extern double code_adc_Vout_low;     // 715
extern double code_adc_Vout_high;        // 716
extern double code_Vout_calc_low;        // 717
extern double code_Vout_calc_high;       // 718

extern double codeVdcOffset;         // 410
extern double codeVdcSpan;               // 411
extern double codeVoutOffset;            // 412
extern double codeVoutSpan;          // 413
//============================================
//   CODE variable 
//============================================
extern double code_I_out_ref;	    // 0
extern double code_Vout;             // 1
extern double code_VoutLimit;	    // 2
extern double code_ovpTime;		    // 3
extern double codeOcTime;           // 4
extern double codePwmPhaseInit;	    // 5
extern double codeInitTime;		    // 6

extern double code_ctrl_mode;        // 10
extern double codeSetPulseNumber;	// 11
extern double code_testPwmPhase;		// 12
extern double code_set_Vdc_on;       // 13
extern double codeIoutAdcOffset;     // 14
extern double codeIpriAdcOffset;     // 15
extern double codeIoutScale;         // 16
extern double codeIpriScale;         // 17
extern double code_protect_inhibit_on;   // 18

extern double Is_Max_Coeff;				// 206
extern double code_OC_time;				// 207

///////////////////////////


extern double code_Ki;					// 510
extern double code_Kp;					// 511
extern double code_integLimit;			// 512
extern double code_phaseMax;			// 513


extern double Data_Check;				// 800
extern double Data_Backup;				// 801
extern double Data_Load;				// 802
extern double Data_Init;				// 803
//***********************************************************
#endif

