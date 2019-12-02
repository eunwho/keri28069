#include	<header.h>
#include	<extern.h>

#define codeAccelTime1  5.0
#define codeDecelTime1  1.0

void ramp_proc( double SetRef,double * pOutRef)
{
	static unsigned long ulCount;

	double OutRef;
	
	OutRef = * pOutRef;

 	if( ulGetNow_mSec( ) == ulCount ) return;
	
	ulCount = ulGetNow_mSec( );

	if (SetRef > OutRef){
        OutRef += 0.001 / codeAccelTime1;
        if( OutRef > SetRef ) OutRef = SetRef;
    }
    else if (SetRef < OutRef){
        OutRef -=  0.001 / codeDecelTime1 ;
        if( OutRef < SetRef ) OutRef = SetRef;
    }
	* pOutRef = OutRef; 
}	

//----------------------------------
// End of File
//----------------------------------
