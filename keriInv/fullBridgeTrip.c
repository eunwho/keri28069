//
// filename 	: fullBridgedual_trip_proc.c
// pcb			: dfig_dsp_.0104.bk.sch
// data			; 2012.04.17		
//					by cheoung soon gil  
// 
#include	<header.h>
#include	<extern.h>

#define OVER_C_TIME 60.0

void trip_recording(int trip_code,double trip_data,char * st)
{
	if(gRunFlag)	gTripSaveFlag = 1;
	else			gTripSaveFlag = 0;

	TripInfoNow.CODE	= trip_code;
	TripInfoNow.DATA	= trip_data;
	strncpy( TripInfoNow.MSG,st,20) ;
	TripInfoNow.CURRENT	= Iout;
	TripInfoNow.VDC 	= Vdc;
	TripInfoNow.VOUT 	= Vout;
}	

int CheckOverCurrent( )
{
//--- OC I_pri check
	if(( protect_reg.bit.OVER_I_ADC)&&( adcIpri > 4000)){
		trip_recording( ERR_OC_I_PRI_ADC_P, (double)(adcIpri),"adcIpri over");
		return ERR_OC_I_PRI_ADC_P;
	}
	if(( protect_reg.bit.OVER_I_ADC)&&( adcIpri  < 100)){
		trip_recording( ERR_OC_I_PRI_ADC_N, (double)(adcIpri),"adcIpri under");
		return ERR_OC_I_PRI_ADC_N;
	}
//--- OC I_out check
	if(( protect_reg.bit.OVER_I_ADC)&&( adcIout > 4000)){
		trip_recording( ERR_OC_I_OUT_ADC_P, (double)(adcIout),"adcIout over ");
		return ERR_OC_I_OUT_ADC_P;
	}
	if(( protect_reg.bit.OVER_I_ADC)&&( adcIout  < 100)){
		trip_recording( ERR_OC_I_OUT_ADC_N, (double)(adcIout),"adcIout under");
		return ERR_OC_I_OUT_ADC_N;
	}
	if( protect_reg.bit.OVER_I){
		if(Iout > OverCurLimit )	OC_Timer += Ts;
		else if(OC_Timer > Ts)		OC_Timer -= Ts;

		if (OC_Timer > codeOcTime ){
			trip_recording( CODE_OC_Time,Iout,"OC Time out");
			return	CODE_OC_Time;
		}
	} 
	return 	0; 
}

int CheckOverVolt( )
{
	static int OverVoltCount = 0;

	if( protect_reg.bit.OVER_VOLT == 0 ) return 0;
	if      (Vdc > 700.0 ) OverVoltCount++;
	else if ( OverVoltCount > 0) OverVoltCount --;

	if (OverVoltCount > 5 ){
		OverVoltCount = 6;
		trip_recording( ERR_OV_VDC,Vdc,"Trip Vdc Over");
		return ERR_OV_VDC;
	}
	return 0;
}

int CheckOVP( ){
	if( Vout > code_VoutLimit )	ovpTimer += Ts;
	else if(ovpTimer > Ts)		ovpTimer -= Ts;

	if (ovpTimer > code_ovpTime ){
		trip_recording( CODE_ovpTime,Vout,"OVP Time out");
		return	CODE_ovpTime;
	}
	return 0;
}

int CheckUndeVolt( )
{
	static int UnderVoltCount = 0;

	if( protect_reg.bit.UNVER_VOLT == 0 ) return 0;
	if( gMachineState == STATE_POWER_ON ) return 0;	// 2014.0901 by soongil

	if (Vdc < 400.0 ) 	UnderVoltCount++;
	else if( UnderVoltCount > 0) 	UnderVoltCount--;

	if (UnderVoltCount > 20 ){
		UnderVoltCount = 20;
		trip_recording( ERR_UV_VDC,Vdc,"Trip Vdc Under");
		return ERR_UV_VDC;
	}
	return 0;
}

int CheckIGBTFault( )
{
	if( protect_reg.bit.IGBT_FAULT == 0 ) return 0;

	if( ! PWM0_HIGH_FAULT ){
	    trip_recording( ERR_IGBT_UH,adc_result[0],"ERR_IGBT_UH");
		return ERR_IGBT_UH;
	}
	if( ! PWM0_LOW_FAULT ){
		trip_recording( ERR_IGBT_UL,adc_result[0],"ERR_IGBT_UL");
		return ERR_IGBT_UL;
	}
	if( ! PWM1_HIGH_FAULT){
		trip_recording( ERR_IGBT_VH,adc_result[0],"ERR_IGBT_VH");
		return ERR_IGBT_VH;
	}
	if( ! PWM1_LOW_FAULT ){
		trip_recording( ERR_IGBT_VL,adc_result[0],"ERR_IGBT_VL");
		return ERR_IGBT_VL;
	}
	return 0;
}

