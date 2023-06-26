//
// Created by ALIEN on 2023/6/24.
//
#include "callback.h"

int goal_temperature = 300;
float duty;

int encoder_count = 0;
float pid_error = 0;
const double k = 0.1;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (hadc->Instance == ADC1) {
        HAL_ADC_Stop_DMA(&hadc1);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM6) {
        static int led_count = 0;
        if (led_count >= 10) {
            HAL_GPIO_TogglePin(led_GPIO_Port, led_Pin);
            led_count = 0;
        }
        led_count += 1;
        if (led_count % 4 == 0) {
            int x = 10, y = 10, size = 16, y_increment = 20;
            sprintf(string_display, "pid_error: %04f", pid_error);
            LCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
            sprintf(string_display, "t:%04f", temperature);
            LCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
            sprintf(string_display, "goal:%04d", goal_temperature);
            LCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
            sprintf(string_display, "d:%04f", duty);
            LCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
            sprintf(string_display, "heat_level:%04d", heat_level);
            LCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
        }
        sprintf(string_send, "%f, %f\n", temperature, (float) goal_temperature);
        send_bluetooth(string_send);
    }

    if (htim->Instance == TIM7) {
        // refresh_adc();
        pid_error = (float) goal_temperature - temperature;
        duty = arm_pid_f32(&pid, pid_error);
        // set_heat_level((uint16_t) duty);
        temperature += (float) 0.01 * duty;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

    if (GPIO_Pin == A_Pin) {
        if (HAL_GPIO_ReadPin(B_GPIO_Port, B_Pin) == RESET && encoder_count < 1000) {
            encoder_count += 1;
        }
    }
    if (GPIO_Pin == B_Pin) {
        if (HAL_GPIO_ReadPin(A_GPIO_Port, A_Pin) == RESET && encoder_count > 0) {
            encoder_count -= 1;
        }
    }
    if (GPIO_Pin == SW_Pin) {
        goal_temperature = (uint16_t) ((float) encoder_count * k);
    }
    if (GPIO_Pin == key_Pin) {

    }
}
