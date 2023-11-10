################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Aula_2.c \
../src/PC_Comm.c \
../src/USART.c \
../src/aula_1.c \
../src/lcd.c \
../src/main.c \
../src/stm32f10x_it.c \
../src/syscalls.c 

OBJS += \
./src/Aula_2.o \
./src/PC_Comm.o \
./src/USART.o \
./src/aula_1.o \
./src/lcd.o \
./src/main.o \
./src/stm32f10x_it.o \
./src/syscalls.o 

C_DEPS += \
./src/Aula_2.d \
./src/PC_Comm.d \
./src/USART.d \
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
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -I"/home/bruno-laptop/Projects/STM/SandBox/Stm32_3SO_Int/inc" -I"/home/bruno-laptop/Projects/STM/SandBox/Stm32_3SO_Int/StdPeriph_Driver/inc" -I"/home/bruno-laptop/Projects/STM/SandBox/Stm32_3SO_Int/CMSIS/core" -I"/home/bruno-laptop/Projects/STM/SandBox/Stm32_3SO_Int/CMSIS/device" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


