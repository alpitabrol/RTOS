################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/cr_startup_lpc175x_6x.c \
../example/src/echo.c \
../example/src/lwip_tcpecho_sa.c \
../example/src/sysinit.c 

OBJS += \
./example/src/cr_startup_lpc175x_6x.o \
./example/src/echo.o \
./example/src/lwip_tcpecho_sa.o \
./example/src/sysinit.o 

C_DEPS += \
./example/src/cr_startup_lpc175x_6x.d \
./example/src/echo.d \
./example/src/lwip_tcpecho_sa.d \
./example/src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/%.o: ../example/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"/home/devil/study_work/RTOS/lambton/2019/fall/ese3025/Real_Time_OS/lpc_chip_175x_6x/inc" -I"/home/devil/study_work/RTOS/lambton/2019/fall/ese3025/Real_Time_OS/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/devil/study_work/RTOS/lambton/2019/fall/ese3025/Real_Time_OS/lwip_tcpecho_sa/example/inc" -I"/home/devil/study_work/RTOS/lambton/2019/fall/ese3025/Real_Time_OS/lwip_tcpecho_sa/lwip/inc" -I"/home/devil/study_work/RTOS/lambton/2019/fall/ese3025/Real_Time_OS/lwip_tcpecho_sa/lwip/inc/ipv4" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


