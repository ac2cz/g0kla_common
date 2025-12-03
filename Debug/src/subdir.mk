################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/agw_tnc.c \
../src/ax25_tools.c \
../src/crc.c \
../src/pacsat_log.c \
../src/str_util.c \
../src/uplink_command.c 

C_DEPS += \
./src/agw_tnc.d \
./src/ax25_tools.d \
./src/crc.d \
./src/pacsat_log.d \
./src/str_util.d \
./src/uplink_command.d 

OBJS += \
./src/agw_tnc.o \
./src/ax25_tools.o \
./src/crc.o \
./src/pacsat_log.o \
./src/str_util.o \
./src/uplink_command.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../inc -O0 -fPIC -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/agw_tnc.d ./src/agw_tnc.o ./src/ax25_tools.d ./src/ax25_tools.o ./src/crc.d ./src/crc.o ./src/pacsat_log.d ./src/pacsat_log.o ./src/str_util.d ./src/str_util.o ./src/uplink_command.d ./src/uplink_command.o

.PHONY: clean-src

