################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_HOST/Target/usbh_conf.c \
../USB_HOST/Target/usbh_platform.c 

OBJS += \
./USB_HOST/Target/usbh_conf.o \
./USB_HOST/Target/usbh_platform.o 

C_DEPS += \
./USB_HOST/Target/usbh_conf.d \
./USB_HOST/Target/usbh_platform.d 


# Each subdirectory must supply rules for building sources it contributes
USB_HOST/Target/%.o USB_HOST/Target/%.su USB_HOST/Target/%.cyclo: ../USB_HOST/Target/%.c USB_HOST/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I"C:/Users/ChoiSeongHyeon/Desktop/SR_CODE_Copy/RTOS-Machine-Fault-Diagnosis-feature-0921/RTOS-Machine-Fault-Diagnosis-feature-16kHz_debugging/Core/Inc" -I"C:/Users/ChoiSeongHyeon/Desktop/SR_CODE_Copy/RTOS-Machine-Fault-Diagnosis-feature-0921/RTOS-Machine-Fault-Diagnosis-feature-16kHz_debugging/Middlewares/USB_Host_Library" -I"C:/Users/ChoiSeongHyeon/Desktop/SR_CODE_Copy/RTOS-Machine-Fault-Diagnosis-feature-0921/RTOS-Machine-Fault-Diagnosis-feature-16kHz_debugging/Core/Inc/FreeRTOS" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include" -I"C:/Users/ChoiSeongHyeon/Desktop/SR_CODE_Copy/RTOS-Machine-Fault-Diagnosis-feature-0921/RTOS-Machine-Fault-Diagnosis-feature-16kHz_debugging/Core/Inc/FreeRTOS/port" -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include -I"C:/Users/ChoiSeongHyeon/Desktop/SR_CODE_Copy/RTOS-Machine-Fault-Diagnosis-feature-0921/RTOS-Machine-Fault-Diagnosis-feature-16kHz_debugging/USB_HOST/App" -I"C:/Users/ChoiSeongHyeon/Desktop/SR_CODE_Copy/RTOS-Machine-Fault-Diagnosis-feature-0921/RTOS-Machine-Fault-Diagnosis-feature-16kHz_debugging/USB_HOST/Target" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc" -I../Core/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include -I../USB_HOST/App -I../USB_HOST/Target -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Core/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Core/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-USB_HOST-2f-Target

clean-USB_HOST-2f-Target:
	-$(RM) ./USB_HOST/Target/usbh_conf.cyclo ./USB_HOST/Target/usbh_conf.d ./USB_HOST/Target/usbh_conf.o ./USB_HOST/Target/usbh_conf.su ./USB_HOST/Target/usbh_platform.cyclo ./USB_HOST/Target/usbh_platform.d ./USB_HOST/Target/usbh_platform.o ./USB_HOST/Target/usbh_platform.su

.PHONY: clean-USB_HOST-2f-Target

