#include	<header.h>
#include	<extern.h>

#define code_VsKi 100.0

inline double speedPICtrl( ){
    double isqRef;
    double IntegralLimit;

    wr_ref = wr_rat * reference_out;
    wr_err = wr_ref-wr;

    // wr_ErrInt += Ki_wr*wr_err*inv_P_pair * Ts * 10.0;
    wr_ErrInt += Ki_wr*wr_err*inv_P_pair * Ts;

    IntegralLimit = Kp_wr*fabs(K_Damp_wr*wr_ref-wr)*inv_P_pair + I_QS_rat;

    if      (wr_ErrInt >  IntegralLimit) wr_ErrInt =  IntegralLimit;
    else if (wr_ErrInt < -IntegralLimit) wr_ErrInt = -IntegralLimit;

    lpfIsqIn[0] = Kp_wr * ( K_Damp_wr * wr_ref - wr ) * inv_P_pair + wr_ErrInt;
    lpf2nd( lpfIsqIn, lpfIsqOut, lpfIsqK);
    isqRef = lpfIsqOut[0];
    if (gfRunTime<0.05)     wr_ErrInt=0.0;
    return isqRef;
}

inline void calcVIdqValue(){

    CosDeltaTheta=cos(we*Ts);
    SinDeltaTheta=sin(we*Ts);

    Us_dq[ds] =  Vs_dq[ds] * CosDeltaTheta + Vs_dq[qs] * SinDeltaTheta;
    Us_dq[qs] = -Vs_dq[ds] * SinDeltaTheta + Vs_dq[qs] * CosDeltaTheta;

    Vs_dq[ds]=Us_dq[ds];
    Vs_dq[qs]=Us_dq[qs];

    Fs_dq[ds] += (Vs_dq[ds]-Rs*Is_dq[ds])*Ts;
    Fs_dq[qs] += (Vs_dq[qs]-Rs*Is_dq[qs])*Ts;
}

inline void calcMaxVI(){

    Is_DQ[DS] = CosTheta*Is_dq[ds] + SinTheta*Is_dq[qs];
    Is_DQ[QS] = -SinTheta*Is_dq[ds] + CosTheta*Is_dq[qs];
    Isd_Square = Is_DQ[DS] * Is_DQ[DS];
    Isq_Square = Is_DQ[QS] * Is_DQ[QS];
    Is_Square = Isd_Square + Isq_Square;
    Is_Scalar = sqrt(Is_Square);
    // Is_Scalar = Is_mag;          // debug 2020.0202

    Vs_DQ[DS] = CosTheta*Vs_dq[ds] + SinTheta*Vs_dq[qs];
    Vs_DQ[QS] = -SinTheta*Vs_dq[ds] + CosTheta*Vs_dq[qs];
    Vsd_Square = Vs_DQ[DS] * Vs_DQ[DS];
    Vsq_Square = Vs_DQ[QS] * Vs_DQ[QS];
    Vs_Square = Vsd_Square + Vsq_Square;
    lpfVsIn[0] = sqrt(Vs_Square);
    lpf2nd( lpfVsIn, lpfVsOut, lpfVsK);
    Vs_Scalar = lpfVsOut[0];
}

