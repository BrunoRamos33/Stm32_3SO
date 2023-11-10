################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"/home/bruno-laptop/Projects/STM/SandBox/Stm32_3SO_Int/inc" -I"/home/bruno-laptop/Projects/STM/SandBox/Stm32_3SO_Int/StdPeriph_Driver/inc" -I"/home/bruno-laptop/Projects/STM/SandBox/Stm32_3SO_Int/CMSIS/core" -I"/home/bruno-laptop/Projects/STM/SandBox/Stm32_3SO_Int/CMSIS/device" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


