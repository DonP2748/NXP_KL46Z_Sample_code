################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/driver/adc.c \
../source/driver/flash.c \
../source/driver/gpio.c \
../source/driver/pit.c \
../source/driver/port.c \
../source/driver/sysclock.c \
../source/driver/uart.c 

C_DEPS += \
./source/driver/adc.d \
./source/driver/flash.d \
./source/driver/gpio.d \
./source/driver/pit.d \
./source/driver/port.d \
./source/driver/sysclock.d \
./source/driver/uart.d 

OBJS += \
./source/driver/adc.o \
./source/driver/flash.o \
./source/driver/gpio.o \
./source/driver/pit.o \
./source/driver/port.o \
./source/driver/sysclock.o \
./source/driver/uart.o 


# Each subdirectory must supply rules for building sources it contributes
source/driver/%.o: ../source/driver/%.c source/driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DCPU_MKL46Z256VLL4_cm0plus -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader/source" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader/CMSIS" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader/drivers" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader/startup" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader/utilities" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader/board/src" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader/board" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader/source/driver" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader/source/peripheral" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_bootloader/source/service" -O0 -fno-common -g -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-driver

clean-source-2f-driver:
	-$(RM) ./source/driver/adc.d ./source/driver/adc.o ./source/driver/flash.d ./source/driver/flash.o ./source/driver/gpio.d ./source/driver/gpio.o ./source/driver/pit.d ./source/driver/pit.o ./source/driver/port.d ./source/driver/port.o ./source/driver/sysclock.d ./source/driver/sysclock.o ./source/driver/uart.d ./source/driver/uart.o

.PHONY: clean-source-2f-driver