inline void IsdCurrentPICtrl(){

    // double retValue;

    I_DS0_0 += (inv_sigma_Tr)*( ((sigma_Tr*w_sl*Is_DQ[QS]) + (sigma_minus_1_div_sigma_Ls*Fs)) - I_DS0_0)*Ts;
    I_DS0 = I_DS0_0 + inv_sigma_Ls*Fs;

    I_DS_err=Is_DQ[DS] - I_DS0;

    if (gfRunTime < 0.05){
        Pf=1.0;
        DeltaLambda = GammaLambda * sigma_Ls * I_DS_err;
        DeltaTheta=0.0;
    }else{
        if (Pf>=0.0){
            DeltaTheta=GammaTheta_M*(sgn_I_QS*inv_Is_rat)*I_DS_err;
            DeltaLambda=GammaLambda*sigma_Ls*I_DS_err;
        } else {
            DeltaTheta=-GammaTheta_R*(sgn_I_QS*inv_Is_rat)*I_DS_err;
            if (fabs(Is_DQ[QS])<(0.05*I_QS_rat))
                DeltaLambda=GammaLambda*sigma_Ls*I_DS_err;
            else
                DeltaLambda=GammaLambda*sigma_Ls*I_DS_err*I_QS_rat/(I_QS_rat+GammaLambda_R_Constant*(fabs(Is_DQ[QS])-0.05*I_QS_rat));
        }
    }
    if (DeltaLambda>Max_DeltaLambda)        DeltaLambda = Max_DeltaLambda;
    else if (DeltaLambda<-Max_DeltaLambda)  DeltaLambda =-Max_DeltaLambda;
    if (DeltaTheta>Max_DeltaTheta)          DeltaTheta  = Max_DeltaTheta;
    else if (DeltaTheta<-Max_DeltaTheta)    DeltaTheta  =-Max_DeltaTheta;

    SinCosDeltaTheta=sqrt(1.0-2.0*DeltaTheta+2.0*DeltaTheta*DeltaTheta);
    inv_SinCosDeltaTheta=1.0/SinCosDeltaTheta;
    CosDeltaTheta=(1.0-DeltaTheta)*inv_SinCosDeltaTheta;
    SinDeltaTheta=DeltaTheta*inv_SinCosDeltaTheta;
    SinTheta1=SinTheta*CosDeltaTheta + CosTheta*SinDeltaTheta;
    CosTheta1=CosTheta*CosDeltaTheta - SinTheta*SinDeltaTheta;

    Fs+=DeltaLambda;
    Fs_dq[ds]=Fs*CosTheta1;
    Fs_dq[qs]=Fs*SinTheta1;

    Is_DQ_ref[DS] = I_DS0_0 + inv_sigma_Ls * Fs_ref;
    // retValue = I_DS0_0 + inv_sigma_Ls * Fs_ref;

    if (gfRunTime < ExcitationTime){
        Is_DQ_max[DS]=(ExcitationTime+Tr)/(ExcitationTime+sigma*Tr)*(Fs_B*inv_Ls);
        if (Is_DQ_max[DS]<(Fs_B*inv_Ls))    Is_DQ_max[DS] = Fs_B*inv_Ls;
        else if (Is_DQ_max[DS] > 0.8*Is_max)  Is_DQ_max[DS] = 0.8*Is_max;
    }

    if      ( Is_DQ_ref[DS] >= Is_DQ_max[DS])       Is_DQ_ref[DS] = Is_DQ_max[DS];
    else if ( Is_DQ_ref[DS] <  (0.1*inv_Ls*Fs_ref)) Is_DQ_ref[DS] = 0.1*inv_Ls*Fs_ref;

    // return retValue;
}

inline double VsD_PICtrl( double isdref ){
    double VsD_Ref;

    Vs_DQ_max[DS] = Vs_max;

    Is_DQ_ErrInt[DS] += codeKiIs * ( isdref - Is_DQ[DS] ) * Ts ;

    if (Is_DQ_ErrInt[DS]>Vs_DQ_max[DS])         Is_DQ_ErrInt[DS] =  Vs_DQ_max[DS];
    else if (Is_DQ_ErrInt[DS]<-Vs_DQ_max[DS])   Is_DQ_ErrInt[DS] = -Vs_DQ_max[DS];

    VsD_Ref = codeKpIs * (K_Damp_Is * Is_DQ_ref[DS] - Is_DQ[DS]) + Is_DQ_ErrInt[DS];
    return VsD_Ref;
}

inline double VsQ_PICtrl( double isqref ){

    double retValue;

    Is_DQ_max[QS]=sqrt( fabs(Is_max*Is_max - Is_DQ_ref[DS]*Is_DQ_ref[DS]) );   //

    if      ( Is_DQ_ref[QS] >  Is_DQ_max[QS] )  isqref =  Is_DQ_max[QS];
    else if ( Is_DQ_ref[QS] < -Is_DQ_max[QS] )  isqref = -Is_DQ_max[QS];

    Vs_DQ_max[QS]=2.0*Vs_max;
    Is_DQ_ErrInt[QS] += codeKiIs*( isqref - Is_DQ[QS])*Ts;

    if      (Is_DQ_ErrInt[QS]>Vs_DQ_max[QS])    Is_DQ_ErrInt[QS] = Vs_DQ_max[QS];
    else if (Is_DQ_ErrInt[QS]<-Vs_DQ_max[QS])   Is_DQ_ErrInt[QS] = -Vs_DQ_max[QS];

    retValue = codeKpIs*(K_Damp_Is*Is_DQ_ref[QS] - Is_DQ[QS]) + Is_DQ_ErrInt[QS];
    return retValue;
}

inline double IsDRefVoltagePICtrol( ){
    double retValue;
    double Vs_err;

    Vs_err = Vs_max  - Vs_Scalar;
    Vsw_ErrInt += KiVsw * Vs_err * Ts;

    if ( Vsw_ErrInt >  codeVswErrLimit )    Vsw_ErrInt =  codeVswErrLimit;
    if ( Vsw_ErrInt < (-codeVswErrLimit) )  Vsw_ErrInt = -codeVswErrLimit;

    retValue = KpVsw * Vs_err + Vsw_ErrInt;
    if (gfRunTime<0.05)     Vsw_ErrInt=0.0;

    return retValue;
}

