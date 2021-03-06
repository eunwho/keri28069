//###########################################################################
// FILE:	Example_2806xGpioSetup.c
// TITLE:	GPIO Setup Example
//###########################################################################
#include    <header.h>
#include    <extern.h>

void ePwmPortOff()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 0;  // GPIO0 = PWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 0;  // GPIO1 = PWM1B
    GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 0;  // GPIO2 = PWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 0;  // GPIO3 = PWM2B
    GpioCtrlRegs.GPAMUX1.bit.GPIO4  = 0;  // GPIO4 = PWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5  = 0;  // GPIO5 = PWM3B
    GpioCtrlRegs.GPAMUX1.bit.GPIO6  = 0;  // GPIO6  = PWM4A

    GpioCtrlRegs.GPADIR.bit.GPIO0   = 1;  // GPIO0 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO1   = 1;  // GPIO1 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO2   = 1;  // GPIO2 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO3   = 1;  // GPIO3 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO4   = 1;  // GPIO4 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO5   = 1;  // GPIO5 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO6   = 1;  // GPIO5 = Output

#if GATE_ACTIVE_LOW
    GpioDataRegs.GPASET.bit.GPIO0 = 1;  // Set Output
    GpioDataRegs.GPASET.bit.GPIO1 = 1;  // Set Output
    GpioDataRegs.GPASET.bit.GPIO2 = 1;  // Set Output
    GpioDataRegs.GPASET.bit.GPIO3 = 1;  // Set Output
    GpioDataRegs.GPASET.bit.GPIO4 = 1;  // Set Output
    GpioDataRegs.GPASET.bit.GPIO5 = 1;  // Set Output
    GpioDataRegs.GPASET.bit.GPIO6 = 1;  // Set Output
#else
    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;  // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;  // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;  // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;  // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;  // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;  // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;  // Set Output
#endif
    EDIS;
}

void ePwmEnable()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 1;            // GPIO0    = PWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 1;            // GPIO1    = PWM1B
    GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 1;            // GPIO2    = PWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 1;            // GPIO3    = PWM2B
    GpioCtrlRegs.GPAMUX1.bit.GPIO4  = 1;            // GPIO4    = PWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5  = 1;            // GPIO5    = PWM3B
    GpioCtrlRegs.GPAMUX1.bit.GPIO6  = 1;            // GPIO5    = PWM3B
    EDIS;
}

void InitGpio(void)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // Enable pullup on GPIO0
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;   // Enable pullup on GPIO1
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;   // Enable pullup on GPIO2
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;   // Enable pullup on GPIO3
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;   // Enable pullup on GPIO4
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;   // Enable pullup on GPIO5

    GpioCtrlRegs.GPADIR.bit.GPIO0   = 1;  // GPIO0 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO1   = 1;  // GPIO1 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO2   = 1;  // GPIO2 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO3   = 1;  // GPIO3 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO4   = 1;  // GPIO4 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO5   = 1;  // GPIO5 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO6   = 1;  // GPIO5 = Output

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;  // GPIO0 = PWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;  // GPIO1 = PWM1B
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;  // GPIO2 = PWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;  // GPIO3 = PWM2B
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;  // GPIO4 = PWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;  // GPIO5 = PWM3B

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // DB-pulse
//    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;  //--- GPIO6 = PWM4A

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  //--- GPIO6 = PWM4A
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;   //--- GPIO7 = output
    GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;   // Load output latch

    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;   // Enable pullup
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;  // gateEnable
    GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;   // Load output latch

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   // Enable pullup on GPIO8
    GpioDataRegs.GPASET.bit.GPIO8 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;  // G-run-out
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;   //--- GPIO8 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // Enable pullup on GPIO9
    GpioDataRegs.GPASET.bit.GPIO9 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;  // reserved
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;   //--- GPIO9 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;  // Enable pullup on GPIO10
    GpioDataRegs.GPACLEAR.bit.GPIO10= 1; // output clear
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0; //--- G-mainRelayOn
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;  // GPIO10 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;  // Enable pullup on GPIO11
    GpioDataRegs.GPACLEAR.bit.GPIO11= 1; // output clear
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0; //--- G-init-charge
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;  // GPIO11 = output
    //--- gTripRelayOut
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pullup on GPIO12
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3; // asynch input
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;  //--- trip-out
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;   // GPIO12 = out
    //--- relayOutAux1
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pullup on GPIO12
    GpioDataRegs.GPACLEAR.bit.GPIO13= 1; // output clear
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;  // --- relay-out-aux1
    GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;  // GPIO12 = output
//--- InputAux1
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;   // Enable pullup
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3; //
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;  //
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;   // Input
//--- InputAux2
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;   // Enable pullup
    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3; //
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;  //
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;   // Input
//--- G-gateFault
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;  //
    GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;   // Input