int tripCheck()
{
	int TripCode;
	TripCode = 0;
	if( ( TripCode = CheckOverCurrent()) != 0 ) return TripCode ;	// debug
	if( ( TripCode = CheckOverVolt()   ) != 0 ) return TripCode ;
	if( ( TripCode = CheckUndeVolt()   ) != 0 ) return TripCode ;
	if( ( TripCode = CheckIGBTFault()  ) != 0 ) return TripCode ;
	if( ( TripCode = CheckOVP( )       ) != 0 ) return TripCode ;
	return TripCode;
}

void tripProc( )
{
	int iCommand;
	int LoopCtrl;
	double fReference;

	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 	= 0;  // gpio
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 	= 0;  // gpio
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 	= 0;  // gpio
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 	= 0;  // gpio

	GpioCtrlRegs.GPADIR.bit.GPIO0 	= 1;  // GPIO0 = Output
	GpioCtrlRegs.GPADIR.bit.GPIO1 	= 1;  // GPIO1 = Output
	GpioCtrlRegs.GPADIR.bit.GPIO2 	= 1;  // GPIO2 = Output
	GpioCtrlRegs.GPADIR.bit.GPIO3 	= 1;  // GPIO3 = Output

	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;  // output low
	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;  // output low
	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;  // output low
	GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;  // output low
	EDIS;

	gMachineState = STATE_TRIP;
	MAIN_CHARGE_OFF;					// Main Charge Relay Off
	init_charge_flag=0;

	TRIP_OUT_ON;
		
	if( gTripSaveFlag )
		SaveTripDataToEeprom();  // debug_jsk

	LoopCtrl = CMD_NULL;
	while( LoopCtrl != CMD_RESET){
		get_command( & iCommand, & fReference);	// Command�� �Է� ���� 				
		if( iCommand == CMD_RESET) LoopCtrl = CMD_RESET;
		Nop();
	}

	delay_msecs(50);
	while( LoopCtrl == CMD_RESET)
	{
		get_command( & iCommand, & fReference);
		if( iCommand == CMD_STOP) LoopCtrl = CMD_STOP;
		Nop();
	}

	gMachineState = STATE_POWER_ON;
	Nop();
	asm (" .ref _c_int00"); // ;Branch to start of boot.asm in RTS library
	asm (" LB _c_int00"); // ;Branch to start of boot.asm in RTS library
}

void GetTripInfo(int Point,TRIP_INFO * TripData )
{
	int TripDataPoint;
	int TripBaseAddr;
	int iTemp;
	char str[30]={0};
	UNION32 u32data;

	I2CA_ReadData(ADDR_24LC32,EPROM_ADDR_TRIP_POINT,&TripDataPoint);

// erased  
	if( ( 0 > Point ) || ( Point > 10) || (TripDataPoint == 0x00ff))
	{
		TripData->CURRENT = 0.0;
		TripData->DATA = 0.0;
		TripData->VOUT = 0.0;
		TripData->CODE = 0.0;
		TripData->VDC = 0.0;
		strncpy(TripData->MSG  ," Invalid Trip Code  ",20);
		return ;
	}

	if( (TripDataPoint<1)||(TripDataPoint>10)){
		I2CA_WriteData(ADDR_24LC32, EPROM_ADDR_TRIP_POINT,0);
		TripDataPoint = 0;
	}
	EepromSaveFlag = 1;
// ����� �� �����͸� ���Ѵ�. 
	iTemp = TripDataPoint - Point;		// iPoint = 1~10;

	if( iTemp < 0 ) iTemp += 10;

	TripBaseAddr = TRIP_BACKUP_ADDR + iTemp * 100;

	// Code
	read_eprom_data( TripBaseAddr+ 0, & u32data);
		TripData->CODE =  u32data.dword;

	// Data
	read_eprom_data( TripBaseAddr+ 4, & u32data);
		TripData->CURRENT =  u32data.dword;

	// Current
	read_eprom_data( TripBaseAddr+ 8, & u32data);
	TripData->CURRENT =  u32data.dword;

	// HZ
	read_eprom_data( TripBaseAddr+ 12, & u32data);
	TripData->VOUT =  u32data.dword;

	// VDC
	read_eprom_data( TripBaseAddr+16, & u32data);
	TripData->VDC =  u32data.dword;

	ReadTripString( TripBaseAddr+20,str);
	strncpy(TripData->MSG,str,20);

	// Time
	ReadTripString( TripBaseAddr+40,str);

	// start Time
	ReadTripString( TripBaseAddr+60,str);

	EepromSaveFlag = 0;
}

