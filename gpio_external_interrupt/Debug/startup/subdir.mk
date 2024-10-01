################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mkl46z4.c 

C_DEPS += \
./startup/startup_mkl46z4.d 

OBJS += \
./startup/startup_mkl46z4.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_led/source" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_led" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_led/CMSIS" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_led/drivers" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_led/startup" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_led/utilities" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_led/board/src" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_led/board" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_led/source/driver" -I"/home/donp/NXP/MCUXpresso_11.9.1_2170/workspace/frdmkl46z_phucth_led/source/peripheral" -O0 -fno-common -g -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_mkl46z4.d ./startup/startup_mkl46z4.o

.PHONY: clean-startup

