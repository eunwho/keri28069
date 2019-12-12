/////////////////////////////////////////////////////////////////////////
//
//	Project Name 	: Inverter for 
//	Fiele Name	 	: Timer_Irq_Proc.c
//
//  Start 			: 2009.07.09 sunday
//
///////////////////////////////////////////////////////////////////////////
#include	<header.h>
#include	<extern.h>

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
        LED_GREEN_RUN_SET;
        LED_RED_CPURUN_SET;
        switch(gMachineState)
        {
        case STATE_TRIP: LED_RED_FAULT_SET ;    break;
        default:          LED_RED_FAULT_SET;    break;
        }
    } else if ( pilotLedCount < 500 ){
        switch(gMachineState)
        {
        case STATE_READY:
            LED_GREEN_RUN_SET;
            LED_RED_CPURUN_SET;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_RUN:
            LED_GREEN_RUN_SET;
            LED_RED_CPURUN_SET;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_TRIP:
            LED_GREEN_RUN_CLEAR;
            LED_RED_CPURUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        default:
            LED_RED_CPURUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        }
    } else if ( pilotLedCount < 750 ){
        switch(gMachineState)
        {
        case STATE_READY:
            LED_RED_CPURUN_SET;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_RUN:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_TRIP:
            LED_RED_CPURUN_SET;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_SET;
            break;
        default:
            LED_RED_CPURUN_SET;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_SET;
            break;
        }
    } else if ( pilotLedCount < 1000 ){
        switch(gMachineState)
        {
        case STATE_READY:
            LED_RED_CPURUN_SET;
            LED_GREEN_RUN_SET;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_RUN:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_TRIP:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        default:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        }
    } else if ( pilotLedCount < 1250 ){
        switch(gMachineState)
        {
        case STATE_READY:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_RUN:
            LED_RED_CPURUN_SET;
            LED_GREEN_RUN_SET;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_TRIP:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        default:
            LED_RED_CPURUN_SET;
            LED_GREEN_RUN_SET;
            LED_RED_FAULT_SET;
            break;
        }
    } else if ( pilotLedCount < 1500 ){
        switch(gMachineState)
        {
        case STATE_READY:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_RUN:
            LED_RED_CPURUN_SET;
            LED_GREEN_RUN_SET;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_TRIP:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        default:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        }
    } else if ( pilotLedCount < 1750 ){
        switch(gMachineState)
        {
        case STATE_READY:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_RUN:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_TRIP:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        default:
            LED_RED_CPURUN_SET;
            LED_GREEN_RUN_SET;
            LED_RED_FAULT_SET;
            break;
        }
    } else if ( pilotLedCount < 2000 ){
        switch(gMachineState)
        {
        case STATE_READY:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_RUN:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        case STATE_TRIP:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        default:
            LED_RED_CPURUN_CLEAR;
            LED_GREEN_RUN_CLEAR;
            LED_RED_FAULT_CLEAR;
            break;
        }
    }
}
