################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/peripheral/button.c \
../source/peripheral/debug.c \
../source/peripheral/led.c \
../source/peripheral/sensor.c 

C_DEPS += \
./source/peripheral/button.d \
./source/peripheral/debug.d \
./source/peripheral/led.d \
./source/peripheral/sensor.d 

OBJS += \
./source/peripheral/button.o \
./source/peripheral/debug.o \
./source/peripheral/led.o \
./source/peripheral/sensor.o 


# Each subdirectory must supply rules for building sources it contributes
source/peripheral/%.o: ../source/peripheral/%.c source/peripheral/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DCPU_MKL46Z256VLL4_cm0plus -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_assigment3/source" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_assigment3" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_assigment3/CMSIS" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_assigment3/drivers" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_assigment3/startup" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_assigment3/utilities" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_assigment3/board/src" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_assigment3/board" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_assigment3/source/driver" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_assigment3/source/peripheral" -O0 -fno-common -g -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-peripheral

clean-source-2f-peripheral:
	-$(RM) ./source/peripheral/button.d ./source/peripheral/button.o ./source/peripheral/debug.d ./source/peripheral/debug.o ./source/peripheral/led.d ./source/peripheral/led.o ./source/peripheral/sensor.d ./source/peripheral/sensor.o

.PHONY: clean-source-2f-peripheral

