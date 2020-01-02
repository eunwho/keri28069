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
    static int pilotLedCount =0;

    ServiceDog();
    CpuTimer0.InterruptCount++;
    if( ref_time < 1.0e+30) ref_time += 0.001;
    if( gfRunTime < 1.0e+30 ) gfRunTime += 0.001;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    pilotLedCount ++;
    pilotLedCount = ( pilotLedCount < 2000 ) ? pilotLedCount + 1 : 0 ;

    if( pilotLedCount < 250){
        SIGNAL2_SET;
    } else if ( pilotLedCount < 500 ){
        switch(gMachineState)
        {
        case STATE_READY: SIGNAL2_SET;      break;
        case STATE_RUN:   SIGNAL2_SET;      break;
        case STATE_TRIP:  SIGNAL2_CLEAR;    break;
        default:          SIGNAL2_CLEAR;    break;
        }
    } else if ( pilotLedCount < 750 ){
        switch(gMachineState)
        {
        case STATE_READY:   SIGNAL2_SET;    break;
        case STATE_RUN:     SIGNAL2_CLEAR;  break;
        case STATE_TRIP:    SIGNAL2_SET;    break;
        default:            SIGNAL2_SET;    break;
        }
    } else if ( pilotLedCount < 1000 ){
        switch(gMachineState)
        {
        case STATE_READY:   SIGNAL2_SET;    break;
        case STATE_RUN:     SIGNAL2_CLEAR;  break;
        case STATE_TRIP:    SIGNAL2_CLEAR;  break;
        default:            SIGNAL2_CLEAR;  break;
        }
    } else if ( pilotLedCount < 1250 ){
        switch(gMachineState)
        {
        case STATE_READY:   SIGNAL2_CLEAR;  break;
        case STATE_RUN:     SIGNAL2_SET;    break;
        case STATE_TRIP:    SIGNAL2_CLEAR;  break;
        default:            SIGNAL2_SET;    break;
        }
    } else if ( pilotLedCount < 1500 ){
        switch(gMachineState)
        {
        case STATE_READY:   SIGNAL2_CLEAR;  break;
        case STATE_RUN:     SIGNAL2_SET;    break;
        case STATE_TRIP:    SIGNAL2_CLEAR;  break;
        default:            SIGNAL2_CLEAR;  break;
        }
    } else if ( pilotLedCount < 1750 ){
        switch(gMachineState)
        {
        case STATE_READY:   SIGNAL2_CLEAR;  break;
        case STATE_RUN:     SIGNAL2_CLEAR;  break;
        case STATE_TRIP:    SIGNAL2_CLEAR;  break;
        default:            SIGNAL2_SET;    break;
        }
    } else if ( pilotLedCount < 2000 ){
        switch(gMachineState)
        {
        case STATE_READY:   SIGNAL2_CLEAR;  break;
        case STATE_RUN:     SIGNAL2_CLEAR;  break;
        case STATE_TRIP:    SIGNAL2_CLEAR;  break;
        default:            SIGNAL2_CLEAR;  break;
        }
    }
}
