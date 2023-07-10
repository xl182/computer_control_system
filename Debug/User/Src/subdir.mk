################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Src/at24c02.c \
../User/Src/callback.c \
../User/Src/font.c \
../User/Src/func.c \
../User/Src/gui.c \
../User/Src/lcd.c \
../User/Src/pid.c \
../User/Src/queue.c \
../User/Src/user.c 

OBJS += \
./User/Src/at24c02.o \
./User/Src/callback.o \
./User/Src/font.o \
./User/Src/func.o \
./User/Src/gui.o \
./User/Src/lcd.o \
./User/Src/pid.o \
./User/Src/queue.o \
./User/Src/user.o 

C_DEPS += \
./User/Src/at24c02.d \
./User/Src/callback.d \
./User/Src/font.d \
./User/Src/func.d \
./User/Src/gui.d \
./User/Src/lcd.d \
./User/Src/pid.d \
./User/Src/queue.d \
./User/Src/user.d 


# Each subdirectory must supply rules for building sources it contributes
User/Src/%.o User/Src/%.su User/Src/%.cyclo: ../User/Src/%.c User/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DARM_MATH_CM3 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I../User/Inc -I../LVGL -I../LVGL/porting -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-Src

clean-User-2f-Src:
	-$(RM) ./User/Src/at24c02.cyclo ./User/Src/at24c02.d ./User/Src/at24c02.o ./User/Src/at24c02.su ./User/Src/callback.cyclo ./User/Src/callback.d ./User/Src/callback.o ./User/Src/callback.su ./User/Src/font.cyclo ./User/Src/font.d ./User/Src/font.o ./User/Src/font.su ./User/Src/func.cyclo ./User/Src/func.d ./User/Src/func.o ./User/Src/func.su ./User/Src/gui.cyclo ./User/Src/gui.d ./User/Src/gui.o ./User/Src/gui.su ./User/Src/lcd.cyclo ./User/Src/lcd.d ./User/Src/lcd.o ./User/Src/lcd.su ./User/Src/pid.cyclo ./User/Src/pid.d ./User/Src/pid.o ./User/Src/pid.su ./User/Src/queue.cyclo ./User/Src/queue.d ./User/Src/queue.o ./User/Src/queue.su ./User/Src/user.cyclo ./User/Src/user.d ./User/Src/user.o ./User/Src/user.su

.PHONY: clean-User-2f-Src

