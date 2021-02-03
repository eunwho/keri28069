// filename 	: trip_proc.c 
// projectname 	: F28069 inverter PCB :
// data			; start 2018.06.23
//					by cheoung soon gil  
// 
#include	<header.h>
#include	<extern.h>

void trip_recording(int trip_code,double trip_data,char * st)
{
    TripInfoNow.CODE    = trip_code;
    TripInfoNow.DATA    = trip_data;
    strncpy( TripInfoNow.MSG,st,30) ;

    gMachineState       = STATE_TRIP;
    TripInfoNow.CURRENT = Is_mag_rms;
    TripInfoNow.VDC     = lpfVdc;
    TripInfoNow.RPM     = codeRateRpm * reference_out;

    if(gRunFlag)    gTripSaveFlag = 1;
    else            gTripSaveFlag = 0;
}

// #define OVER_I_LIMIT    300.0
int CheckOverCurrent( )
{
	if( adcCurrentA > 4000){
        trip_recording( ERR_OVER_CURRENT_U_PHASE, (double)(adcCurrentA),"I adc over U ph");
		return ERR_OVER_CURRENT_U_PHASE;
	}
	if( adcCurrentA < 100){
        trip_recording( ERR_OVER_CURRENT_U_PHASE, (double)(adcCurrentA),"I adc under U ph");
		return ERR_OVER_CURRENT_U_PHASE;
	}
	if( adcCurrentB > 4000){
        trip_recording( ERR_OVER_CURRENT_V_PHASE, (double)(adcCurrentB),"I adc over V ph");
		return ERR_OVER_CURRENT_V_PHASE;
	}
    if( adcCurrentB < 100 ){
        trip_recording( ERR_OVER_CURRENT_V_PHASE, (double)(adcCurrentB),"I adc under V ph");
        return ERR_OVER_CURRENT_V_PHASE;
    }

    if( fabs(Is_abc[as]) > codeIOver ){
        trip_recording( ERR_OVER_CURRENT_U_PHASE, fabs(Is_abc[as]) ,"I_a over");
        return ERR_OVER_CURRENT_U_PHASE;
    }

    if( fabs(Is_abc[bs]) > codeIOver ){
        trip_recording( ERR_OVER_CURRENT_V_PHASE, fabs(Is_abc[bs]) ,"I_b over");
        return ERR_OVER_CURRENT_V_PHASE;
    }

	return 	0; 
}

//#define OVER_V_LEVEL        420.0
int CheckOverVolt( )
{
	static int OverVoltCount = 0;

	if (Vdc > codeOverVoltLevel ) OverVoltCount++;
	else if( OverVoltCount > 0) OverVoltCount --;
	else    OverVoltCount = 0;

	if (OverVoltCount > 5 )
	{
		OverVoltCount = 6;
        trip_recording( ERR_HOV, Vdc,"Trip Over Volt");
		return ERR_HOV;
	}
	return 0;
}

int CheckUndeVolt( )
{
	static int UnderVoltCount = 0;

	if (Vdc < codeUnderVoltLevel) 	UnderVoltCount++;
	else if( UnderVoltCount > 0) 	UnderVoltCount--;
	else                            UnderVoltCount = 0;

	if (UnderVoltCount > 5 )
	{
		UnderVoltCount = 6;
        trip_recording( ERR_HUV, Vdc,"Trip Under Volt");
		return ERR_HUV;
	}
	return 0;
}

int CheckIGBTFault( )
{
    int tripCode =0;

    pwmTripState = digitalInputState = 0;

    if( GATE_DRIVER_FAULT == 0){ pwmTripState += 1;
        trip_recording( ERR_PWM_IGBT, 0.0,"Trip IGBT GATE"); tripCode = ERR_PWM_IGBT;
    }
	return tripCode;
}

int CheckOverHeat( ){
	static int OverHeatCount = 0;

	if( adcIgbtTemperature < 1000 )		OverHeatCount++;
	else if( OverHeatCount > 0) 	    OverHeatCount--;

	if( OverHeatCount > 10 ){	// debug// Low --> High
		OverHeatCount = 11;
        trip_recording( ERR_OVER_HEAT, 11.0,"Trip Over Heat");
		return ERR_OVER_HEAT;
	}
	return 0 ;
}

int tripCheckPWM()
{
    int TripCode;

    if ( codeProtectOff > 0.5 ) return 0;

    TripCode = 0;
    if( ( TripCode = CheckOverCurrent()) != 0 ) return TripCode ;   //
    return TripCode;
}

int trip_check()
{
    int TripCode;

    if ( codeProtectOff > 0.5 ) return 0;

    TripCode = 0;
    if( ( TripCode = CheckOverVolt()   ) != 0 ) return TripCode ;
    if( ( TripCode = CheckUndeVolt()   ) != 0 ) return TripCode ;   //

//    if( ( TripCode = CheckOverCurrent()) != 0 ) return TripCode ;   //
//  if( ( TripCode = CheckOverHeat()   != 0 ) return TripCode ;
//  if( ( TripCode = CheckIGBTFault()  ) != 0 ) return TripCode ;

    return TripCode;
}

void GetTripInfo(int Point,TRIP_INFO * TripData )
{

	strncpy(TripData->MSG ,NULL,41);

	TripData->CURRENT 	= TripInfoNow.CURRENT;
    TripData->DATA 		= TripInfoNow.DATA;
    TripData->RPM 		= TripInfoNow.RPM;
    TripData->CODE 		= TripInfoNow.CODE;
    TripData->VDC 		= TripInfoNow.VDC;
    strncpy(TripData->MSG  ,TripInfoNow.MSG,20);
}

void tripProc()
{
    int cmd,temp;
    double ref_in0;
    double dbtemp;
    char str[30]={0};

    // PWM_OFF();
    ePwmPortOff();
    gMachineState = STATE_TRIP;
	MAIN_CHARGE_OFF;

	load_scia_tx_mail_box("\nTRIP\t"); delay_msecs(20);
    load_scia_tx_mail_box(TripInfoNow.MSG); delay_msecs(20);

    snprintf( str,12,"\nCODE=%3d",TripInfoNow.CODE);
    load_scia_tx_mail_box(str);delay_msecs(20);

    dbtemp = TripInfoNow.RPM;
    temp = (int)(floor(dbtemp +0.5));
    snprintf( str,13,"\tFq=%3d[hz]",temp);
    load_scia_tx_mail_box(str); delay_msecs(20);

    dbtemp = TripInfoNow.VDC;
    temp = (int)(floor(dbtemp +0.5));
    snprintf( str,13,"\tVDC =%4d",temp);
    load_scia_tx_mail_box(str); delay_msecs(20);

    dbtemp = TripInfoNow.CURRENT;
    temp = (int)(floor(dbtemp +0.5));
    snprintf( str,13,"\tI1  =%4d ",temp);
    load_scia_tx_mail_box(str); delay_msecs(20);

    dbtemp = TripInfoNow.DATA;
    temp = (int)(floor(dbtemp +0.5));
    snprintf( str,13," \tDATA=%4d\n",temp);
    load_scia_tx_mail_box(str); delay_msecs(20);

    temp = 1;

	while( temp ){
        get_command( & cmd, & ref_in0);
	    if( START_INPUT && EX_DIO_INPUT1 ) temp = 0;
	}

	gPWMTripCode = 0;
    DINT;
    EALLOW;
    EmuKey = 0x55aa;
    EmuBMode = 0x000B;
    SysCtrlRegs.SCSR = 0x00;
    SysCtrlRegs.WDCR = 0x20;
    EDIS;
    while(1);
}
//--- end of Trip_proc.c
