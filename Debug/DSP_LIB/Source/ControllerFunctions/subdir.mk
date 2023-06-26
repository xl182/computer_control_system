################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DSP_LIB/Source/ControllerFunctions/arm_pid_init_f32.c \
../DSP_LIB/Source/ControllerFunctions/arm_pid_init_q15.c \
../DSP_LIB/Source/ControllerFunctions/arm_pid_init_q31.c \
../DSP_LIB/Source/ControllerFunctions/arm_pid_reset_f32.c \
../DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q15.c \
../DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q31.c \
../DSP_LIB/Source/ControllerFunctions/arm_sin_cos_f32.c \
../DSP_LIB/Source/ControllerFunctions/arm_sin_cos_q31.c 

OBJS += \
./DSP_LIB/Source/ControllerFunctions/arm_pid_init_f32.o \
./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q15.o \
./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q31.o \
./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_f32.o \
./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q15.o \
./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q31.o \
./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_f32.o \
./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_q31.o 

C_DEPS += \
./DSP_LIB/Source/ControllerFunctions/arm_pid_init_f32.d \
./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q15.d \
./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q31.d \
./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_f32.d \
./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q15.d \
./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q31.d \
./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_f32.d \
./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_q31.d 


# Each subdirectory must supply rules for building sources it contributes
DSP_LIB/Source/ControllerFunctions/%.o DSP_LIB/Source/ControllerFunctions/%.su DSP_LIB/Source/ControllerFunctions/%.cyclo: ../DSP_LIB/Source/ControllerFunctions/%.c DSP_LIB/Source/ControllerFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DARM_MATH_CM3 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I"../User/Inc" -I../DSP_LIB/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-DSP_LIB-2f-Source-2f-ControllerFunctions

clean-DSP_LIB-2f-Source-2f-ControllerFunctions:
	-$(RM) ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_f32.cyclo ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_f32.d ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_f32.o ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_f32.su ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q15.cyclo ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q15.d ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q15.o ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q15.su ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q31.cyclo ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q31.d ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q31.o ./DSP_LIB/Source/ControllerFunctions/arm_pid_init_q31.su ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_f32.cyclo ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_f32.d ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_f32.o ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_f32.su ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q15.cyclo ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q15.d ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q15.o ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q15.su ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q31.cyclo ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q31.d ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q31.o ./DSP_LIB/Source/ControllerFunctions/arm_pid_reset_q31.su ./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_f32.cyclo ./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_f32.d ./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_f32.o ./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_f32.su ./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_q31.cyclo ./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_q31.d ./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_q31.o ./DSP_LIB/Source/ControllerFunctions/arm_sin_cos_q31.su

.PHONY: clean-DSP_LIB-2f-Source-2f-ControllerFunctions

