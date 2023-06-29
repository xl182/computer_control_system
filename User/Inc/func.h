//
// Created by ALIEN on 2023/6/26.
//

#ifndef COMPUTER_CONTROL_SYSTEM_FUNC_H
#define COMPUTER_CONTROL_SYSTEM_FUNC_H

#include <assert.h>
#include <main.h>
#include "arm_math.h"
#include "tim.h"
#include "usart.h"
#include "adc.h"

#define ADC_ARRAY_SIZE 16
#define ADC_NUMS 3

#define serial huart1
#define bluetooth huart3

extern arm_pid_instance_f32 pid;
extern uint16_t adc1_buffer[ADC_ARRAY_SIZE * ADC_NUMS];
extern float temperature, voltage, NTC;
extern char string_display[100], string_send[100];
extern int heat_level;

extern char tmp_data;
extern char string_recv[100];

void set_heat_level(int level);
void set_buzzer_level(int level);
void refresh_adc();

void send_bluetooth(char string[]);

void send_serial(char string[]);

#endif //COMPUTER_CONTROL_SYSTEM_FUNC_H
