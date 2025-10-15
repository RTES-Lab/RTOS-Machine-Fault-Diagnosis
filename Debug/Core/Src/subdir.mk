################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/crc.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/i2c_lcd.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/crc.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/i2c_lcd.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/crc.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/i2c_lcd.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I"C:/Github/RTOS-Machine-Fault-Diagnosis/Core/Inc" -I"C:/Github/RTOS-Machine-Fault-Diagnosis/Middlewares/ST/AI/Inc" -I"C:/Github/RTOS-Machine-Fault-Diagnosis/X-CUBE-AI/App" -I"C:/Github/RTOS-Machine-Fault-Diagnosis/Middlewares/USB_Host_Library" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include" -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include -I"C:/Github/RTOS-Machine-Fault-Diagnosis/USB_HOST/App" -I"C:/Github/RTOS-Machine-Fault-Diagnosis/USB_HOST/Target" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"C:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc" -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Core/Inc -IC:/Users/ChoiSeongHyeon/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Drivers/CMSIS/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.2/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../X-CUBE-AI/App -I../X-CUBE-AI -I../Middlewares/ST/AI/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/crc.cyclo ./Core/Src/crc.d ./Core/Src/crc.o ./Core/Src/crc.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/i2c_lcd.cyclo ./Core/Src/i2c_lcd.d ./Core/Src/i2c_lcd.o ./Core/Src/i2c_lcd.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

