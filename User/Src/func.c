//
// Created by ALIEN on 2023/6/26.
//
#include "func.h"

int heat_level = 0;
char string_display[100] = {0}, string_send[100] = {0};
arm_pid_instance_f32 pid;
float temperature = 0, voltage = 0, NTC = 0;
uint16_t adc1_buffer[ADC_ARRAY_SIZE * ADC_NUMS] = {0};

void set_heat_level(int level) {
    assert(level <= 1000);
    TIM1->CCR1 = level;
}


void refresh_adc() {
    float res[ADC_NUMS] = {0};
    for (int i = 0; i < ADC_ARRAY_SIZE * ADC_NUMS; i++) {
        res[i % ADC_NUMS] += (float) adc1_buffer[i];
    }
    for (int i = 0; i < ADC_NUMS; i++) {
        res[i] = (res[i] / ADC_ARRAY_SIZE);
    }
    temperature = res[0];
    voltage = res[1];
    NTC = res[2];
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *) &adc1_buffer, ADC_ARRAY_SIZE * ADC_NUMS);
}

void send_bluetooth(char string[]) {
    HAL_UART_Transmit(&bluetooth, (uint8_t *) string, strlen(string), 0xFF);
}

void send_serial(char string[]) {
    HAL_UART_Transmit(&serial, (uint8_t *) string, strlen(string), 0xFF);
}
