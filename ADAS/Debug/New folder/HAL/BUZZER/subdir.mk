################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../New\ folder/HAL/BUZZER/BUZZER_program.c 

OBJS += \
./New\ folder/HAL/BUZZER/BUZZER_program.o 

C_DEPS += \
./New\ folder/HAL/BUZZER/BUZZER_program.d 


# Each subdirectory must supply rules for building sources it contributes
New\ folder/HAL/BUZZER/BUZZER_program.o: ../New\ folder/HAL/BUZZER/BUZZER_program.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"New folder/HAL/BUZZER/BUZZER_program.d" -MT"New\ folder/HAL/BUZZER/BUZZER_program.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