//--- epWriteProtect
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;  // Enable pullup
    GpioDataRegs.GPASET.bit.GPIO17= 1;	 // write protected, output high
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0; //
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 1;  //
//--- addon-din-1
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;  //
    GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;   // Input
//--- addon-din-2
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;  //
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;   // Input
//--- addon-din-3
    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;   // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;  //
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;   // Input
//--- addon-din-4
    GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;   // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;  //
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;   // Input

//--- addon-equp1 Enable EQEP1 on GPIO20 - GPIO23
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pullup on GPIO20
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pullup on GPIO21
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;   // Enable pullup on GPIO22
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;   // Enable pullup on GPIO23
    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;  // GPIO20 = EQEP1A
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;  // GPIO21 = EQEP1B
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 1;  // GPIO22 = EQEP1S
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;  // GPIO23 = EQEP1I

//--- addon Enable EQEP2 on GPIO24 - GPIO25
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;   // pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0; // Synch SYSCLKOUT
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0; // Synch SYSCLKOUT
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;  // EQEP2A
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;  // EQEP2B

//--- Enable SCI-A on GPIO28 - GPIO29
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;   // Enable pullup on GPIO28
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // Asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // GPIO28 = SCIRXDA
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;   // Enable pullup on GPIO29
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // GPIO29 = SCITXDA

//--- addon-relay-a pin 30 reserved
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;  // Enable pullup
    GpioDataRegs.GPACLEAR.bit.GPIO30= 1; // output clear
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0; //
    GpioCtrlRegs.GPADIR.bit.GPIO30 = 1;  // addon-relay-a

//--- addon-relay-b pin 31
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;  // Enable pullup
    GpioDataRegs.GPACLEAR.bit.GPIO31= 1; // output clear
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0; //
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;  // addon-relay-b

//--- Enable I2C-A on GPIO32 - GPIO33
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pullup on GPIO32
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;  // GPIO32 = SDAA
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3; // Asynch input
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pullup on GPIO33
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;  // GPIO33 = SCLA

//--- G-Input-1 gpio34 reserved
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;  // Enable pullup on GPIO34
    GpioDataRegs.GPBCLEAR.bit.GPIO34= 1; // output clear
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // GPIO34 = GPIO34
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;  // G-Input-1

//--- gpio39 input-aux-3
    GpioCtrlRegs.GPBPUD.bit.GPIO39 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO39= 1; // output clear
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0; // GPIO34 = GPIO34
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;  // input-aux-3

//--- gpio40 addon-txd
    GpioCtrlRegs.GPBPUD.bit.GPIO40 = 0;  // Enable pullup on GPIO34
    GpioDataRegs.GPBCLEAR.bit.GPIO40= 1; // output clear
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 2; // sci-txd-b
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = 1;  // GPIO34 = output

//--- gpio41 addon-rxd
    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 0;  // Enable pullup on GPIO34
    GpioDataRegs.GPBCLEAR.bit.GPIO41= 1; // output clear
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 2; // sci-rxd-b
    GpioCtrlRegs.GPBDIR.bit.GPIO41 = 0;  // GPIO41 = input

//--- gpio42 reserved output low
    GpioCtrlRegs.GPBPUD.bit.GPIO42 = 0;  // Enable pullup on GPIO34
    GpioDataRegs.GPBCLEAR.bit.GPIO42= 1; // output low
    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO42 = 1;  // out

//--- gpio43 reserved
    GpioCtrlRegs.GPBPUD.bit.GPIO43 = 0;  // Enable
    GpioDataRegs.GPBCLEAR.bit.GPIO43= 1; // output clear
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO43 = 1;  // out

//--- gpio44 reserved
    GpioCtrlRegs.GPBPUD.bit.GPIO44 = 0;  // Enable pullup on GPIO34
    GpioDataRegs.GPBCLEAR.bit.GPIO44= 1; // output clear
    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;  //

//--- gpio50 reserved
    GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO50= 1; // output clear
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;  // output

//--- gpio51 reserved
    GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO51= 1; // output clear
    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1;  // output

//--- gpio52
    GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO52= 1; // output clear
    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO52 = 1;  // output

//--- fndD gpio53
    GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO53= 1; // output clear
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1;  // output

//--- led-a
    GpioCtrlRegs.GPBPUD.bit.GPIO54 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO54= 1; // output clear
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO54 = 1;  // output

//--- led-b
    GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO55= 1; // output clear
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO55 = 1;  // output

//--- gpio56 reserved
    GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO56= 1; // output clear
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO56 = 1;  // output

//--- gpio57 reserved
    GpioCtrlRegs.GPBPUD.bit.GPIO57 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO57= 1; // output clear
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO57 = 1;  // output

//--- gpio58 reserved
    GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO58= 1; // output clear
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO58 = 1;  // output
    EDIS;
}

//
// End of File
//

