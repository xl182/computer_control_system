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

#include "queue.h"
#include "func.h"
#include "callback.h"

#include "lcd.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "gui.h"
#include "gui_guider.h"
#include "events_init.h"

#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "ff.h"
#include "diskio.h"
#include "bsp_driver_sd.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}

#endif //COMPUTER_CONTROL_SYSTEM_USER_H
