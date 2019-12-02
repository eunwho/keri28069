/* project :  dcPower
File Name:	fault.h
*/
#ifndef		_ERROR_CODE_DEFINITION_
#define		_ERROR_CODE_DEFINITION_

#define ERR_IGBT_UH							821
#define ERR_IGBT_UL							822
#define ERR_IGBT_VH							823
#define ERR_IGBT_VL							824
#define ERR_PWM_IGBT						825

#define ERR_OC_I_PRI_ADC_P					831
#define ERR_OC_I_PRI_ADC_N					832
#define ERR_OC_I_OUT_ADC_P					833
#define ERR_OC_I_OUT_ADC_N					834
#define ERR_OV_VDC      					842
#define ERR_UV_VDC      					843

#define ERR_EXT_TRIP                        851
#define TRIP_EXT_A                          852
#define ERR_PWM_CNT                         853

#define ERR_INVALID_CTRL_MODE               898
#define ERR_UNKNOWN_ERR						899

struct TRIP_INFO_DEFINE {
	int		CODE;				// 1
	double	CURRENT;			// 5
	double	VDC;				// 6
	double	VOUT;				// 7
	double	DATA;				// 4
	char 	MSG[21];			// 2
};
typedef struct TRIP_INFO_DEFINE TRIP_INFO;

struct PROTECT_BITS {      // bits description
	Uint16  OVER_VOLT	:1;	
	Uint16  UNVER_VOLT	:1; 
	Uint16  OVER_I  	:1; 
	Uint16  LOW_I		:1; 
	Uint16  OVER_I_ADC	:1; 
	Uint16  CONV_ADC	:1;
	Uint16  OVER_LOAD	:1; 
	Uint16  LOW_LOAD	:1;
	Uint16  OVER_SPEED	:1; 
	Uint16  LOW_SPEED	:1; 
	Uint16  IGBT_FAULT	:1;
	Uint16  IGBT_FAULT2	:1;
	Uint16  EX_TRIP		:1; 
	Uint16	OVER_HEAT	:1;
};
union PROTECT_FLAG{
   Uint16               all;
   struct PROTECT_BITS  bit;
};  
#endif


