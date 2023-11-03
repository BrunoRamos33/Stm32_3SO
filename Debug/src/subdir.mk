################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Aula_2.c \
../src/aula_1.c \
../src/lcd.c \
../src/main.c \
../src/stm32f10x_it.c \
../src/syscalls.c 

OBJS += \
./src/Aula_2.o \
./src/aula_1.o \
./src/lcd.o \
./src/main.o \
./src/stm32f10x_it.o \
./src/syscalls.o 

C_DEPS += \
./src/Aula_2.d \
./src/aula_1.d \
./src/lcd.d \
./src/main.d \
./src/stm32f10x_it.d \
./src/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -I"/home/bruno-laptop/Projects/STM/WS/3S0/3SO/inc" -I"/home/bruno-laptop/Projects/STM/WS/3S0/3SO/StdPeriph_Driver/inc" -I"/home/bruno-laptop/Projects/STM/WS/3S0/3SO/CMSIS/core" -I"/home/bruno-laptop/Projects/STM/WS/3S0/3SO/CMSIS/device" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


