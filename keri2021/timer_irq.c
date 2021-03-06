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

#if GATE_ACTIVE_LOW
interrupt void cpu_timer0_isr(void)
{
    static int pilotLedCount =0;
    static int scrGatePulse =0;
    static int msCount = 0;

    msCount++;
    if(msCount > 2 ) {
        CpuTimer0.InterruptCount++;
        if( ref_time < 1.0e+30) ref_time += 0.001;
        if( gfRunTime < 1.0e+30 ) gfRunTime += 0.001;
        ServiceDog();
        msCount =0;

        pilotLedCount ++;
        pilotLedCount = ( pilotLedCount < 2000 ) ? pilotLedCount + 1 : 0 ;
    }

    if( pilotLedCount < 250){
        G_INIT_SET;
        LED1_SET;                 // cpu run blink
        LED2_SET;                   // error blink
    } else if ( pilotLedCount < 500 ){
        switch(gMachineState)
        {
        case STATE_READY:   G_INIT_SET;     LED1_SET;       LED2_SET;   break;
        case STATE_RUN:     G_INIT_SET;     LED1_SET;       LED2_SET;   break;
        case STATE_TRIP:    G_INIT_CLEAR;   LED1_CLEAR;     LED2_CLEAR; break;
        default:
            G_INIT_CLEAR;
            LED1_CLEAR; LED2_CLEAR;
            break;
        }
    } else if ( pilotLedCount < 750 ){
        switch(gMachineState)
        {
        case STATE_READY: G_INIT_SET;   LED1_SET;   LED2_SET; break;
        case STATE_RUN:   G_INIT_CLEAR; LED1_CLEAR; LED2_SET; break;
        case STATE_TRIP:  G_INIT_SET;   LED1_SET;   LED2_CLEAR; break;
        default:          G_INIT_SET;   LED1_SET;   LED2_CLEAR; break;
        }
    } else if ( pilotLedCount < 1000 ){
        switch(gMachineState)
        {
        case STATE_READY:   G_INIT_SET;  LED1_SET; LED2_SET;  break;
        case STATE_RUN:     G_INIT_CLEAR; LED1_CLEAR; LED2_SET; break;
        case STATE_TRIP:    G_INIT_CLEAR; LED1_CLEAR; LED2_CLEAR; break;
        default:            G_INIT_CLEAR; LED1_CLEAR; LED2_CLEAR; break;
        }
    } else if ( pilotLedCount < 1250 ){
        switch(gMachineState)
        {
        case STATE_READY:   G_INIT_CLEAR; LED1_CLEAR; LED2_SET; break;
        case STATE_RUN:     G_INIT_SET;   LED1_SET; LED2_SET; break;
        case STATE_TRIP:    G_INIT_CLEAR; LED1_CLEAR; LED2_CLEAR; break;
        default:            G_INIT_SET;   LED1_SET; LED2_CLEAR; break;
        }
    } else if ( pilotLedCount < 1500 ){
        switch(gMachineState)
        {
        case STATE_READY:   G_INIT_CLEAR; LED1_CLEAR; LED2_SET; break;
        case STATE_RUN:     G_INIT_SET;   LED1_SET; LED2_SET; break;
        case STATE_TRIP:    G_INIT_CLEAR; LED1_CLEAR; LED2_CLEAR; break;
        default:            G_INIT_CLEAR; LED1_CLEAR; LED2_CLEAR; break;
        }
    } else if ( pilotLedCount < 1750 ){
        switch(gMachineState)
        {
        case STATE_READY:   G_INIT_CLEAR; LED1_CLEAR; LED2_SET; break;
        case STATE_RUN:     G_INIT_CLEAR; LED1_CLEAR; LED2_SET; break;
        case STATE_TRIP:    G_INIT_CLEAR; LED1_CLEAR; LED2_CLEAR; break;
        default:            G_INIT_SET;   LED1_SET; LED2_CLEAR; break;
        }
    } else if ( pilotLedCount < 2000 ){
        switch(gMachineState)
        {
        case STATE_READY:   G_INIT_CLEAR; LED1_CLEAR; LED2_SET; break;
        case STATE_RUN:     G_INIT_CLEAR; LED1_CLEAR; LED2_SET; break;
        case STATE_TRIP:    G_INIT_CLEAR; LED1_CLEAR; LED2_CLEAR; break;
        default:            G_INIT_CLEAR; LED1_CLEAR; LED2_CLEAR; break;
        }
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

#else
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
#endif
