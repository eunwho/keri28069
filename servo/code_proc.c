#include	"header.h"
#include	"extern.h"

int get_code_information(int address,int cmd , CODE_INFO *  codes)
{	
	switch(address)
	{
    case CODE_motor_direction_change:
        strncpy(codes->disp, "Rotate CW ON",20);
        if( cmd == CMD_WRITE_RAM ) codeMotorDirection = codes->code_value;
        set_code_default(0,1,0,codeMotorDirection,0,codes);
        break;

    case CODE_accel_time1:
        strncpy(codes->disp, "accel_time1 (sec)",20);
        if( cmd == CMD_WRITE_RAM ) codeAccelTime1 = codes->code_value;
        set_code_default(0.0,3000.0,5.0,codeAccelTime1,0,codes);
        break;

    case CODE_decel_time1:
        strncpy(codes->disp, "decel_time1 (sec)",20);
        if( cmd == CMD_WRITE_RAM ) codeDecelTime1 = codes->code_value;
        set_code_default(0.0,3000.0,5.0,codeDecelTime1,0,codes);
        break;

    case CODE_MotorCtrMode:
        strncpy(codes->disp, "select Ctrl Mode",20);
        if( cmd == CMD_WRITE_RAM ) codeMotorCtrlMode = codes->code_value;
        set_code_default(0,9,0,codeMotorCtrlMode,0,codes);
        break;

    case CODE_start_ref:
        strncpy(codes->disp, "start ref (p.u)",20);
        if( cmd == CMD_WRITE_RAM ) code_start_ref = codes->code_value;
        set_code_default(0.0, 1.0, 0.05, code_start_ref,0,codes);
        break;

    case CODE_speed1:
        strncpy(codes->disp, "speed1 (p.u)",20);
        if( cmd == CMD_WRITE_RAM ) codeSpeed1 = codes->code_value;
        set_code_default(0.0,0.9,0.25,codeSpeed1,0,codes);
        break;

    case CODE_set_vdc:
        strncpy(codes->disp, "set Vdc 300.0",20);
        if( cmd == CMD_WRITE_RAM ) codeSetVdc = codes->code_value;
        set_code_default(0,1,0,codeSetVdc,0,codes);
        break;

    case CODE_protect_off:
        strncpy(codes->disp, "Protect Off",20);
        if( cmd == CMD_WRITE_RAM ) codeProtectOff = codes->code_value;
        set_code_default(0,1,1,codeProtectOff,0,codes);
        break;

    case CODE_pwm_freq:
        strncpy(codes->disp, "PWM Freq",20);
        if( cmd == CMD_WRITE_RAM ) codePwmFreq = codes->code_value;
        set_code_default(500.0,10000.0,8000.0,codePwmFreq,0,codes);
        break;

    case CODE_rate_power:
        strncpy(codes->disp, "Rate_power",20);
        if( cmd == CMD_WRITE_RAM ) codeRatePower = codes->code_value;
        set_code_default(100,2.0e+6,400,codeRatePower,0,codes);
        break;

    case CODE_rate_rpm:
        strncpy(codes->disp, "Rate RPM",20);
        if( cmd == CMD_WRITE_RAM ) codeRateRpm = codes->code_value;
        set_code_default(500,8000.0,1690.0,codeRateRpm,0,codes);
        break;

    case CODE_rate_volt:
        strncpy(codes->disp, "Rate Volt (Vrms)",20);
        if( cmd == CMD_WRITE_RAM ) codeRateVolt = codes->code_value;
        set_code_default(100.0,500.0,220.0,codeRateVolt,0,codes);
        break;

    case CODE_IaOffset:
        strncpy(codes->disp, "Ia Offset",20);
        if( cmd == CMD_WRITE_RAM ) codeIaOffset = codes->code_value;
        set_code_default(1000.0,3000.0,1830.0,codeIaOffset,0,codes);
        break;

    case CODE_IbOffset:
        strncpy(codes->disp, "Ib Offset",20);
        if( cmd == CMD_WRITE_RAM ) codeIbOffset = codes->code_value;
        set_code_default(1000.0,3000.0,1830.0,codeIbOffset,0,codes);
        break;

    case CODE_I_sense_value:
        strncpy(codes->disp, "I_sense_value (A)",20);
        if( cmd == CMD_WRITE_RAM ) I_sense_value = codes->code_value;
        set_code_default(5.0,2000.0, 30.0,I_sense_value ,0,codes);
        break;

    case CODE_u_phase_I_sense_span:
        strncpy(codes->disp, "u I_sense_span ",20);
        if( cmd == CMD_WRITE_RAM ) u_phase_I_sense_span = codes->code_value;
        set_code_default(0.5,1.5,1.0,u_phase_I_sense_span,0,codes);
        break;

    case CODE_v_phase_I_sense_span:
        strncpy(codes->disp, "v_I_sense_span ",20);
        if( cmd == CMD_WRITE_RAM ) v_phase_I_sense_span = codes->code_value;
        set_code_default(0.5,1.5,1.0,v_phase_I_sense_span,0,codes);
        break;

    case CODE_adc_Vdc_low:
        strncpy(codes->disp, "adc Vdc low",20);
        if( cmd == CMD_WRITE_RAM ) code_adc_Vdc_low = codes->code_value;
        set_code_default(100.0, 3000.0, 300.0, code_adc_Vdc_low,0,codes);
        break;

    case CODE_adc_Vdc_high:
        strncpy(codes->disp, "adc Vdc high",20);
        if( cmd == CMD_WRITE_RAM ) code_adc_Vdc_high = codes->code_value;
        set_code_default(500.0, 4000.0, 2000.0, code_adc_Vdc_high,0,codes);
        break;

    case CODE_Vdc_calc_low:
        strncpy(codes->disp, "Vdc calc_low",20);
        if( cmd == CMD_WRITE_RAM ) code_Vdc_calc_low = codes->code_value;
        set_code_default(0.0, 500.0, 10.0, code_Vdc_calc_low,0,codes);
        break;

    case CODE_Vdc_calc_high:
        strncpy(codes->disp, "Vdc calc_high",20);
        if( cmd == CMD_WRITE_RAM ) code_Vdc_calc_high = codes->code_value;
        set_code_default(50.0,999.0, 300.0,code_Vdc_calc_high,0,codes);
        break;

    case CODE_VF_DeadTimeGain:
        strncpy(codes->disp, "VF_DeadTimeGain",20);
        if( cmd == CMD_WRITE_RAM ) VF_DeadTimeGain = codes->code_value;
        set_code_default(0.0,2.0,1.0,VF_DeadTimeGain,0,codes);
        break;

    case CODE_VF_ExcitationTime:
        strncpy(codes->disp, "VF_ExcitationTime",20);
        if( cmd == CMD_WRITE_RAM ) VF_ExcitationTime = codes->code_value;
        set_code_default(0.0,3.5,1.0,VF_ExcitationTime,0,codes);
        break;

    case CODE_VF_Fs_Coeff:
        strncpy(codes->disp, "VF_Fs_Coeff (p.u)",20);
        if( cmd == CMD_WRITE_RAM ) VF_Fs_Coeff = codes->code_value;
        set_code_default(0.3,3.0,1.0,VF_Fs_Coeff,0,codes);
        break;

    case CODE_VF_Freq_TrqBoost:
        strncpy(codes->disp, "VF_Freq_TrqBoost",20);
        if( cmd == CMD_WRITE_RAM ) VF_Freq_TrqBoost = codes->code_value;
        set_code_default(0.0,10.0,1.5, VF_Freq_TrqBoost ,0,codes);
        break;

    case CODE_VF_Vs_Coeff_TrqBoost:
        strncpy(codes->disp, "VF_VsCoefTqBoost",20);
        if( cmd == CMD_WRITE_RAM ) VF_Vs_Coeff_TrqBoost = codes->code_value;
        set_code_default(0.0,0.2,0.1, VF_Vs_Coeff_TrqBoost ,0,codes);
        break;

    case CODE_VF_Rs_ThermalCoeff:
        strncpy(codes->disp, "VF_Rs_ThermalCoeff",20);
        if( cmd == CMD_WRITE_RAM ) VF_Rs_ThermalCoeff = codes->code_value;
        set_code_default(0.8,3.0,1.05, VF_Rs_ThermalCoeff ,0,codes);
        break;

    case CODE_VF_IR_Comp_FilterPole:
        strncpy(codes->disp, "vfIRCompFiltPole",20);
        if( cmd == CMD_WRITE_RAM ) VF_IR_Comp_FilterPole = codes->code_value;
        set_code_default(5.0,1000.0,100.0, VF_IR_Comp_FilterPole ,0,codes);
        break;

    case CODE_VF_Slip_Comp_FilterPole:
        strncpy(codes->disp, "vfSlipCompFiltPole",20);
        if( cmd == CMD_WRITE_RAM ) VF_Slip_Comp_FilterPole = codes->code_value;
        set_code_default(5.0,1000.0,20.0, VF_Slip_Comp_FilterPole ,0,codes);
        break;

    case CODE_VF_Rs:
        strncpy(codes->disp, "VF_Rs",20);
        if( cmd == CMD_WRITE_RAM ) VF_Rs = codes->code_value;
        set_code_default(0.0,50.0,0.0, VF_Rs ,0,codes);
        break;

//---
    case CODE_kpPosi:
        strncpy(codes->disp, "code_kpPosi",20);
        if( cmd == CMD_WRITE_RAM ) code_kpPosi = codes->code_value;
        set_code_default(0.1, 50.0, 3.5, code_kpPosi ,0,codes);
        break;

    case CODE_kpSpeed:
        strncpy(codes->disp, "code_kpSpeed",20);
        if( cmd == CMD_WRITE_RAM ) code_kpSpeed = codes->code_value;
        set_code_default(50.0,1000.0, 200.0, code_kpSpeed ,0,codes);
        break;

    case CODE_kiSpeed:
        strncpy(codes->disp, "code_kiSpeed",20);
        if( cmd == CMD_WRITE_RAM ) code_kiSpeed = codes->code_value;
        set_code_default(100.0, 5000.0, 2600.0, code_kiSpeed ,0,codes);
        break;

    case CODE_kpIdq:
        strncpy(codes->disp, "code_kpIdq",20);
        if( cmd == CMD_WRITE_RAM ) code_kpIdq = codes->code_value;
        set_code_default(0.1, 20.0, 4.5, code_kpIdq ,0,codes);
        break;

    case CODE_kiIdq:
        strncpy(codes->disp, "code_kiIdq",20);
        if( cmd == CMD_WRITE_RAM ) code_kiIdq = codes->code_value;
        set_code_default(10.0,1500.0, 150.0, code_kiIdq ,0,codes);
        break;

    case CODE_encoderPulse:
        strncpy(codes->disp, "code_encoderPulse",20);
        if( cmd == CMD_WRITE_RAM ) code_encoderPulse = codes->code_value;
        set_code_default(50.0, 8000.0, 1024.0, code_encoderPulse ,0,codes);
        break;

//--- 100 scope channel setting
    case CODE_scopeLoopCount:
        strncpy(codes->disp, "scope Loop Count",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeLoopCount = codes->code_value;
        set_code_default(0.0,100.0,10.0,codeScopeLoopCount,0,codes);
        break;
//--- ch1 Point Scale Offset
    case CODE_scopePointCh1:
        strncpy(codes->disp, "scope Point Ch1",20);
        if( cmd == CMD_WRITE_RAM ) codeScopePointCh1 = codes->code_value;
        set_code_default(0.0,50.0,0.0,codeScopePointCh1,0,codes);
        break;
    case CODE_scopeScaleCh1:
        strncpy(codes->disp, "scope Scale Ch1",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeScaleCh1 = codes->code_value;
        set_code_default(0.1,500.0,5.0,codeScopeScaleCh1,0,codes);
        break;
    case CODE_scopeOffsetCh1:
        strncpy(codes->disp, "scope Offset Ch1",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeOffsetCh1 = codes->code_value;
        set_code_default(0.0,50.0,0.0,codeScopeOffsetCh1,0,codes);
        break;
//--- ch2 Point Scale Offset
    case CODE_scopePointCh2:
        strncpy(codes->disp, "scope Point Ch2",20);
        if( cmd == CMD_WRITE_RAM ) codeScopePointCh2 = codes->code_value;
        set_code_default(0.0,50.0,1.0,codeScopePointCh2,0,codes);
        break;
    case CODE_scopeScaleCh2:
        strncpy(codes->disp, "scope Scale Ch2",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeScaleCh2 = codes->code_value;
        set_code_default(0.1,500.0,5.0,codeScopeScaleCh2,0,codes);
        break;
    case CODE_scopeOffsetCh2:
        strncpy(codes->disp, "scope Offset Ch2",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeOffsetCh2 = codes->code_value;
        set_code_default(0.0,50.0,0.0,codeScopeOffsetCh2,0,codes);
        break;
//--- ch3 Point Scale Offset
    case CODE_scopePointCh3:
        strncpy(codes->disp, "scope Point Ch3",20);
        if( cmd == CMD_WRITE_RAM ) codeScopePointCh3 = codes->code_value;
        set_code_default(0.0,50.0,2.0,codeScopePointCh3,0,codes);
        break;
    case CODE_scopeScaleCh3:
        strncpy(codes->disp, "scope Scale Ch3",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeScaleCh3 = codes->code_value;
        set_code_default(0.1,500.0,5.0,codeScopeScaleCh3,0,codes);
        break;
    case CODE_scopeOffsetCh3:
        strncpy(codes->disp, "scope Offset Ch3",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeOffsetCh3 = codes->code_value;
        set_code_default(0.0,50.0,0.0,codeScopeOffsetCh3,0,codes);
        break;
//--- ch4 Point Scale Offset
    case CODE_scopePointCh4:
        strncpy(codes->disp, "scope Point Ch4",20);
        if( cmd == CMD_WRITE_RAM ) codeScopePointCh4 = codes->code_value;
        set_code_default(0.0,50.0,3.0,codeScopePointCh4,0,codes);
        break;
    case CODE_scopeScaleCh4:
        strncpy(codes->disp, "scope Scale Ch4",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeScaleCh4 = codes->code_value;
        set_code_default(0.1,500.0,5.0,codeScopeScaleCh4,0,codes);
        break;
    case CODE_scopeOffsetCh4:
        strncpy(codes->disp, "scope Offset Ch4",20);
        if( cmd == CMD_WRITE_RAM ) codeScopeOffsetCh4 = codes->code_value;
        set_code_default(0.0,50.0,0.0,codeScopeOffsetCh4,0,codes);
        break;

	case CODE_END:
		return -2;
			
	default:
		return -1;
	}
	return 0;
}

void set_code_default(double min, double max, double defaults, double value,int open_level, CODE_INFO * codes )
{
	codes->type 		= TYPE_float;
	codes->open_level 	= open_level;
	codes->code_min		= min;
	codes->code_max		= max;
	codes->code_default	= defaults;
	codes->code_value 	= value;
}

int check_backup_data()
{
	UNION32	data;
	int check,address,cmd;
	
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
    for( address = 0 ; address <= CODE_END; address++){	 // code group �� 6��
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            Flag_TripDataBackup = 1;
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 0;
            check = check_code_data(address, data );	// check min and max boundary
            if(check)  return -1;
        }
    }
	return 0;
}


void save_backup_data()
{
	UNION32	data;
	int check,address,cmd;
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
	for( address = 0 ; address <= CODE_END ; address++){
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 1;
            write_code_2_eeprom( address,data);
            Flag_TripDataBackup = 0;
        }
	}
}

void backup_data_load()
{
	UNION32	data;
	int check,address,cmd;
	
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
    for( address = 0; address <= CODE_END ;address++)
    {
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            Flag_TripDataBackup = 1;
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 0;
            write_code_2_eeprom( address,data);
            code_inform.code_value = data.dword;
            cmd = CMD_WRITE_RAM;
            check = get_code_information( address,cmd, & code_inform);
        }
	}
}
double CheckSum()
{
    return 0.0;
}

int SaveDataProc(int addr, double data)
{
	int cmd,i,return_value;
	char SciBuf[30]={0};
	char str[30];
	UNION32 u32data,u32data2;

	return_value = 0;

	cmd = CMD_READ_DATA;

	i = get_code_information( addr,cmd,&code_inform); 

	if( i != 0 ) goto _SAVE_ERROR_INVALID_ADDR;   

	if( addr >= 800 ){

		if( data < 1.22 ) goto _SAVE_ERROR_INVALID_DATA; 
		if( data > 1.24 ) goto _SAVE_ERROR_INVALID_DATA; 
		switch(addr)
		{
		case CODE_Data_Check: 	return_value = check_backup_data();	break;
		case CODE_Data_Backup:
			strncpy(str,"Wait for Data Backup",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			save_backup_data();
			strncpy(str,"Wait for Error Check",20);
			load_sci_tx_mail_box(str);  delay_msecs(20);

			break;
		case CODE_Data_Load:
			strncpy(str,"Wait for Data Load !",20);
			load_sci_tx_mail_box(str); delay_msecs(20);	
			backup_data_load();
			break;
		case CODE_Data_Init:
			strncpy(str,"Wait For Data Init !",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			init_eprom_data();
			strncpy(str,"Data Init OK !      ",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			break;

		default:
			goto _SAVE_ERROR_INVALID_ADDR;
		}
		return return_value;
	}

    if( code_inform.code_min > data ){
        goto _SAVE_ERROR_DATA_UNDER;
    }
    else if( code_inform.code_max < data ){
        goto _SAVE_ERROR_DATA_OVER;
    }
    else {
        u32data.dword = data;
        read_eprom_data( addr, & u32data2);
        if( u32data.dword != u32data2.dword ){
            write_code_2_eeprom( addr, u32data);
            read_eprom_data( addr, & u32data2);

            if( u32data.dword != u32data2.dword ) goto _EEPROM_WRITE_ERROR;

            code_inform.code_value = data;
            cmd = CMD_WRITE_RAM;
            get_code_information( addr,cmd, & code_inform);

            // CheckSum Save
            u32data.dword = CheckSum();
            EepromSaveFlag = 1;
            write_code_2_eeprom(EPROM_ADDR_CHECKSUM, u32data);
            EepromSaveFlag = 0;

            load_sci_tx_mail_box("OK write success") ;
        }
        else{
            load_sci_tx_mail_box("Equal Data write skipped");
        }
        return 0;
    }
_SAVE_ERROR_INVALID_ADDR:
//	strcpy(SciBuf, "ADDR");
	strcpy(SciBuf,"Invalid Address" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_DATA_UNDER:

//	strcpy(SciBuf, "UNDE");

	strcpy(SciBuf,"Input data under" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_DATA_OVER:
//	strcpy(SciBuf, "OVER");
	strcpy(SciBuf,"Input data over" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_INVALID_DATA:
//	strcpy(SciBuf, "DATA");
	strcpy(SciBuf,"Invalid data " );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_EEPROM_WRITE_ERROR:
//	strcpy(SciBuf, "DATA");
	strcpy(SciBuf,"Eeprom write error" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;
}


int init_eprom_data()
{
	UNION32	data,data2;
	int check,address,cmd;

	data.dword  = 0.0;

	cmd = CMD_READ_DATA;
	for( address = 0 ; address < CODE_END ; address++ )
	{
		cmd = CMD_READ_DATA;
		check = get_code_information( address, cmd , & code_inform);
		if( check==0 ){
			data.dword = code_inform.code_default;
			read_eprom_data(address, & data2 );
			if( data.dword != data2.dword)	write_code_2_eeprom( address,data);
			read_eprom_data(address, & data2 );
			if( data.dword != data2.dword){
				load_sci_tx_mail_box("Trip : eeprom write" );
				delay_msecs(100);
				return -1;
			}	 
			else{
			    code_inform.code_value = data.dword;
			    cmd = CMD_WRITE_RAM;
			    check = get_code_information( address,cmd, & code_inform);
			}
		}
    }
	return 0;
}
void readAllCodes()
{
    int check;
    int addr,cmd;
    char * str;
    scia_tx_end_addr = 0;
    scia_tx_start_addr = 0;
    loadSciaTxMailBox("9:4:901:0.000e+0:");
    loadSciaTxMailBox("//Read code data:");
    loadSciaTxMailBox("code  data  Disc:");
    for( addr = 0 ; addr <= CODE_END ; addr++){
        check = get_code_information( addr, cmd , & code_inform);
        if( !check ){
            snprintf( str, 6 ,"%4d,",addr); load_scia_tx_mail_box(str);
            snprintf( str,20,"%.3e,",code_inform.code_value);
            load_scia_tx_mail_box(str);
            load_scia_tx_mail_box(code_inform.disp);
            load_scia_tx_mail_box(" : ");
            delay_msecs(4);
        }
    }
    load_scia_tx_mail_box("endOfReadall.\r\n");
}
//--- end of code_proc.c
