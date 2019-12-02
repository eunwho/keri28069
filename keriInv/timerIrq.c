//	Project Name 	: dcPower
//	File Name	 	: timerIrq.c
//  Start 			: 2018.0504
#include	<header.h>
#include	<extern.h>

interrupt void cpu_timer0_isr(void)
{
    static int msec=0;

    ServiceDog();
    CpuTimer0.InterruptCount++;

    if( ref_time < 1.0e+30) ref_time += 0.001;
    if( gfRunTime < 1.0e+30 ) gfRunTime += 0.001;

    if(msec >= 999 ){
        msec = 0;
        if( secRun >= 3599){
            secRun = 0;
            if ( hourRun < 23 ) hourRun ++ ;
            else { hourRun = 0; dayRun ++; }
        } else secRun ++;
    } else msec ++;

    if( gMachineState == STATE_READY ) {
        secRun = secRun % 10;
        hourRun = 0; dayRun = 0;
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
