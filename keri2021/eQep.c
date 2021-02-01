/*
 * eqep.c
 *
 *  Created on: 2019. 7. 26.
 *      Author: light
 */

#include    <header.h>
#include    <extern.h>

#define Main_clock_90mhz  90000000.0
#define EQEP_interrupt_time_set_ms      5
#define EQEP_interrupt_time_value       (EQEP_interrupt_time_set_ms*90000)
#define EQEP_compute_hz_buffer          (Main_clock_90mhz/EQEP_interrupt_time_value)
#define EQEP_capture_clk    (90000000/8)   //EQep1Regs.QCAPCTL.bit.CCPS= 3; //8����

void Init_EQep(void)
{

    encoderMaxCount = (Uint16)(code_encoderPulse * 4 -1 );
    inv_encoderMaxCount = 1.0 / ( encoderMaxCount +1);
    inv_QepTime = 1.0 / EQEP_interrupt_time_set_ms / 1000.0;

    EALLOW;

    //EQep1Regs.QEPCTL &= (~QEP_QEPCTL_QPEN);
    EQep1Regs.QEPCTL.bit.QPEN = 0;

    EQep1Regs.QPOSINIT = 0; //eQEP Position Counter Initialization (QPOSINIT) Register

    EQep1Regs.QEINT.all = 0;

    EQep1Regs.QCLR.all = 0xfff;

    EQep1Regs.QPOSCNT = 0;

    EQep1Regs.QPOSMAX = encoderMaxCount;                 //

    EQep1Regs.QDECCTL.bit.QSRC = 0;     // Quadrature counter mode
    //EQep1Regs.QDECCTL.bit.QSRC = 2;     // UP counter mode
    EQep1Regs.QDECCTL.bit.SOEN = 0;     // 1= Enable position-compare sync output
    EQep1Regs.QDECCTL.bit.SWAP = 0;
    EQep1Regs.QDECCTL.bit.IGATE = 0;    // 1= Gate the index pin with strobe
    EQep1Regs.QDECCTL.bit.XCR = 0;      //0=2x resolution: Count the rising/falling edge, 1=1x resolution: Count the rising edge only
    EQep1Regs.QDECCTL.bit.QAP = 0;
    EQep1Regs.QDECCTL.bit.QBP = 0;
    EQep1Regs.QDECCTL.bit.QIP = 0;

    EQep1Regs.QEPCTL.bit.FREE_SOFT = 2;     //2=������ī���Ͱ� ���ķ��̼� ������� ����
    //EQep1Regs.QEPCTL.bit.PCRM = 3;  //�����ð� �̺�Ʈ�� ���� QPOSCNT �缳��, Position counter reset mode ,1=Position counter reset on the maximum position
    EQep1Regs.QEPCTL.bit.PCRM = 1;      //�ִ� ��ġ���� QPOSCNT �� ����
    EQep1Regs.QEPCTL.bit.SEI = 0;
    EQep1Regs.QEPCTL.bit.IEI = 0;
    EQep1Regs.QEPCTL.bit.IEL = 0;   //EQep1Regs.QEPCTL.bit.IEL = 1;
    EQep1Regs.QEPCTL.bit.SWI = 0;
    EQep1Regs.QEPCTL.bit.UTE = 1;   //eQEP unit timer enable
    EQep1Regs.QEPCTL.bit.WDE = 0;

    EQep1Regs.QPOSCTL.bit.PCE = 0;

    EQep1Regs.QCAPCTL.bit.CEN = 1;  //1= eQEP capture unit is enabled
    //EQep1Regs.QCAPCTL.bit.CCPS= 6;  //64����//SYSCLK�� ���ֺ�
    //EQep1Regs.QCAPCTL.bit.UPPS= 1;  //2����//QA,QB �� Ŭ���������� ��������� ���ֺ�
    EQep1Regs.QCAPCTL.bit.CCPS= 3;  //8����//SYSCLK�� ���ֺ�
    EQep1Regs.QCAPCTL.bit.UPPS= 1;  //2����//QA,QB �� Ŭ���������� ��������� ���ֺ�

    //EQep1Regs.QUPRD= 900000;        //90,000,000/900,000 = 100hz ����   //10ms ����
    EQep1Regs.QUPRD = EQEP_interrupt_time_value;    //5ms ����
    EQep1Regs.QEINT.bit.UTO = 1;    //1=Unit time out interrupt enable
    //EQep1Regs.QEINT.all = 0xffe;

    EQep1Regs.QEPCTL.bit.QPEN = 1;//eQEP position counter is enabled

    EDIS;
}


interrupt void eqep1_isr(void)     //5ms ���ͷ�Ʈ
{
    int32 POSCNT_new,POSCNT_value;      //float->int �� �ٲܰ�
    // Uint16 i,count=0;

    //POSCNT_new = EQep1Regs.QPOSLAT;
    POSCNT_new = EQep1Regs.QPOSCNT;

    if(EQep1Regs.QEPSTS.bit.QDF==1){             //�ð�����϶�
        if(POSCNT_new >= POSCNT_old){
            POSCNT_value = POSCNT_new - POSCNT_old;
        } else {
            POSCNT_value = encoderMaxCount + POSCNT_new - POSCNT_old;
        }
    }  else {
        if(POSCNT_new > POSCNT_old) {
            POSCNT_value = -(encoderMaxCount + POSCNT_new -POSCNT_old);
        }  else    {
            POSCNT_value = POSCNT_new -POSCNT_old;
        }
    }

    POSCNT_old = POSCNT_new;
    theta_m = PI_2 * ( POSCNT_new - posCountOrigin )  * inv_encoderMaxCount ;
     wr_m = PI_2 * POSCNT_value * inv_encoderMaxCount * inv_QepTime;

    EQep1Regs.QCLR.bit.UTO = 1;     //Clear UTO(unit time out) interrupt flag
    EQep1Regs.QCLR.bit.INT = 1;     //Clear INT(unit time out) interrupt flag

    // Acknowledge this interrupt to receive more interrupts from group 5
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}

// end of eQep.c

