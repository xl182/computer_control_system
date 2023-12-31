//
// Created by ALIEN on 2023/6/24.
//

#ifndef COMPUTER_CONTROL_SYSTEM_CALLBACK_H
#define COMPUTER_CONTROL_SYSTEM_CALLBACK_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arm_math.h"
#include "adc.h"
#include "lcd.h"
#include "func.h"
#include "settings.h"
#include "gui.h"
#include "lvgl.h"

void display();
extern int time_counter;

#endif //COMPUTER_CONTROL_SYSTEM_CALLBACK_H
