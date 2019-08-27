#include	<header.h>
#include	<extern.h>

void rampFunc1( double SetRef,double * pOutRef, double accelIn)
{
    static unsigned long ulCount;
    double OutRef;
    double accel_time,decel_time;

    OutRef = * pOutRef;
    if( ulGetNow_mSec( )== ulCount ) return;

    ulCount = ulGetNow_mSec( );
    if(accelIn <= 0.0) accel_time = decel_time = 1.0;            // debug
    else decel_time = accel_time = accelIn;

    if( OutRef >= 0 )
    {
        if (SetRef > OutRef){
            OutRef += 0.001 / accel_time;
            if( OutRef > SetRef ) OutRef = SetRef;
        }else if (SetRef < OutRef){
            OutRef -=  0.001 / decel_time ;
            if( OutRef < SetRef ) OutRef = SetRef;
        }
    } else{
        if (SetRef > OutRef){
            OutRef += 0.001 / decel_time ;
            if( OutRef > SetRef ) OutRef = SetRef;
        } else if (SetRef < OutRef){
            OutRef -= 0.001 / accel_time ;
            if( OutRef < SetRef ) OutRef = SetRef;
        }
    }
    * pOutRef = OutRef;
}

void RefFunc( double SetRef,double * pOutRef)
{
    static unsigned long ulCount;
    double OutRef;
    double accel_time,decel_time;

    OutRef = * pOutRef;
    if( ulGetNow_mSec( )== ulCount ) return;

    ulCount = ulGetNow_mSec( );
    if(codeAccelTime1 <= 0.0) codeAccelTime1 = 0.01;            // debug
    if(codeDecelTime1 <= 0.0) codeDecelTime1 = 0.01;            // debug
/*
    if( fabs(OutRef) <= digital_speed2 )    { accel_time = accel_time1; decel_time = decel_time1; }
    else                                { accel_time = accel_time2; decel_time = decel_time2; }
*/
    accel_time = codeAccelTime1; decel_time = codeDecelTime1;
    if( OutRef >= 0 )
    {
        if (SetRef > OutRef){
            OutRef += 0.001 / accel_time;
            if( OutRef > SetRef ) OutRef = SetRef;
        }else if (SetRef < OutRef){
            OutRef -=  0.001 / decel_time ;
            if( OutRef < SetRef ) OutRef = SetRef;
        }
    } else{
        if (SetRef > OutRef){
            OutRef += 0.001 / decel_time ;
            if( OutRef > SetRef ) OutRef = SetRef;
        } else if (SetRef < OutRef){
            OutRef -= 0.001 / accel_time ;
            if( OutRef < SetRef ) OutRef = SetRef;
        }
    }
    * pOutRef = OutRef;
}


void ramp_proc( double set_ref, double * out_ref)
{
	RefFunc( set_ref, out_ref );
}

//----------------------------------
// End of File
//----------------------------------
