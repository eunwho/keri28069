#include	<header.h>
#include	<extern.h>

/* current */
#define SCOPE_I_d          0
#define SCOPE_I_q          1
#define SCOPE_I_D          2
#define SCOPE_I_Q          3

#define SCOPE_I_U          4
#define SCOPE_I_V          5
#define SCOPE_I_W          6

/* voltage */
#define SCOPE_V_d          7
#define SCOPE_V_q          8
#define SCOPE_V_D          9
#define SCOPE_V_Q          10

#define SCOPE_V_U          11
#define SCOPE_V_V          12
#define SCOPE_V_W          13

#define SCOPE_ADC_IU       14
#define SCOPE_ADC_IV       15
#define SCOPE_ADC_VDC      16
#define SCOPE_ADC_TEMP     17
#define SCOPE_ADC_SENSOR   18
#define SCOPE_ADC_CMD      19

#define SCOPE_DUTY_U       20
#define SCOPE_DUTY_V       21
#define SCOPE_DUTY_W       22

#define SCOPE_Fs       23
#define SCOPE_Fs_d       24
#define SCOPE_Fs_q       25

#define SCOPE_Iref_D       26
#define SCOPE_Iref_Q       27

#define SCOPE_Vref_D       28
#define SCOPE_Vref_Q       29

#define SCOPE_THETA             30
#define SCOPE_THETA_M         31
#define SCOPE_SIN_THETA         32
#define SCOPE_COS_THETA        33

#define SCOPE_We        34
#define SCOPE_Wr        35
#define SCOPE_Wr_M        36

#define SCOPE_I_DS0_0     40
#define SCOPE_I_DS0       41



void setScopePoint()
{
    scopePoint[SCOPE_I_d] = &Is_dq[ds];
    scopePoint[SCOPE_I_q] = &Is_dq[qs];
    scopePoint[SCOPE_I_D] = &Is_DQ[DS];
    scopePoint[SCOPE_I_Q] = &Is_DQ[QS];

    scopePoint[SCOPE_I_U] = &Is_abc[as];
    scopePoint[SCOPE_I_V] = &Is_abc[bs];
    scopePoint[SCOPE_I_W] = &Is_abc[cs];

/* voltage */
    scopePoint[SCOPE_V_d] = &Vs_dq[ds];
    scopePoint[SCOPE_V_q] = &Vs_dq[qs];
    scopePoint[SCOPE_V_D] = &Vs_DQ[DS];
    scopePoint[SCOPE_V_Q] = &Vs_DQ[QS];

    scopePoint[SCOPE_V_U] = &Vs_abc[as];
    scopePoint[SCOPE_V_V] = &Vs_abc[bs];
    scopePoint[SCOPE_V_W] = &Vs_abc[cs];

    scopePoint[SCOPE_ADC_IU]        = &dAdcIa;
    scopePoint[SCOPE_ADC_IV]        = &dAdcIb;
    scopePoint[SCOPE_ADC_VDC]       = &dAdcVdc;
    scopePoint[SCOPE_ADC_TEMP]      = &dAdcTemp;
    scopePoint[SCOPE_ADC_SENSOR]    = &dAdcSens;
    scopePoint[SCOPE_ADC_CMD]       = &dAdcCmd;

    scopePoint[SCOPE_DUTY_U]       = &DutyRatio[u];
    scopePoint[SCOPE_DUTY_V]       = &DutyRatio[v];
    scopePoint[SCOPE_DUTY_W]       = &DutyRatio[w];

    scopePoint[SCOPE_Fs]       = &Fs;
    scopePoint[SCOPE_Fs_d]       = &Fs_dq[ds];
    scopePoint[SCOPE_Fs_q]       = &Fs_dq[qs];

    scopePoint[SCOPE_Iref_D]       = &Is_DQ_ref[DS];
    scopePoint[SCOPE_Iref_Q]       = &Is_DQ_ref[QS];

    scopePoint[SCOPE_Vref_D]       = &Vs_DQ_ref[DS];
    scopePoint[SCOPE_Vref_Q]       = &Vs_DQ_ref[QS];

    scopePoint[SCOPE_THETA]       = &theta;
    scopePoint[SCOPE_THETA_M]       = &theta_m;
    scopePoint[SCOPE_SIN_THETA]       = &SinTheta;
    scopePoint[SCOPE_COS_THETA]       = &CosTheta;

    scopePoint[SCOPE_We]       = &we;
    scopePoint[SCOPE_Wr]       = &wr;
    scopePoint[SCOPE_Wr_M]   = &wr_m;

    scopePoint[SCOPE_I_DS0_0]   = &I_DS0_0;
    scopePoint[SCOPE_I_DS0]   = &I_DS0;
}

//--- end of file
