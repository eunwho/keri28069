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

    GpioCtrlRegs.GPADIR.bit.GPIO0   = 1;  // GPIO0 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO1   = 1;  // GPIO1 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO2   = 1;  // GPIO2 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO3   = 1;  // GPIO3 = Output

    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;  // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;  // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;  // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;  // Set Output
    EDIS;
}

void ePwmEnable()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 1;            // GPIO0    = PWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 1;            // GPIO1    = PWM1B
    GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 1;            // GPIO2    = PWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 1;            // GPIO3    = PWM2B
    EDIS;
}

void InitGpio(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 0; // GPIO0 = PWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 0; // GPIO1 = PWM1B
    GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 0; // GPIO2 = PWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 0; // GPIO3 = PWM2B
    GpioCtrlRegs.GPAMUX1.bit.GPIO4  = 0; // GPIO4 = PWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5  = 0; // GPIO5 = PWM3B
    GpioCtrlRegs.GPAMUX1.bit.GPIO6  = 0; // GPIO6 = PWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7  = 0; // GPIO7 = PWM4B

    GpioCtrlRegs.GPADIR.bit.GPIO0   = 1; // GPIO0 = output
    GpioCtrlRegs.GPADIR.bit.GPIO1   = 1; // GPIO1 = output
    GpioCtrlRegs.GPADIR.bit.GPIO2   = 1; // GPIO2 = output
    GpioCtrlRegs.GPADIR.bit.GPIO3   = 1; // GPIO3 = output
    GpioCtrlRegs.GPADIR.bit.GPIO4   = 1; // GPIO4 = output
    GpioCtrlRegs.GPADIR.bit.GPIO5   = 1; // GPIO5 = output
    GpioCtrlRegs.GPADIR.bit.GPIO6   = 1; // GPIO6 = output
    GpioCtrlRegs.GPADIR.bit.GPIO7   = 1; // GPIO7 = output

    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1; // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO3 = 1; // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO4 = 1; // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO5 = 1; // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO6 = 1; // Set Output
    GpioDataRegs.GPACLEAR.bit.GPIO7 = 1; // Set Output

//--- gpio7 reserved set out
    GpioCtrlRegs.GPAPUD.bit.GPIO7   = 0; // Enable pullup
    GpioDataRegs.GPASET.bit.GPIO7   = 1; // set high
    GpioCtrlRegs.GPAMUX1.bit.GPIO7  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO7   = 1; // output

//--- gpio8 TRIP_OUT
    GpioCtrlRegs.GPAPUD.bit.GPIO8   = 0; // Enable pullup on GPIO8
    GpioDataRegs.GPACLEAR.bit.GPIO8 = 1; // set low
    GpioCtrlRegs.GPAMUX1.bit.GPIO8  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO8   = 1; // output

//--- gpio9 INIT_CHARGE
    GpioCtrlRegs.GPAPUD.bit.GPIO9   = 0; // Enable pullup on GPIO9
    GpioDataRegs.GPACLEAR.bit.GPIO9 = 1; // set low
    GpioCtrlRegs.GPAMUX1.bit.GPIO9  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO9   = 1; // output

//---gpio10 MAIN_CHARGE
    GpioCtrlRegs.GPAPUD.bit.GPIO10  = 0; // Enable pullup on GPIO10
    GpioDataRegs.GPACLEAR.bit.GPIO10= 1; // set low
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO10  = 1; // output

//---gpio11 GATE_EN
    GpioCtrlRegs.GPAPUD.bit.GPIO11  = 0; // Enable pullup on GPIO11
    GpioDataRegs.GPACLEAR.bit.GPIO11= 1; // set low
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO11  = 1; // output

//--- gpio12 START_INPUT
    GpioCtrlRegs.GPAPUD.bit.GPIO12   = 0; // Enable pullup on GPIO12
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3; // asynch input
    GpioCtrlRegs.GPAMUX1.bit.GPIO12  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO12   = 0; // input

//---gpio13 EX_TRIP_INPUT
    GpioCtrlRegs.GPAPUD.bit.GPIO13   = 0; // Enable pullup on GPIO13
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // asynch input
    GpioCtrlRegs.GPAMUX1.bit.GPIO13  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO13   = 0; // input

//---gpio14 EX_DIO_INPUT1
    GpioCtrlRegs.GPAPUD.bit.GPIO14   = 0; // Enable pullup
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3; // asynch input
    GpioCtrlRegs.GPAMUX1.bit.GPIO14  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO14   = 0; // input

//---gpio15 EX_DIO_INPUT2
    GpioCtrlRegs.GPAPUD.bit.GPIO15   = 0; // Enable pullup
    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3; // asynch input
    GpioCtrlRegs.GPAMUX1.bit.GPIO15  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO15   = 0; // input

//---gpio16 EX_IO_16
    GpioCtrlRegs.GPAPUD.bit.GPIO16   = 0; // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO16  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO16   = 0; // input

//--- gpio17 EP_WR   eeprom write protection
    GpioCtrlRegs.GPAPUD.bit.GPIO17   = 0; // Enable pullup
    GpioDataRegs.GPASET.bit.GPIO17   = 1; // write protected, output high
    GpioCtrlRegs.GPAMUX2.bit.GPIO17  = 0; //
    GpioCtrlRegs.GPADIR.bit.GPIO17   = 1; // output

//--- gpio18 TRIP_UH
    GpioCtrlRegs.GPAPUD.bit.GPIO18   = 0; // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO18  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO18   = 0; // input

//--- gpio19 TRIP_UL
    GpioCtrlRegs.GPAPUD.bit.GPIO19   = 0; // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO19  = 0; //
    GpioCtrlRegs.GPADIR.bit.GPIO19   = 0; // input

//--- gpio20 EX_IO_20
    GpioCtrlRegs.GPAPUD.bit.GPIO20   = 0;  // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO20  = 0;  // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO20   = 0;  // input

//--- gpio20 EX_IO_21
    GpioCtrlRegs.GPAPUD.bit.GPIO21   = 0;  // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO21  = 0;  // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO21   = 0;  // output


//--- 22 sci_txdb
    GpioCtrlRegs.GPAPUD.bit.GPIO22   = 0; // Enable pullup on GPIO22
    GpioCtrlRegs.GPAMUX2.bit.GPIO22  = 3; // sci_txdb

//--- 23 sci_rxdb
    GpioCtrlRegs.GPAPUD.bit.GPIO23   = 0; // Enable pullup on GPIO23
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO23  = 0; // sci_rxdb

//--- 24 EX_IO_24
    GpioCtrlRegs.GPAPUD.bit.GPIO24   = 0; // Enable pullup on GPIO24
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO24  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO24   = 0; // input

//--- 25 EX_IO_25
    GpioCtrlRegs.GPAPUD.bit.GPIO25   = 0;  // Enable pullup on GPIO25
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO25  = 0;  // GPIO25
    GpioCtrlRegs.GPADIR.bit.GPIO25   = 1;  // output

//--- gpio26 TRIP_VH
    GpioCtrlRegs.GPAPUD.bit.GPIO26   = 0; // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO26  = 0; //
    GpioCtrlRegs.GPADIR.bit.GPIO26   = 0; // input

//--- gpio27 TRIP_VL
    GpioCtrlRegs.GPAPUD.bit.GPIO27   = 0; // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO27  = 0; //
    GpioCtrlRegs.GPADIR.bit.GPIO27   = 0; // input

//--- 28 sci_rxda
    GpioCtrlRegs.GPAPUD.bit.GPIO28  = 0;  // Enable pullup on GPIO28
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // Asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // GPIO28

//--- 29 sci_txda
    GpioCtrlRegs.GPAPUD.bit.GPIO29  = 0;  // Enable pullup on GPIO29
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // GPIO29

//---gpio30 TRIP_WH
    GpioCtrlRegs.GPAPUD.bit.GPIO30   = 0; // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO30  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO30   = 0; // input

//--- pin 31 TRIP_WL
    GpioCtrlRegs.GPAPUD.bit.GPIO31   = 0; // Enable pullup
    GpioCtrlRegs.GPAQSEL2.bit.GPIO31 = 3; //
    GpioCtrlRegs.GPAMUX2.bit.GPIO31  = 0; // gpio
    GpioCtrlRegs.GPADIR.bit.GPIO31   = 0; // input

//--- 32 SDAA
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pullup on GPIO32
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;  // GPIO32 = SDAA

//--- 33 SCLA
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3; // Asynch input
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pullup on GPIO33
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;  // GPIO33 = SCLA

//--- gpio34 TRIP_DB
    GpioCtrlRegs.GPBPUD.bit.GPIO34   = 0; // Enable pullup on GPIO34
    GpioCtrlRegs.GPBQSEL1.bit.GPIO34 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO34  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO34   = 0; // input

//--- gpio39~58 open output reserved
    GpioCtrlRegs.GPBPUD.bit.GPIO39 = 0;  // pullup
    GpioDataRegs.GPBCLEAR.bit.GPIO39= 1; // output clear
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0; // GPIO34 = GPIO34
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;  // GPIO34 = input

//--- 40 EX_IO_40 input
//    GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1; // output low
    GpioCtrlRegs.GPBPUD.bit.GPIO40   = 0; // enable pullup
    GpioCtrlRegs.GPBQSEL1.bit.GPIO40 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO40  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO40   = 0; // input

//--- 41 EX_IO_41 input
    GpioCtrlRegs.GPBPUD.bit.GPIO41   = 0; // enable pullup
    GpioCtrlRegs.GPBQSEL1.bit.GPIO41 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO41  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO41   = 0; // input

//--- 42 EX_IO_42 input
    GpioCtrlRegs.GPBPUD.bit.GPIO42   = 0; // enable pullup
    GpioCtrlRegs.GPBQSEL1.bit.GPIO42 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO42  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO42   = 0; // input

//--- 43 EX_IO_43 input
    GpioCtrlRegs.GPBPUD.bit.GPIO43   = 0; // enable pullup
    GpioCtrlRegs.GPBQSEL1.bit.GPIO43 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO43  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO43   = 0; // input

//--- 44 EX_IO_44 input
    GpioCtrlRegs.GPBPUD.bit.GPIO44   = 0; // enable pullup
    GpioCtrlRegs.GPBQSEL1.bit.GPIO44 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO44  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO44   = 0; // output

//    GpioDataRegs.GPBCLEAR.bit.GPIO50= 1; // output low

//--- 50 EX_IO_50 input
    GpioCtrlRegs.GPBPUD.bit.GPIO50   = 0; // enable pullup
    GpioCtrlRegs.GPBQSEL2.bit.GPIO50 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX2.bit.GPIO50  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO50   = 0; // input

//--- 51 EX_IO_51 input
    GpioCtrlRegs.GPBPUD.bit.GPIO51   = 0; // enable pullup
    GpioCtrlRegs.GPBQSEL2.bit.GPIO51 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX2.bit.GPIO51  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO51   = 0; // input

//--- 52 EX_IO_52 input
    GpioCtrlRegs.GPBPUD.bit.GPIO52   = 0; // enable pullup
    GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX2.bit.GPIO52  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO52   = 0; // input

//--- 53 EX_IO_53 input
    GpioCtrlRegs.GPBPUD.bit.GPIO53   = 0; // enable pullup
    GpioCtrlRegs.GPBQSEL2.bit.GPIO53 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX2.bit.GPIO53  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO53   = 0; // input

//--- 54 EX_IO_54 input
    GpioCtrlRegs.GPBPUD.bit.GPIO54   = 0; // enable pullup
    GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX2.bit.GPIO54  = 0; // gpio
    GpioCtrlRegs.GPBDIR.bit.GPIO54   = 0; // input

//--- 55 EX_IO_55 input
    GpioCtrlRegs.GPBPUD.bit.GPIO55   = 0; // pullup
    GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX2.bit.GPIO55  = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO55   = 0; // input

//--- 56 EX_IO_56 input
    GpioCtrlRegs.GPBPUD.bit.GPIO56   = 0; // pullup
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX2.bit.GPIO56  = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO56   = 0; // input

//--- 57 LED_RED
    GpioCtrlRegs.GPBPUD.bit.GPIO57   = 0; // pullup
//    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX2.bit.GPIO57  = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO57   = 1; // input

//--- 58 LED_GREEN
    GpioCtrlRegs.GPBPUD.bit.GPIO58   = 0; // pullup
//    GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX2.bit.GPIO58  = 0; //
    GpioCtrlRegs.GPBDIR.bit.GPIO58   = 1; // input
    EDIS;
}

//
// End of File
//

