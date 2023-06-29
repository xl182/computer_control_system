//
// Created by ALIEN on 2023/6/27.
//

#ifndef COMPUTER_CONTROL_SYSTEM_PID_H
#define COMPUTER_CONTROL_SYSTEM_PID_H

#include "main.h"

typedef struct PID {
    float Kp, Ki, Kd, limit;
} PID;

typedef struct Error {
    float current_error;  // 当前误差
    float last_error;     // 上一次误差
    float previous_error; // 上上次误差
} Error;

uint16_t PID_Increase(Error *err, PID *pid, uint16_t current, uint16_t expected);

extern PID pid;

#endif //COMPUTER_CONTROL_SYSTEM_PID_H