#define fwBeta  0.00005 // 1/2000
//#define fwBeta  1 // 1/2000

inline double IsQRefVoltPICtrolbk(double iSQ_Ref){
    double tmpIsQRef, VsdMax;
    double Isq_maxA, Isq_maxB;
    double IqMax;

    VsdMax = Vs_max * INV_ROOT2;

    lpfVsdIn[0] = VsdMax -abs( Vs_DQ[DS]);
    lpf2nd( lpfVsdIn, lpfVsdOut, lpfVsdK);

    IsqFw = fwBeta * sigma_Ls * lpfVsdOut[0]  * we * codeFwCoef2;

    // IsqFw = ( IsqFw < 0.0 ) ? 0.0 : IsqFw ;

    IqMax = sqrt(Is_max - Isd_Square);

    Isq_maxB = (codeFw2On > 0.5) ? (  IqMax- IsqFw) : IqMax;    //
    Isq_maxA = abs(Is_DQ[DS] * inv_sigma);

    tmpIsQRef = ( Isq_maxA < Isq_maxB  ) ? Isq_maxA  : Isq_maxB;

    if (iSQ_Ref > 0.0 ){
        tmpIsQRef = ( tmpIsQRef < iSQ_Ref  ) ? tmpIsQRef : iSQ_Ref;
    } else {
        tmpIsQRef = -tmpIsQRef;
        tmpIsQRef = ( tmpIsQRef > iSQ_Ref  ) ? tmpIsQRef : iSQ_Ref;
    }
    return tmpIsQRef;
}
inline double IsQRefVoltPICtrol(double iSQ_Ref){
    double tmpIsQRef, VsdMax;
    double Isq_maxA, Isq_maxB;
    double IqMax;

    VsdMax = Vs_max * INV_ROOT2;

    lpfVsdIn[0] = VsdMax -abs( Vs_DQ[DS]);
    lpf2nd( lpfVsdIn, lpfVsdOut, lpfVsdK);

    IsqFw = fwBeta * sigma_Ls * lpfVsdOut[0]  * we * codeFwCoef2;

    // IsqFw = ( IsqFw < 0.0 ) ? 0.0 : IsqFw ;

    IqMax = sqrt(Is_max - Isd_Square);

    Isq_maxB = (codeFw2On > 0.5) ? (  IqMax- IsqFw) : IqMax;    //
    Isq_maxA = abs(Is_DQ[DS] * inv_sigma);

    tmpIsQRef = ( Isq_maxA < Isq_maxB  ) ? Isq_maxA  : Isq_maxB;

    if (iSQ_Ref > 0.0 ){
        tmpIsQRef = ( tmpIsQRef < iSQ_Ref  ) ? tmpIsQRef : iSQ_Ref;
    } else {
        tmpIsQRef = -tmpIsQRef;
        tmpIsQRef = ( tmpIsQRef > iSQ_Ref  ) ? tmpIsQRef : iSQ_Ref;
    }
    return tmpIsQRef;
}

