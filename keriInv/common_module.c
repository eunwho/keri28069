#include	<header.h>
#include	<extern.h>

double linear_eq(double x1, double x2, double y1, double y2, double x )
{
	double y;
	y = (( y2-y1) / ( x2 - x1 )) * x  + (( y1 * x2 - y2 * x1 )/ (x2- x1));
	return y;
}

void LPF1(double Ts,double pole,double in,double *out)
{
	*out+=pole*(in-*out)*Ts;
}

void Nop()
{
  asm ("      nop");
}
void PI_Damp_Controller(double limit,double Ts, double damp_factor, double Kp,double Ki,double ref,double feedback,double *integral,double *output)
{
	*integral+=Ki*(ref-feedback)*Ts;
	if (*integral>fabs(limit))			*integral=fabs(limit);
	else if (*integral<-fabs(limit))	*integral=-fabs(limit);
	*output=Kp*(damp_factor*ref-feedback)+*integral;
}

void SetSensorOffset()
{
}

void PowerOnReset()
{

}

unsigned long ulGetTime_mSec(unsigned long Start_mSec)
{
	unsigned long Temp;
	 
	if( CpuTimer0.InterruptCount < Start_mSec){
		Temp = ((unsigned long )(0xFFFFFFFF) - Start_mSec) + CpuTimer0.InterruptCount; 		
	}
	else{
		Temp = CpuTimer0.InterruptCount - Start_mSec ;
	}
	return Temp;
}

unsigned long ulGetNow_mSec( )
{
	return CpuTimer0.InterruptCount;

}

void delay_msecs( unsigned long ulmSec)
{
	unsigned long Start_mSec,ulTemp;

	ulTemp =0;
	Start_mSec = ulGetNow_mSec( );

	while( ulTemp < ulmSec)
	{
		ulTemp = ulGetTime_mSec( Start_mSec );
	}
}

int periodic_check(unsigned long  msec)
{
	static unsigned long count_msec=0;

	if( ulGetTime_mSec(count_msec) > msec ){
		count_msec = ulGetNow_mSec( );
		return 0;
	}
	return -1;				
}

int iGetAinCmd(int * piCommand, double * pfReference)
{
	int iTemp;
	iTemp = 0;

	* piCommand =  CMD_NULL;
	* pfReference = 0.0;
	return iTemp;
}
// 2018.0518 remove analog command proc
void get_command( int * command, double * ref )
{
	int digital_cmd,sci_cmd;
	double digital_reference,sci_ref;

	digital_input_proc( & digital_cmd, & digital_reference);
	serial_com_proc( & sci_cmd, & sci_ref );

	* command = digital_cmd;
	* ref = digital_reference;

	if( sci_cmd != CMD_NULL){
		if( sci_cmd == CMD_SAVE){
			* command = sci_cmd ;
		}
		else if( sci_cmd == CMD_RESET){
			* command = sci_cmd ;
		}
		else if( sci_cmd == CMD_READ_ALL){
			* command = sci_cmd ;
		}
	}
}

void get_adc_offset()
{
/*
    int LoopCtrl;

	Uint32 RunTimeMsec,StartTimeMsec;
	double u_offset_in, v_offset_in;
	double R_offset_in, S_offset_in;

	double u_offset_out, v_offset_out;
	double R_offset_out, S_offset_out;
	
	UNION32 u32data;

	load_sci_tx_mail_box( "\n***********************"); delay_msecs(10);
	load_sci_tx_mail_box( "\n Start ADC Offset Calc "); delay_msecs(10);
	load_sci_tx_mail_box( "\n***********************"); delay_msecs(10);

	gfRunTime=0.0;
	LoopCtrl = 1;

	while(LoopCtrl == 1)
	{
		if( gfRunTime >= 5.0 ) LoopCtrl = 0;
		RunTimeMsec = ulGetTime_mSec( StartTimeMsec);
		if(RunTimeMsec > 1){
			StartTimeMsec = ulGetNow_mSec( );
			u_offset_in = (double)adc_result[0];
			v_offset_in = (double)adc_result[1];
			R_offset_in = (double)adc_result[3];
			S_offset_in = (double)adc_result[4];

			LPF1(0.002,10.0,u_offset_in, & u_offset_out);
			LPF1(0.002,10.0,v_offset_in, & v_offset_out);
			LPF1(0.002,10.0,R_offset_in, & R_offset_out);
			LPF1(0.002,10.0,S_offset_in, & S_offset_out);
		}
	}

	if( gfRunTime >= 5.0 ){
		codeIAdcOffset1st = (int)u_offset_out;
		codeIAdcOffset2nd = (int)v_offset_out;

		codeIAdcOffset3rd = (int)R_offset_out;
		codeIAdcOffsetOut = (int)S_offset_out;

		u32data.word.word0 = codeIAdcOffset1st; write_code_2_eeprom(CODE_IAdcOffset1st,u32data);
		u32data.word.word0 = codeIAdcOffset2nd; write_code_2_eeprom(CODE_IAdcOffset2nd,u32data);

		u32data.word.word0 = codeIAdcOffset3rd; write_code_2_eeprom(CODE_IAdcOffset3rd,u32data);
		u32data.word.word0 = codeIAdcOffsetOut; write_code_2_eeprom(CODE_IAdcOffsetOut,u32data);
				
		load_sci_tx_mail_box("\n*********************");delay_msecs(10);		
		load_sci_tx_mail_box("\n OK Adc offset Saved ");delay_msecs(10);		
		load_sci_tx_mail_box("\n*********************");delay_msecs(10);		
	}
*/
}
//--- end of file
