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

    ServiceDog();

    if ( scrGatePulse < 2 ) {
        scrGatePulse ++;
        G_INIT_CLEAR;
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
        return;
    }

    scrGatePulse = 0;

    if( gMachineState == STATE_POWER_ON ) G_INIT_SET;

    CpuTimer0.InterruptCount++;
    if( ref_time < 1.0e+30) ref_time += 0.001;
    if( gfRunTime < 1.0e+30 ) gfRunTime += 0.001;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}
