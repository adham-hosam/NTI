################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../New\ folder/main.c 

OBJS += \
./New\ folder/main.o 

C_DEPS += \
./New\ folder/main.d 


# Each subdirectory must supply rules for building sources it contributes
New\ folder/main.o: ../New\ folder/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"New folder/main.d" -MT"New\ folder/main.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


