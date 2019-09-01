################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../F28069_eunwho.cmd \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/headers/cmd/F2806x_Headers_nonBIOS.cmd 

ASM_SRCS += \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_CSMPasswords.asm \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_CodeStartBranch.asm \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_usDelay.asm 

C_SRCS += \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_Adc.c \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_CpuTimers.c \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_DefaultIsr.c \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/headers/source/F2806x_GlobalVariableDefs.c \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_PieCtrl.c \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_PieVect.c \
/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_SysCtrl.c \
../I2C_eeprom.c \
../MonitorProc.c \
../ParameterSet.c \
../RefFunc.c \
../Set_Par.c \
../analog.c \
../code_proc.c \
../common_module.c \
../digital_inout.c \
../eQep.c \
../f28069GpioSetup.c \
../low_pass_filter.c \
../main.c \
../pmsmCtrl.c \
../scia.c \
../scopePoint.c \
../serial_com.c \
../svm.c \
../switching_irq.c \
../trip_proc.c \
../udd_timer_irq.c \
../vf_contol.c 

C_DEPS += \
./F2806x_Adc.d \
./F2806x_CpuTimers.d \
./F2806x_DefaultIsr.d \
./F2806x_GlobalVariableDefs.d \
./F2806x_PieCtrl.d \
./F2806x_PieVect.d \
./F2806x_SysCtrl.d \
./I2C_eeprom.d \
./MonitorProc.d \
./ParameterSet.d \
./RefFunc.d \
./Set_Par.d \
./analog.d \
./code_proc.d \
./common_module.d \
./digital_inout.d \
./eQep.d \
./f28069GpioSetup.d \
./low_pass_filter.d \
./main.d \
./pmsmCtrl.d \
./scia.d \
./scopePoint.d \
./serial_com.d \
./svm.d \
./switching_irq.d \
./trip_proc.d \
./udd_timer_irq.d \
./vf_contol.d 

OBJS += \
./F2806x_Adc.obj \
./F2806x_CSMPasswords.obj \
./F2806x_CodeStartBranch.obj \
./F2806x_CpuTimers.obj \
./F2806x_DefaultIsr.obj \
./F2806x_GlobalVariableDefs.obj \
./F2806x_PieCtrl.obj \
./F2806x_PieVect.obj \
./F2806x_SysCtrl.obj \
./F2806x_usDelay.obj \
./I2C_eeprom.obj \
./MonitorProc.obj \
./ParameterSet.obj \
./RefFunc.obj \
./Set_Par.obj \
./analog.obj \
./code_proc.obj \
./common_module.obj \
./digital_inout.obj \
./eQep.obj \
./f28069GpioSetup.obj \
./low_pass_filter.obj \
./main.obj \
./pmsmCtrl.obj \
./scia.obj \
./scopePoint.obj \
./serial_com.obj \
./svm.obj \
./switching_irq.obj \
./trip_proc.obj \
./udd_timer_irq.obj \
./vf_contol.obj 

ASM_DEPS += \
./F2806x_CSMPasswords.d \
./F2806x_CodeStartBranch.d \
./F2806x_usDelay.d 

OBJS__QUOTED += \
"F2806x_Adc.obj" \
"F2806x_CSMPasswords.obj" \
"F2806x_CodeStartBranch.obj" \
"F2806x_CpuTimers.obj" \
"F2806x_DefaultIsr.obj" \
"F2806x_GlobalVariableDefs.obj" \
"F2806x_PieCtrl.obj" \
"F2806x_PieVect.obj" \
"F2806x_SysCtrl.obj" \
"F2806x_usDelay.obj" \
"I2C_eeprom.obj" \
"MonitorProc.obj" \
"ParameterSet.obj" \
"RefFunc.obj" \
"Set_Par.obj" \
"analog.obj" \
"code_proc.obj" \
"common_module.obj" \
"digital_inout.obj" \
"eQep.obj" \
"f28069GpioSetup.obj" \
"low_pass_filter.obj" \
"main.obj" \
"pmsmCtrl.obj" \
"scia.obj" \
"scopePoint.obj" \
"serial_com.obj" \
"svm.obj" \
"switching_irq.obj" \
"trip_proc.obj" \
"udd_timer_irq.obj" \
"vf_contol.obj" 

C_DEPS__QUOTED += \
"F2806x_Adc.d" \
"F2806x_CpuTimers.d" \
"F2806x_DefaultIsr.d" \
"F2806x_GlobalVariableDefs.d" \
"F2806x_PieCtrl.d" \
"F2806x_PieVect.d" \
"F2806x_SysCtrl.d" \
"I2C_eeprom.d" \
"MonitorProc.d" \
"ParameterSet.d" \
"RefFunc.d" \
"Set_Par.d" \
"analog.d" \
"code_proc.d" \
"common_module.d" \
"digital_inout.d" \
"eQep.d" \
"f28069GpioSetup.d" \
"low_pass_filter.d" \
"main.d" \
"pmsmCtrl.d" \
"scia.d" \
"scopePoint.d" \
"serial_com.d" \
"svm.d" \
"switching_irq.d" \
"trip_proc.d" \
"udd_timer_irq.d" \
"vf_contol.d" 

ASM_DEPS__QUOTED += \
"F2806x_CSMPasswords.d" \
"F2806x_CodeStartBranch.d" \
"F2806x_usDelay.d" 

C_SRCS__QUOTED += \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_Adc.c" \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_CpuTimers.c" \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_DefaultIsr.c" \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/headers/source/F2806x_GlobalVariableDefs.c" \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_PieCtrl.c" \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_PieVect.c" \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_SysCtrl.c" \
"../I2C_eeprom.c" \
"../MonitorProc.c" \
"../ParameterSet.c" \
"../RefFunc.c" \
"../Set_Par.c" \
"../analog.c" \
"../code_proc.c" \
"../common_module.c" \
"../digital_inout.c" \
"../eQep.c" \
"../f28069GpioSetup.c" \
"../low_pass_filter.c" \
"../main.c" \
"../pmsmCtrl.c" \
"../scia.c" \
"../scopePoint.c" \
"../serial_com.c" \
"../svm.c" \
"../switching_irq.c" \
"../trip_proc.c" \
"../udd_timer_irq.c" \
"../vf_contol.c" 

ASM_SRCS__QUOTED += \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_CSMPasswords.asm" \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_CodeStartBranch.asm" \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/common/source/F2806x_usDelay.asm" 


