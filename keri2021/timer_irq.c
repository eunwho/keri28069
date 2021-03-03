/////////////////////////////////////////////////////////////////////////
//
//  Project Name    : Inverter for
//  Fiele Name      : timer_irq.c
//
//  Start           : 2019.12.30 Monday
//
///////////////////////////////////////////////////////////////////////////
#include    <header.h>
#include    <extern.h>

interrupt void cpu_timer0_isr(void)
{
    static int scrGatePulse =0;
    static int msCount = 0;

    msCount++;
    if(msCount > 2 ) {
        CpuTimer0.InterruptCount++;
        if( ref_time < 1.0e+30) ref_time += 0.001;
        if( gfRunTime < 1.0e+30 ) gfRunTime += 0.001;
        ServiceDog();
        msCount =0;
    }

    if ( scrGatePulse < 3 ) {
        scrGatePulse ++;
#if SCR_INIT_CHARGE
        G_INIT_CLEAR;
#endif
    } else {

        scrGatePulse = 0;
#if SCR_INIT_CHARGE
        if( gMachineState == STATE_POWER_ON ) G_INIT_SET;
        //if( gMachineState == STATE_READY ) G_INIT_SET;
#else
        G_INIT_CLEAR;
#endif
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
