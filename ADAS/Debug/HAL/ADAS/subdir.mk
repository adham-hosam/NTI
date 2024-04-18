################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/ADAS/ADAS_program.c 

OBJS += \
./HAL/ADAS/ADAS_program.o 

C_DEPS += \
./HAL/ADAS/ADAS_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/ADAS/%.o: ../HAL/ADAS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\MCAL\ADC" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL\ADAS" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\MCAL" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\MCAL" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\MCAL\DIO" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\MCAL\EEPROM" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\MCAL\EXTI" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\MCAL\TIMER" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL\BAS" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL\BUZZER" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL\CCS" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL\KeyPad" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL\LCD" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL\LED" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL\PushButton" -I"E:\Studing\Assignments\Eclipse_WorkSpace\ADAS\HAL\RELAY" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


