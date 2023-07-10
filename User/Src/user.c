#include "user.h"

const float32_t PID_PARAM_KP = (float32_t) 10;
const float32_t PID_PARAM_KI = (float32_t) 1;
const float32_t PID_PARAM_KD = (float32_t) 1;

void fatfs_test() {
    uint8_t res;
    uint32_t bytes_written, bytes_read;
    char w_text[100] = "write text";
    char r_text[100];

    res = f_mount(&SDFatFS, SDPath, 1);
    printf("mount result :%d\r\n", res);

    res = f_open(&SDFile, "file.txt", FA_WRITE| FA_CREATE_ALWAYS); // FA_CREATE_ALWAYS
    if (res == 0) {
        printf("create success\r\n");
    } else {
        printf("create failure %d\r\n", res);
    }

    res = f_write(&SDFile, w_text, sizeof(w_text), &bytes_written);
    if (res == 0) {
        printf("write success\r\n");
    } else {
        printf("write failure %d\r\n", res);
    }

    res = f_close(&SDFile);
    if (res) {
        printf("f_close error!!! %d\r\n", res);
    } else {
        printf("f_close sucess!!! \r\n");
    }

    res = f_open(&SDFile, "file.txt", FA_READ | FA_OPEN_ALWAYS);
    res = f_read(&SDFile, r_text, sizeof(r_text), &bytes_read);
    if (res == 0) {
        printf("read success\r\n");
        printf("%s", r_text);
    } else {
        printf("read failure %d\r\n", res);
    }

    res = f_close(&SDFile);
    if (res) {
        printf("f_close error!!! %d\r\n", res);
    } else {
        printf("f_close sucess!!! \r\n");
    }

    res = f_mkdir("test");
    if (res) {
        printf("mkdir error!!! %d\r\n", res);
    } else {
        printf("mkdir sucess!!! \r\n");
    }
}

void init() {
    pid.Kp = PID_PARAM_KP;
    pid.Ki = PID_PARAM_KI;
    pid.Kd = PID_PARAM_KD;
    arm_pid_init_f32(&pid, 1);
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    MX_SDIO_SD_Init();
    MX_FATFS_Init();
    MX_DMA_Init();

    MX_USART1_UART_Init();
    MX_USART3_UART_Init();
    HAL_UART_Receive_IT(&huart3, (uint8_t *) &tmp_data, 1);

    fatfs_test();

    MX_SPI2_Init();
    __HAL_SPI_ENABLE(&hspi2);

    lv_init();
    LCD_Init();
    lv_port_disp_init();
    LCD_Display(true);
    LCD_Fill(0, 0, LCD_WIDTH, LCD_HEIGHT, GRAYBLUE);

    MX_ADC1_Init();
    HAL_ADC_MspInit(&hadc1);
    HAL_ADCEx_Calibration_Start(&hadc1);

    MX_TIM1_Init();
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    MX_TIM3_Init();
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

    MX_TIM4_Init();
    MX_TIM6_Init();
    MX_TIM7_Init();

    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_Base_Start_IT(&htim6);
    HAL_TIM_Base_Start_IT(&htim7);
}

int main() {
    init();
    gui_display();

    while (true) {
        lv_task_handler();
    }
}
