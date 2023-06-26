#include "user.h"

const float32_t PID_PARAM_KP = (float32_t) 50;
const float32_t PID_PARAM_KI = (float32_t) 0.01;
const float32_t PID_PARAM_KD = (float32_t) 5;


void init() {
    pid.Kp = PID_PARAM_KP;
    pid.Ki = PID_PARAM_KI;
    pid.Kd = PID_PARAM_KD;
    arm_pid_init_f32(&pid, 1);

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    MX_USART1_UART_Init();
    MX_USART3_UART_Init();

    MX_SPI2_Init();
    HAL_SPI_MspInit(&hspi2);
    __HAL_SPI_ENABLE(&hspi2);

    LCD_Init();
    LCD_Display(true);
    LCD_Fill(0, 0, LCD_WIDTH, LCD_HEIGHT, GRAYBLUE);

    MX_DMA_Init();
    MX_ADC1_Init();
    HAL_ADC_MspInit(&hadc1);
    HAL_ADCEx_Calibration_Start(&hadc1);

    MX_TIM1_Init();
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM6_Init();
    MX_TIM7_Init();

    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_Base_Start_IT(&htim6);
    HAL_TIM_Base_Start_IT(&htim7);
}

int main() {
    init();
    while (true) {
    }
}
