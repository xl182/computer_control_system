################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Src/callback.c \
../User/Src/func.c \
../User/Src/lcd.c \
../User/Src/queue.c \
../User/Src/user.c 

OBJS += \
./User/Src/callback.o \
./User/Src/func.o \
./User/Src/lcd.o \
./User/Src/queue.o \
./User/Src/user.o 

C_DEPS += \
./User/Src/callback.d \
./User/Src/func.d \
./User/Src/lcd.d \
./User/Src/queue.d \
./User/Src/user.d 


# Each subdirectory must supply rules for building sources it contributes
User/Src/%.o User/Src/%.su User/Src/%.cyclo: ../User/Src/%.c User/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DARM_MATH_CM3 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I"../User/Inc" -I../DSP_LIB/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-Src

clean-User-2f-Src:
	-$(RM) ./User/Src/callback.cyclo ./User/Src/callback.d ./User/Src/callback.o ./User/Src/callback.su ./User/Src/func.cyclo ./User/Src/func.d ./User/Src/func.o ./User/Src/func.su ./User/Src/lcd.cyclo ./User/Src/lcd.d ./User/Src/lcd.o ./User/Src/lcd.su ./User/Src/queue.cyclo ./User/Src/queue.d ./User/Src/queue.o ./User/Src/queue.su ./User/Src/user.cyclo ./User/Src/user.d ./User/Src/user.o ./User/Src/user.su

.PHONY: clean-User-2f-Src

