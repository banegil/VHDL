################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/altavozumbador.c \
../src/altavozumbador_selftest.c \
../src/coprocesador.c \
../src/keypad_selftest.c \
../src/lcd.c \
../src/lcd_controller_selftest.c \
../src/testperiph.c \
../src/xbram_example.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/altavozumbador.o \
./src/altavozumbador_selftest.o \
./src/coprocesador.o \
./src/keypad_selftest.o \
./src/lcd.o \
./src/lcd_controller_selftest.o \
./src/testperiph.o \
./src/xbram_example.o 

C_DEPS += \
./src/altavozumbador.d \
./src/altavozumbador_selftest.d \
./src/coprocesador.d \
./src/keypad_selftest.d \
./src/lcd.d \
./src/lcd_controller_selftest.d \
./src/testperiph.d \
./src/xbram_example.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -Wl,--no-relax -I../../peripheral_tests_bsp_0/microblaze_0/include -mxl-pattern-compare -mcpu=v8.30.a -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


