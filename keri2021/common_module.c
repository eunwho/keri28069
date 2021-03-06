#include	<header.h>
#include	<extern.h>

void LPF1(double TsIn,double pole,double in,double *out)
{
    *out+=pole*(in-*out)*TsIn;
}

double linear_eq(double x1, double x2, double y1, double y2, double x )
{
	double y;

	y = (( y2-y1) / ( x2 - x1 )) * x  + (( y1 * x2 - y2 * x1 )/ (x2- x1));
	return y;
}

void Nop()
{
  asm ("      nop");
}
void PI_Damp_Controller(double limit,double TsIn, double damp_factor, double Kp,double Ki,double ref,double feedback,double *integral,double *output)
{
	*integral+=Ki*(ref-feedback)*TsIn;
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

#define analog_cmd_in_span1     1.0
#define analog_cmd_in_zero1     0.0

void analog_cmd_proc(double * ana_ref)
{
    //    double temp = ((double) (adcCmdAnalog)) * 0.0002441406250;
    double temp = adcExSensor * 0.0002441406250;
    * ana_ref = temp * analog_cmd_in_span1 - analog_cmd_in_zero1;
}

void get_command( int * command, double * ref )
{
	int sci_cmd, digital_cmd;
	double sci_ref, digital_ref;

	readPwmTripInputState();    // read pwmTripInput and Digital Input
	serial_com_proc( & sci_cmd, & sci_ref );
//	analog_cmd_proc( & analog_ref);
	digital_input_proc(&digital_cmd, &digital_ref);

	* command = digital_cmd;
	* ref = codeStartRef;

	if( digital_cmd == CMD_START){
	    * command = sci_cmd;
	    * ref = sci_ref;
	} else {
	    * command = CMD_STOP;
	    * ref = 0.0;
	}

	Nop();
}

//---------------------------------
// end of file
//----------------------------------

