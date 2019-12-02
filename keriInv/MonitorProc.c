#include	<header.h>
#include	<extern.h>

void monitor_proc()     // need_edit
{
    int temp1,temp2,temp3,temp4,temp5;
    static int count = 0;

    int secTemp,minTemp;

    count = (count < 998 ) ? count + 1 : 0;

    temp1 = (Vout < 0.0 )? 0 : (int)( floor (Vout));
    temp2 = (Vout < 0.0 )? 0 : ((int)(Vout * 10.0)) % 10;

    temp3 = (Pout < 0.0 ) ? 0 : (int)(Pout/1000);
    temp4 = (Pout < 0.0 ) ? 0 : ((int)(Pout / 100.0)) % 10;

    temp5 = (Vdc < 0.0 ) ? 0: (int)(Vdc);

    secTemp = secRun % 60;
    minTemp = secRun / 60;

    sprintf( monitOut2,"\x02 1Vo =%02d.%01dV: Po=%02d.%01dkW\x03\r\n",temp1,temp2,temp3,temp4);
    sprintf( monitOut3,"\x02 2Vdc=%03dV: %d:%02d:%02d:%02d\x03\r\n",temp5,dayRun,hourRun,minTemp,secTemp);

    switch(gMachineState){
        case STATE_POWER_ON:
            strncpy(monitOut1,"\x02 0[POWER ON] wait ...\x03\r\n",25);
            break;

        case STATE_READY:

            temp1 = (int)(floor(Iout+0.5));
            sprintf(monitOut1,"\x02 0[READY] Io=%3d[A]   \x03\r\n",temp1);
            break;

        case STATE_TRIP:

            temp1 = (int)(floor(Iout+0.5));
            sprintf( monitOut1,"\x02 0[TRIP %03d] Io=%3d[A]\x03\r\n",TripInfoNow.CODE,temp1);

            temp1 = (int)( floor (TripInfoNow.CURRENT+0.5));
            temp2 = (int)(TripInfoNow.VOUT);
            temp3 = ((int)(TripInfoNow.VOUT * 10.0)) % 10;
            sprintf( monitOut2,"\x02 1AT =%03dA : AT =%02d.%1dV \x03\r\n",temp1,temp2,temp3);

            temp1 = (int)(TripInfoNow.DATA);
            if( (temp1 > 999 )||(temp1 < 0)) temp1 = 999;

            temp2 = (int)( floor (TripInfoNow.VDC + 0.5));
            if( (temp2 > 999 ) || ( temp2 < 0)) temp2 = 999;

            sprintf( monitOut3,"\x02 2data=%03d: AT=%03dV\x03\r\n",temp1,temp2);
            sprintf( monitOut4,"\x02 3Er:%s%03d\x03\r\n",TripInfoNow.MSG,count);
            break;

        case STATE_INIT_RUN:
            sprintf(monitOut1,"\x02 0[INIT RUN] Io =%03d[A] \x03\r\n",temp1);
            break;

        case STATE_GO_STOP:
            temp1 = (int)(floor(Iout+0.5));
            sprintf(monitOut1,"\x02 0[GO STOP] Io =%03d[A]\x03\r\n",temp1);
            break;
        case STATE_RUN:
            //            temp1 = (Iout < 0.0 ) ? 0: (int)(floor(Iout+0.5));
            temp1 = (int)(floor(Iout+0.5));
            sprintf(monitOut1,"\x02 0[ RUN ] Io =%03d[A]\x03\r\n",temp1);
            break;

        default:
            sprintf(monitOut1,"\x02 0[SYSTEM INIT ] %d\x03\r\n",count);
            break;
    }
}

void GetInputMark(char * str)
{
	strncpy(str,"xxxx",20);			// debug
}
//--- End of file.
