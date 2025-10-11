################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include X-CUBE-AI/App/subdir.mk
-include USB_HOST/Target/subdir.mk
-include USB_HOST/App/subdir.mk
-include Middlewares/USB_Host_Library/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/FreeRTOS/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := RTOS-Machine-Fault-Diagnosis-test-execution_time
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
RTOS-Machine-Fault-Diagnosis-test-execution_time.elf \

MAP_FILES += \
RTOS-Machine-Fault-Diagnosis-test-execution_time.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
RTOS-Machine-Fault-Diagnosis-test-execution_time.list \


# All Target
all: main-build

# Main-build Target
main-build: RTOS-Machine-Fault-Diagnosis-test-execution_time.elf secondary-outputs

# Tool invocations
RTOS-Machine-Fault-Diagnosis-test-execution_time.elf RTOS-Machine-Fault-Diagnosis-test-execution_time.map: $(OBJS) $(USER_OBJS) C:\Users\ChoiSeongHyeon\Desktop\SR_CODE_Copy\RTOS-Machine-Fault-Diagnosis-test-execution_time\RTOS-Machine-Fault-Diagnosis-test-execution_time\STM32F401RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "RTOS-Machine-Fault-Diagnosis-test-execution_time.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\ChoiSeongHyeon\Desktop\SR_CODE_Copy\RTOS-Machine-Fault-Diagnosis-test-execution_time\RTOS-Machine-Fault-Diagnosis-test-execution_time\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="RTOS-Machine-Fault-Diagnosis-test-execution_time.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

RTOS-Machine-Fault-Diagnosis-test-execution_time.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "RTOS-Machine-Fault-Diagnosis-test-execution_time.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) RTOS-Machine-Fault-Diagnosis-test-execution_time.elf RTOS-Machine-Fault-Diagnosis-test-execution_time.list RTOS-Machine-Fault-Diagnosis-test-execution_time.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
