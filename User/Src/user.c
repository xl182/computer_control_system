#include "user.h"

const float32_t PID_PARAM_KP = (float32_t) 10;
const float32_t PID_PARAM_KI = (float32_t) 1;
const float32_t PID_PARAM_KD = (float32_t) 1;


#include <string.h>
#define WRITE_READ_ADDR 0x00000000
#define NUMBER_OF_BLOCKS 1
#define BLOCK_SIZE 512
HAL_StatusTypeDef Return_Status;
HAL_SD_CardStateTypeDef SD_Card_Status;
HAL_DMA_StateTypeDef DMA_Status;
uint8_t Buffer_Tx[512];
uint8_t Buffer_Rx[512];


int sd_test() {
    uint16_t temp;
    printf(" changed?\r\n");
    printf("\r\n Initialize SD card successfully!\r\n\r\n");
    printf(" SD card information! \r\n");
    printf(" CardCapacity  : %llu \r\n", ((unsigned long long) hsd.SdCard.BlockSize * hsd.SdCard.BlockNbr));
    printf(" CardBlockSize : %d \r\n", hsd.SdCard.BlockSize);
    printf(" RCA           : %d \r\n", hsd.SdCard.RelCardAdd);
    printf(" CardType      : %d \r\n", hsd.SdCard.CardType);

    Return_Status = HAL_SD_Erase(&hsd, WRITE_READ_ADDR, WRITE_READ_ADDR + NUMBER_OF_BLOCKS * 4);
    printf("erase status :%d\r\n", Return_Status);

    Return_Status = SDIO_ReadBlocks_DMA(&hsd, Buffer_Rx, WRITE_READ_ADDR, NUMBER_OF_BLOCKS);
    printf("read status :%d\r\n", Return_Status);

    for (temp = 0; temp < 512; temp++) {
        printf("%4d", Buffer_Rx[temp]);
    }

    memset(Buffer_Tx, 55, sizeof(Buffer_Tx) - 1);
    SDIO_WriteBlocks_DMA(&hsd, Buffer_Tx, WRITE_READ_ADDR, NUMBER_OF_BLOCKS);
    printf("write status :%d\r\n", Return_Status);

    Return_Status = SDIO_ReadBlocks_DMA(&hsd, Buffer_Rx, WRITE_READ_ADDR, NUMBER_OF_BLOCKS);
    printf("read status :%d\r\n", Return_Status);

    for (temp = 0; temp < 512; temp++) {
        printf("%4d", Buffer_Rx[temp]);
    }
    printf("\n");
}

void fatfs_test() {

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
    SD_Driver.disk_initialize(0);
    MX_DMA_Init();

    MX_USART1_UART_Init();
    MX_USART3_UART_Init();
    HAL_UART_Receive_IT(&huart3, (uint8_t *) &tmp_data, 1);

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

    set_buzzer_level(100);
    HAL_Delay(100);
    set_buzzer_level(0);
    set_heat_level(10);
}

int main() {
    init();
    gui_display();
    sd_test();
    fatfs_test();
    while (true) {
        lv_task_handler();
    }
}
