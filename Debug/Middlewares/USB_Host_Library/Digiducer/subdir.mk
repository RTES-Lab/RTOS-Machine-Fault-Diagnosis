################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/USB_Host_Library/Digiducer/usbh_digiducer.c 

OBJS += \
./Middlewares/USB_Host_Library/Digiducer/usbh_digiducer.o 

C_DEPS += \
./Middlewares/USB_Host_Library/Digiducer/usbh_digiducer.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/USB_Host_Library/Digiducer/%.o Middlewares/USB_Host_Library/Digiducer/%.su Middlewares/USB_Host_Library/Digiducer/%.cyclo: ../Middlewares/USB_Host_Library/Digiducer/%.c Middlewares/USB_Host_Library/Digiducer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"C:/Users/user/Downloads/RS-STM32-401RE-USB/Middlewares/USB_Host_Library/Digiducer" -I"C:/Users/user/Downloads/RS-STM32-401RE-USB/Core/Inc/FreeRTOS" -I"C:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include" -I"C:/Users/user/Downloads/RS-STM32-401RE-USB/Core/Inc/FreeRTOS/port" -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include -IC:/Users/likelike07/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/likelike07/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/likelike07/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/likelike07/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include -I../USB_HOST/App -I../USB_HOST/Target -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-USB_Host_Library-2f-Digiducer

clean-Middlewares-2f-USB_Host_Library-2f-Digiducer:
	-$(RM) ./Middlewares/USB_Host_Library/Digiducer/usbh_digiducer.cyclo ./Middlewares/USB_Host_Library/Digiducer/usbh_digiducer.d ./Middlewares/USB_Host_Library/Digiducer/usbh_digiducer.o ./Middlewares/USB_Host_Library/Digiducer/usbh_digiducer.su

.PHONY: clean-Middlewares-2f-USB_Host_Library-2f-Digiducer

