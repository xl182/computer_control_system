#include "user.h"

const float32_t PID_PARAM_KP = (float32_t) 10;
const float32_t PID_PARAM_KI = (float32_t) 1;
const float32_t PID_PARAM_KD = (float32_t) 1;

void init() {
    pid.Kp = PID_PARAM_KP;
    pid.Ki = PID_PARAM_KI;
    pid.Kd = PID_PARAM_KD;
    arm_pid_init_f32(&pid, 1);

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (HAL_GPIO_ReadPin(SW_GPIO_Port, SW_Pin) == SET) {};

    MX_USART1_UART_Init();
    MX_USART3_UART_Init();
    HAL_UART_Receive_IT(&huart3, (uint8_t *) &tmp_data, 1);

    MX_SPI2_Init();
    HAL_SPI_MspInit(&hspi2);
    __HAL_SPI_ENABLE(&hspi2);

    LCD_Init();
    LCD_Display(true);
    LCD_Fill(0, 0, LCD_WIDTH, LCD_HEIGHT, GRAYBLUE);

#if defined USE_ADC_DMA
    MX_DMA_Init();
#endif

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
    set_buzzer_level(100);
    HAL_Delay(100);
    set_buzzer_level(0);
    set_heat_level(10);
    while (true) {
        set_heat_level(0);
        HAL_Delay(1);
#if defined USE_ADC_DMA
        refresh_adc_dma();
#else
        refresh_adc();
#endif
        display();
        HAL_Delay(200);
    }
}
