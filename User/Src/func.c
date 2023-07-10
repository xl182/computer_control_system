//
// Created by ALIEN on 2023/6/26.
//
#include "func.h"

int heat_level = 0;
char string_display[100] = {0}, string_send[100] = {0};
arm_pid_instance_f32 pid;
float temperature = 0, voltage = 0, NTC = 0;
uint16_t adc1_buffer[ADC_ARRAY_SIZE * ADC_NUMS] = {0};
char tmp_data = 0;
char string_recv[100] = {0};

void set_heat_level(int level) {
    level = 0;
    TIM1->CCR1 = level;
}

void set_buzzer_level(int level) {
    TIM3->CCR4 = level;
}

void refresh_adc_dma() {
    float res[ADC_NUMS] = {0};
    for (int i = 0; i < ADC_ARRAY_SIZE * ADC_NUMS; i++) {
        res[i % ADC_NUMS] += (float) adc1_buffer[i];
    }
    for (int i = 0; i < ADC_NUMS; i++) {
        res[i] = (res[i] / ADC_ARRAY_SIZE);
    }
    voltage = res[0];
    NTC = res[1];
    temperature = res[2];
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *) &adc1_buffer, ADC_ARRAY_SIZE * ADC_NUMS);
}

void refresh_adc() {
    int adc_sum[ADC_NUMS] = {0};
    for (int i = 0; i < ADC_ARRAY_SIZE; i++) {
        for (int j = 0; j < ADC_NUMS; j++) {
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, 50);
            adc_sum[j] += (uint16_t) HAL_ADC_GetValue(&hadc1);
        }
    }
    voltage = (float) adc_sum[0] / ADC_ARRAY_SIZE;
    NTC = (float) adc_sum[1] / ADC_ARRAY_SIZE;
    temperature = (float) adc_sum[2] / ADC_ARRAY_SIZE;
}

void send_bluetooth(char string[]) {
    HAL_UART_Transmit(&bluetooth, (uint8_t *) string, strlen(string), 0xFF);
}

void send_serial(char string[]) {
    HAL_UART_Transmit(&serial, (uint8_t *) string, strlen(string), 0xFF);
}
