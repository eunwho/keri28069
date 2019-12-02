//
// project	: back to back inverter 
// pcb		: dfig_dsp.0104.BK.sch ~pcb
// work dir : d:\dspBack2back\InvCon\src
// date		: 2013.0111 Friday
// 			by Soonkil Cheoung. CEO Eunwho Power Electronics

#include	<header.h>
#include	<extern.h>

#define LPF_ZETA 0.707

double lpfIoutIn[3], lpfIoutOut[3],lpfIoutK[4];
double lpfVoutIn[3], lpfVoutOut[3],lpfVoutK[4];
double lpfVdcIn[3],lpfVdcOut[3],lpfVdcK[4];

void lpf2ndCoeffInit( double cutoff_freq, double T_sample, double *x, double *y, double *k)
{
    double omega_n;
    omega_n = 2.0 * PI * cutoff_freq ;
    * x = * (x + 1) = *(x + 2 ) = 0.0 ;
    * y = * (y + 1) = *(y +2) = 0.0 ;
    * k = 1./ (4.+4.* LPF_ZETA * omega_n * T_sample + omega_n * omega_n * T_sample * T_sample);
    *(k+1) = 8.0 - 2.0 * omega_n * omega_n * T_sample * T_sample;
    *(k+2) = 4.0 * LPF_ZETA * omega_n * T_sample - omega_n * omega_n * T_sample * T_sample -4.0;
    *(k+3) = omega_n * omega_n * T_sample * T_sample;
}
void lpf2nd(double * x,double * y, double * K)
{
    int i;
    double k[4];
    for ( i = 0 ; i< 4; i++)    k[i] = *(K + i);
    *y = k[0]*( k[1]*( *(y+1)) + k[2]*( *(y+2)) + k[3]*( (*x) + 2.*(*(x+1)) + (*(x+2))) );
    *(y+2) = *(y+1);    *(y+1) = * y;
    *(x+2) = *(x+1);    *(x+1) = * x;
}
// end of low_pass_filter