void fieldWeakenVoltageLoopCtrl()
{
    double dtemp1;
    double Isq_maxA,Isq_maxB,Isq_maxC;
    double IsqCmd;

    //    Vs_max=0.57735*Vdc;   // 1.0/sqrt(3.0)=0.57735027
    Vs_max = Vs_rat * codeFwCoef1;   // 1.0/sqrt(3.0)=0.57735027

    calcVIdqValue();                // get DQ value V, I from Is_dq[ds],[dq] Vs_dq[ds],[qs]
    Fs = sqrt(Fs_dq[ds]*Fs_dq[ds] + Fs_dq[qs]*Fs_dq[qs]);

    if ( gfRunTime >0.05){
        inv_Fs=1.0/Fs; CosTheta = Fs_dq[ds]*inv_Fs; SinTheta = Fs_dq[qs]*inv_Fs;
    }else { inv_Fs=0.0; SinTheta=0.0;  CosTheta=1.0; }

    calcMaxVI();
    //---get we
    we_in = (Vs_DQ[QS] - Rs*Is_DQ[QS]) * inv_Fs;
    we   += ( 0.5 * wr_FilterPole ) * (we_in - we ) * Ts;

    dtemp1 = (we > 0.0) ? we : -we;

    Is_DQ_max[QS] = sqrt(Is_max * Is_max - Isd_Square);
    Is_DQ_max[DS] = Is_D_Rate;

    Isq_maxA = abs(Is_DQ[DS] * inv_sigma);
    Isq_maxB = sqrt(Is_max - Isd_Square);
    Isq_maxC = Te_rat * Lr * inv_Kt * Lr_div_Lm  * inv_Lm;

    Is_DQ_max[QS] = ( Isq_maxA < Isq_maxB )? Isq_maxA : Isq_maxB;
    Is_DQ_max[QS] = ( Is_DQ_max[QS] < Isq_maxC )? Is_DQ_max[QS] : Isq_maxC;

    if (dtemp1 < we1FieldWeak ) Fs_ref0 = Fs_B;
    else  Fs_ref0 = Fs_B * we1FieldWeak / we;

    if (Fs_ref0 > Fs_B) Fs_ref0 = Fs_B;
    Fs_ref += 100.0 * ( Fs_ref0 - Fs_ref ) * Ts;

    if ( gfRunTime > 0.05 ){
        w_sl=(sigma_Ls*(Is_DQ[QS] - prev_I_QS)*inv_Ts + SlipCoeff*Is_DQ[QS])/(Fs - sigma_Ls*Is_DQ[DS]);
        prev_I_QS=Is_DQ[QS];
        w_sl += 0.5 * SlipCompCoeff * Pf * Delta_wr;
    } else {
        we=0.0; we_in=0.0; w_sl=0.0; prev_I_QS=Is_DQ[QS];
    }

    Pf = ((Is_DQ[QS]*(Vs_DQ[QS] - Rs*Is_DQ[QS])) >= 0.0) ? 1.0 : -1.0;
    sgn_I_QS = (Is_DQ[QS]>=0.0) ?  1.0 : -1.0;

    IsqCmd = speedPICtrl();

    IsQ_Ref = IsQRefVoltPICtrol(IsqCmd);

    if(codeFw2On > 0.5) Is_DQ_ref[QS] = IsqCmd;
    else Is_DQ_ref[QS] = IsQ_Ref;

    IsdCurrentPICtrl();                     // get Is_DQ_ref[DS] in function
    IsD_Ref = IsDRefVoltagePICtrol();

    if ( gfRunTime < 0.25 )  Is_DQ_ref[DS] = Is_D_Rate;
    else if(codeVoltPIOn > 0.5) {
        Is_DQ_ref[DS] = Is_D_Rate + IsD_Ref;
        Is_DQ_ref[DS] = ( Is_DQ_ref[DS] > Is_D_Rate ) ? Is_D_Rate : Is_DQ_ref[DS] ;
     }


    if      ( Is_DQ_ref[DS] >= Is_DQ_max[DS])       Is_DQ_ref[DS] = Is_DQ_max[DS];
    else if ( Is_DQ_ref[DS] < (0.1*inv_Ls*Fs_ref))  Is_DQ_ref[DS] = 0.1*inv_Ls*Fs_ref;

    Vs_DQ_ref_PI[DS] = VsD_PICtrl( Is_DQ_ref[DS] );
    Vs_DQ_ref_PI[QS] = VsQ_PICtrl( Is_DQ_ref[QS] );

    Vs_DQ_comp[DS] += code_VsKi * ( Fs_ref * inv_Tr - Vs_DQ_comp[DS])*Ts;
    Vs_DQ_comp[QS] += code_VsKi * ( wr * Fs_ref - Vs_DQ_comp[QS])*Ts;

    Vs_DQ_ref[DS] = Vs_DQ_ref_PI[DS] - Vs_DQ_comp[DS];
    Vs_DQ_ref[QS] = Vs_DQ_ref_PI[QS] + Vs_DQ_comp[QS];

    Vs_dq_ref[ds] = (CosTheta*Vs_DQ_ref[DS] - SinTheta*Vs_DQ_ref[QS]) + (Vs_dq_ref[ds]-Vs_dq[ds]);
    Vs_dq_ref[qs] = (SinTheta*Vs_DQ_ref[DS] + CosTheta*Vs_DQ_ref[QS]) + (Vs_dq_ref[qs]-Vs_dq[qs]);

    if (gfRunTime<0.05) {
        Delta_wr=0.0; wr=0.0; we=0.0;
    } else {
        Delta_wr_Filter_Pole=1.0*wn_wr;
        Delta_wr += Delta_wr_Filter_Pole*(DeltaTheta*inv_Ts - Delta_wr)*Ts;
        wr += (wr_FilterPole)*( (we_in + Delta_wr - w_sl)  - wr)*Ts;
    }

    Freq_out    = we * inv_PI_2;
    rpm         = rpm_Coeff * wr;
    Te          = Kt * Fs * Is_DQ[QS];
    P_total     = Te * wr;
}
//--- end of file



