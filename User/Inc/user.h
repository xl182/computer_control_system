//
// Created by ALIEN on 2023/6/24.
//

#ifndef COMPUTER_CONTROL_SYSTEM_USER_H
#define COMPUTER_CONTROL_SYSTEM_USER_H

#include "settings.h"

#include <stdbool.h>
#include "iso646.h"
#include "arm_math.h"

#include "main.h"
#include "gpio.h"
#include "adc.h"
#include "usart.h"
#include "tim.h"
#include "spi.h"
#ifdef USE_ADC_DMA
#include "dma.h"
#endif

#include "lcd.h"
#include "queue.h"
#include "callback.h"


#endif //COMPUTER_CONTROL_SYSTEM_USER_H
