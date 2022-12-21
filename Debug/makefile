################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Ard_Tmr_Tst.lss \

FLASH_IMAGE += \
Ard_Tmr_Tst.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Ard_Tmr_Tst.elf secondary-outputs

# Tool invocations
Ard_Tmr_Tst.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Ard_Tmr_Tst.map -mmcu=atmega32 -o "Ard_Tmr_Tst.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Ard_Tmr_Tst.lss: Ard_Tmr_Tst.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Ard_Tmr_Tst.elf  >"Ard_Tmr_Tst.lss"
	@echo 'Finished building: $@'
	@echo ' '

Ard_Tmr_Tst.hex: Ard_Tmr_Tst.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Ard_Tmr_Tst.elf  "Ard_Tmr_Tst.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Ard_Tmr_Tst.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Ard_Tmr_Tst.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Ard_Tmr_Tst.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
