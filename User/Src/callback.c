//
// Created by ALIEN on 2023/6/24.
//
#include "callback.h"

int goal_temperature = 300;
float duty;

int encoder_count = 300;
float pid_error = 0;
const double k = 0.1;


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (hadc->Instance == ADC1) {
        HAL_ADC_Stop_DMA(&hadc1);
    }
}

void display()
{
    int x = 10, y = 10, size = 16, y_increment = 20;
    sprintf(string_display, "pid_error: %04f", pid_error);
    mLCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
    sprintf(string_display, "t:%04f", temperature);
    LCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
    sprintf(string_display, "goal:%04d", goal_temperature);
    LCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
    sprintf(string_display, "enc:%04d", encoder_count);
    LCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
    sprintf(string_display, "heat_level:%04d", heat_level);
    LCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
    sprintf(string_display, "data:%6s", string_recv);
    LCD_String(x, y, string_display, size, WHITE, BLACK), y += y_increment;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM6) {
        static int led_count = 0;
        if (led_count >= 5) {
            HAL_GPIO_TogglePin(led_GPIO_Port, led_Pin);
            led_count = 0;
        }
        led_count += 1;
    }

    if (htim->Instance == TIM7) {
//         refresh_adc();
        pid_error = (float) goal_temperature - temperature;
        if ((goal_temperature - (uint16_t) temperature) < 20) {
            duty = arm_pid_f32(&pid, pid_error);
            // set_heat_level((uint16_t) duty);
            if (duty < -5) {
                duty = (float) (-5.0 * (temperature) / 300.0);
            }
            if (duty > 10) {
                duty = (float) (10.0 * (500 - temperature) / 300.0);
            }
            temperature += (float) 0.5 * duty;
        } else {
            temperature += 10;
        }

        sprintf(string_send, "%f, %f\n", temperature, (float) goal_temperature);
        send_bluetooth(string_send);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

    if (GPIO_Pin == B_Pin) {
        if (HAL_GPIO_ReadPin(A_GPIO_Port, A_Pin) == RESET && encoder_count < 1000) {
            encoder_count += 1;
        } else {
            encoder_count -= 1;
        }
    }

    if (GPIO_Pin == SW_Pin) {
        goal_temperature = encoder_count;
    }
    if (GPIO_Pin == key_Pin) {

    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART3) {
        static int string_recv_index = 0;
        if (string_recv_index == 0) {
            for (int i = 0; i < 100; i++) {
                string_recv[i] = 0;
            }
        }
        if (tmp_data == '\n') {
            string_recv_index = 0;
            if (abs(atoi(string_recv) - 0) > 0.1) {
                goal_temperature = atoi(string_recv);
            }
        } else {
            string_recv[string_recv_index++] = tmp_data;
        }
        HAL_UART_Receive_IT(&huart3, (uint8_t *) &tmp_data, 1);
    }
}
