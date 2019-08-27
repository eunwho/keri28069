################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/eunwho/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
-lrts2800_fpu32_fast_supplement.lib \
-lrts2800_fpu32.lib \
"./F2806x_Adc.obj" \
"./F2806x_CSMPasswords.obj" \
"./F2806x_CodeStartBranch.obj" \
"./F2806x_CpuTimers.obj" \
"./F2806x_DefaultIsr.obj" \
"./F2806x_GlobalVariableDefs.obj" \
"./F2806x_PieCtrl.obj" \
"./F2806x_PieVect.obj" \
"./F2806x_SysCtrl.obj" \
"./F2806x_usDelay.obj" \
"./I2C_eeprom.obj" \
"./MonitorProc.obj" \
"./ParameterSet.obj" \
"./RefFunc.obj" \
"./Set_Par.obj" \
"./analog.obj" \
"./code_proc.obj" \
"./common_module.obj" \
"./digital_inout.obj" \
"./f28069GpioSetup.obj" \
"./low_pass_filter.obj" \
"./main.obj" \
"./scia.obj" \
"./scopePoint.obj" \
"./serial_com.obj" \
"./svm.obj" \
"./switching_irq.obj" \
"./trip_proc.obj" \
"./udd_timer_irq.obj" \
"./vf_contol.obj" \
"./windPower.obj" \
"../F28069_eunwho.cmd" \
"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/headers/cmd/F2806x_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-lIQmath_fpu32.lib \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
servo.out \

EXE_OUTPUTS__QUOTED += \
"servo.out" \

BIN_OUTPUTS += \
servo.hex \

BIN_OUTPUTS__QUOTED += \
"servo.hex" \


# All Target
all: servo.out

# Tool invocations
servo.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"/home/eunwho/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --opt_for_speed=2 --advice:performance=all --define="_DEBUG" --define="LARGE_MODEL" -g --diag_suppress=10063 --diag_warning=225 --issue_remarks --verbose_diagnostics --quiet --abi=coffabi -z -m"servo.map" --heap_size=0x400 --stack_size=0x800 --warn_sections -i"/home/eunwho/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/lib" -i"/home/eunwho/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" -i"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/libraries/math/IQmath/c28/lib" -i"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/libraries/math/FPUfastRTS/c28/lib" -i"/home/eunwho/ti/C2000Ware_2_00_00_02_Software/device_support/f2806x/examples/c28/adc_soc" --priority --reread_libs --issue_remarks --verbose_diagnostics --xml_link_info="Example_2806xEPwmUpDownAQ_linkInfo.xml" --entry_point=code_start --rom_model -o "servo.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

servo.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"/home/eunwho/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/hex2000"  -o "servo.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "F2806x_Adc.obj" "F2806x_CSMPasswords.obj" "F2806x_CodeStartBranch.obj" "F2806x_CpuTimers.obj" "F2806x_DefaultIsr.obj" "F2806x_GlobalVariableDefs.obj" "F2806x_PieCtrl.obj" "F2806x_PieVect.obj" "F2806x_SysCtrl.obj" "F2806x_usDelay.obj" "I2C_eeprom.obj" "MonitorProc.obj" "ParameterSet.obj" "RefFunc.obj" "Set_Par.obj" "analog.obj" "code_proc.obj" "common_module.obj" "digital_inout.obj" "f28069GpioSetup.obj" "low_pass_filter.obj" "main.obj" "scia.obj" "scopePoint.obj" "serial_com.obj" "svm.obj" "switching_irq.obj" "trip_proc.obj" "udd_timer_irq.obj" "vf_contol.obj" "windPower.obj" 
	-$(RM) "F2806x_Adc.d" "F2806x_CpuTimers.d" "F2806x_DefaultIsr.d" "F2806x_GlobalVariableDefs.d" "F2806x_PieCtrl.d" "F2806x_PieVect.d" "F2806x_SysCtrl.d" "I2C_eeprom.d" "MonitorProc.d" "ParameterSet.d" "RefFunc.d" "Set_Par.d" "analog.d" "code_proc.d" "common_module.d" "digital_inout.d" "f28069GpioSetup.d" "low_pass_filter.d" "main.d" "scia.d" "scopePoint.d" "serial_com.d" "svm.d" "switching_irq.d" "trip_proc.d" "udd_timer_irq.d" "vf_contol.d" "windPower.d" 
	-$(RM) "F2806x_CSMPasswords.d" "F2806x_CodeStartBranch.d" "F2806x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