void WriteTripString(int StartAddr, char * str)
{
	int i;
	int Addr;
	int string[21]={0};
	
	for(i=0;i<20;i++) string[i] = (int)(*(str ++));

	Addr = StartAddr;

	for(i=0;i<20;i++) I2CA_WriteData(ADDR_24LC32,Addr+i,string[i]);
}

void ReadTripString(int StartAddr, char * str)
{
	int i;
	int Addr;
	int iTemp;	
	char StrBuf[30];

	Addr = StartAddr;

	for(i=0;i<20;i++){
		I2CA_ReadData(ADDR_24LC32,Addr+i,&iTemp);
		StrBuf[i] = (char)(iTemp);
	}
	StrBuf[20] =0;
	strncpy(str,StrBuf,20);
}

void SaveTripDataToEeprom()
{
	int TripDataPoint,TripBaseAddr;
	char str[30];
	UNION32 u32data;

	I2CA_ReadData(ADDR_24LC32,EPROM_ADDR_TRIP_POINT,&TripDataPoint);

	if(( TripDataPoint < 0 ) ||( TripDataPoint > 8)) TripDataPoint = 0;
	else TripDataPoint ++;

	I2CA_WriteData(ADDR_24LC32, EPROM_ADDR_TRIP_POINT, TripDataPoint);			
	 
	TripBaseAddr = TRIP_BACKUP_ADDR + TripDataPoint * 100;

	EepromSaveFlag = 1;
// Code
	u32data.dword = TripInfoNow.CODE;
	write_code_2_eeprom( TripBaseAddr+ 0, u32data);

// Data
	u32data.dword = TripInfoNow.DATA;
	write_code_2_eeprom( TripBaseAddr+ 4, u32data);

// Current
	u32data.dword = TripInfoNow.CURRENT;
	write_code_2_eeprom( TripBaseAddr+ 8, u32data);

// Vout
	u32data.dword = TripInfoNow.VOUT;
	write_code_2_eeprom( TripBaseAddr+ 12, u32data);

// VDC
	u32data.dword = TripInfoNow.VDC;
	write_code_2_eeprom( TripBaseAddr+16, u32data);

// Msg
	strncpy(str,TripInfoNow.MSG,20);
	WriteTripString( TripBaseAddr+20,str);
// Time
	WriteTripString( TripBaseAddr+40,str);
// start Time
	WriteTripString( TripBaseAddr+60,str);

	EepromSaveFlag = 0;
}

void ClearTripDataToEeprom()
{
	int TripBaseAddr = 0;
	int TripDataPoint;
	int TripPointCount;
	char str[30];
	UNION32 u32data;

	EepromSaveFlag = 1;

	u32data.dword = 0.0;

	load_sci_tx_mail_box("WAIT FOR CLEAR DATA!");

	for(TripPointCount = 0; TripPointCount < 10; TripPointCount++)
	{

		I2CA_WriteData(ADDR_24LC32, EPROM_ADDR_TRIP_POINT, TripDataPoint);

		TripBaseAddr = TRIP_BACKUP_ADDR + TripDataPoint * 100;
		write_code_2_eeprom( TripBaseAddr+ 0, u32data);
		write_code_2_eeprom( TripBaseAddr+ 4, u32data);
		write_code_2_eeprom( TripBaseAddr+ 8, u32data);
		write_code_2_eeprom( TripBaseAddr+ 12, u32data);
		write_code_2_eeprom( TripBaseAddr+16, u32data);
		strncpy(str," NO TRIP DATA       ",20);
		WriteTripString( TripBaseAddr+20,str);

		strncpy(str,"2010:01:01  00:00:00",20);
		WriteTripString( TripBaseAddr+40,str);

		strncpy(str,"2010:01:01  00:00:00",20);
		WriteTripString( TripBaseAddr+60,str);
	}
	EepromSaveFlag = 0;
	load_sci_tx_mail_box("CLEAR COMPLETE !!   ");
}

//------------------------------
// End
//------------------------------

