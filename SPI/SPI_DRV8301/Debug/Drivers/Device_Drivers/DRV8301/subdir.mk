################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Device_Drivers/DRV8301/DRV8301.c 

OBJS += \
./Drivers/Device_Drivers/DRV8301/DRV8301.o 

C_DEPS += \
./Drivers/Device_Drivers/DRV8301/DRV8301.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Device_Drivers/DRV8301/DRV8301.o: ../Drivers/Device_Drivers/DRV8301/DRV8301.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103x6 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Device_Drivers/DRV8301/DRV8301.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

