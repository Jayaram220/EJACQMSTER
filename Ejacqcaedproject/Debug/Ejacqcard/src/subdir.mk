################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Ejacqcard/src/comm.c \
../Ejacqcard/src/display.c \
../Ejacqcard/src/keypad.c \
../Ejacqcard/src/process.c \
../Ejacqcard/src/usb.c 

OBJS += \
./Ejacqcard/src/comm.o \
./Ejacqcard/src/display.o \
./Ejacqcard/src/keypad.o \
./Ejacqcard/src/process.o \
./Ejacqcard/src/usb.o 

C_DEPS += \
./Ejacqcard/src/comm.d \
./Ejacqcard/src/display.d \
./Ejacqcard/src/keypad.d \
./Ejacqcard/src/process.d \
./Ejacqcard/src/usb.d 


# Each subdirectory must supply rules for building sources it contributes
Ejacqcard/src/%.o: ../Ejacqcard/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F0 -DSTM32F030R8Tx -DSTM32F0308_DISCO -DDEBUG -DSTM32F030 -DUSE_STDPERIPH_DRIVER -I"C:/Users/Devsys3/workspace/Ejacqcaedproject/Utilities" -I"C:/Users/Devsys3/workspace/Ejacqcaedproject/Ejacqcard/inc" -I"C:/Users/Devsys3/workspace/Ejacqcaedproject/StdPeriph_Driver/inc" -I"C:/Users/Devsys3/workspace/Ejacqcaedproject/inc" -I"C:/Users/Devsys3/workspace/Ejacqcaedproject/CMSIS/device" -I"C:/Users/Devsys3/workspace/Ejacqcaedproject/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


