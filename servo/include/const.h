// project name : inverter for Electric Vehicle by soonkil jung 2019.12.20
#ifndef		__COMMON_CONSTANTS_
#define		__COMMON_CONSTANTS_

// #define MIN_REF       0.05    // minimum run reference
//'math
#define PI_2_INV	 0.15915494309		//' 1/(2*pi)
#define	PI_120		 376.991118430		//' 2*pi*60

#define ROOT2	   	 1.41421356237		//' sqrt(2)
#define INV_ROOT2    0.70710678118		//' 1/sqrt(2)

#define ROOT3        1.73205080757		//' sqrt(3)
#define INV_ROOT3    0.57735026918		//' 1/sqrt(3)
#define	ROOT3_2		 1.224744871		// sqrt(3/2)
#define	ROOT2_3		 0.8164965809		// sqrt(2/3)

#define DIV1_3       0.33333333333
#define DIV2_3       0.66666666667
#define DIV1_380	 0.002631578947
#define DIV1_220     0.004545454545

#define		PI_2		6.283185			// 2.0*PI 
#define		PI			3.141593			// PI 
#define		PI_DIV2		1.570796			// PI/2.0
#define		PI_DIV3		1.047198			// PI/3.0
#define		PI_DIV4		0.785398			// PI/4.0
#define		PI_DIV6		0.523599			// PI/6.0

#define     PI_2        6.283185            // 2.0*PI
#define     PI          3.141593            // PI
#define     PI_1_2      1.570796            // PI/2.0
#define     PI_1_3      1.047198            // PI/3.0
#define     PI_1_4      0.785398            // PI/4.0
#define     PI_1_6      0.523599            // PI/6.0
#define     PI_1_9      0.349066            // PI/9.0
#define     PI_2_3      2.094395            // 2.0*PI/3.0
#define     PI_3_2      4.712389            // 3.0*PI/2.0
#define     PI_4_3      4.188790            // 4.0*PI/3.0
#define     PI_5_3      5.235988            // 5.0*PI/3.0

#define     inv_PI_2    0.159155
#define     inv_PI      0.318310
#define     inv_PI_1_2  (2.0*inv_PI)
#define     inv_PI_1_3  (3.0*inv_PI)
#define     inv_PI_1_4  (4.0*inv_PI)
#define     inv_PI_1_6  (6.0*inv_PI)

#define 	INV_SQRT2	0.7071067812

// Array Index
#define		ds					0
#define		qs					1

#define		DS					0
#define		QS					1

#define		as					0
#define		bs					1
#define		cs					2

#define		u					0
#define		v					1
#define		w					2

#define		R					0
#define		S					1
#define		T					2	

#define		A					0
#define		B					1
#define		C					2

#define F_OSC					20000000

//
#define over_volt_set           380.0         // check
//#define UNDER_VOLT_LEVEL        200.0         // check
// #define OVER_V_LEVEL        420.0
#define UNDER_VOLT_LEVEL        200.0         // check
// #define OVER_V_LEVEL        720.0
#define OVER_V_LEVEL        380.0


// Control Constant
#define AT_SUCCESS	10

//--- define inner parameter
#define AT_Ls_DMB_OpenTime      0.5

#endif

