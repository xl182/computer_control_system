/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sdio.c
  * @brief   This file provides code for the configuration
  *          of the SDIO instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "sdio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SD_HandleTypeDef hsd;
DMA_HandleTypeDef hdma_sdio;

/* SDIO init function */

void MX_SDIO_SD_Init(void) {

    /* USER CODE BEGIN SDIO_Init 0 */

    /* USER CODE END SDIO_Init 0 */

    /* USER CODE BEGIN SDIO_Init 1 */

    /* USER CODE END SDIO_Init 1 */
    hsd.Instance = SDIO;
    hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
    hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
    hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
    hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
    hsd.Init.ClockDiv = 8;
    /* USER CODE BEGIN SDIO_Init 2 */
    hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
    if (HAL_SD_Init(&hsd) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_SD_ConfigWideBusOperation(&hsd, SDIO_BUS_WIDE_4B) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE END SDIO_Init 2 */

}

void HAL_SD_MspInit(SD_HandleTypeDef *sdHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (sdHandle->Instance == SDIO) {
        /* USER CODE BEGIN SDIO_MspInit 0 */

        /* USER CODE END SDIO_MspInit 0 */
        /* SDIO clock enable */
        __HAL_RCC_SDIO_CLK_ENABLE();

        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        /**SDIO GPIO Configuration
        PC8     ------> SDIO_D0
        PC9     ------> SDIO_D1
        PC10     ------> SDIO_D2
        PC11     ------> SDIO_D3
        PC12     ------> SDIO_CK
        PD2     ------> SDIO_CMD
        */
        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11
                              | GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        /* SDIO DMA Init */
        /* SDIO Init */
        hdma_sdio.Instance = DMA2_Channel4;
        hdma_sdio.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_sdio.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_sdio.Init.MemInc = DMA_MINC_ENABLE;
        hdma_sdio.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
        hdma_sdio.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
        hdma_sdio.Init.Mode = DMA_NORMAL;
        hdma_sdio.Init.Priority = DMA_PRIORITY_LOW;
        if (HAL_DMA_Init(&hdma_sdio) != HAL_OK) {
            Error_Handler();
        }

        /* Several peripheral DMA handle pointers point to the same DMA handle.
         Be aware that there is only one channel to perform all the requested DMAs. */
        /* Be sure to change transfer direction before calling
         HAL_SD_ReadBlocks_DMA or HAL_SD_WriteBlocks_DMA. */
        __HAL_LINKDMA(sdHandle, hdmarx, hdma_sdio);
        __HAL_LINKDMA(sdHandle, hdmatx, hdma_sdio);

        /* SDIO interrupt Init */
        HAL_NVIC_SetPriority(SDIO_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(SDIO_IRQn);
        /* USER CODE BEGIN SDIO_MspInit 1 */

        /* USER CODE END SDIO_MspInit 1 */
    }
}

void HAL_SD_MspDeInit(SD_HandleTypeDef *sdHandle) {

    if (sdHandle->Instance == SDIO) {
        /* USER CODE BEGIN SDIO_MspDeInit 0 */

        /* USER CODE END SDIO_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_SDIO_CLK_DISABLE();

        /**SDIO GPIO Configuration
        PC8     ------> SDIO_D0
        PC9     ------> SDIO_D1
        PC10     ------> SDIO_D2
        PC11     ------> SDIO_D3
        PC12     ------> SDIO_CK
        PD2     ------> SDIO_CMD
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11
                               | GPIO_PIN_12);

        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

        /* SDIO DMA DeInit */
        HAL_DMA_DeInit(sdHandle->hdmarx);
        HAL_DMA_DeInit(sdHandle->hdmatx);

        /* SDIO interrupt Deinit */
        HAL_NVIC_DisableIRQ(SDIO_IRQn);
        /* USER CODE BEGIN SDIO_MspDeInit 1 */

        /* USER CODE END SDIO_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */

HAL_StatusTypeDef
SDIO_ReadBlocks_DMA(SD_HandleTypeDef *hsd, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks) {
    HAL_StatusTypeDef Return_Status;
    HAL_SD_CardStateTypeDef SD_Card_Status;

    do {
        SD_Card_Status = HAL_SD_GetCardState(hsd);
    } while (SD_Card_Status != HAL_SD_CARD_TRANSFER);

    /* SDIO DMA DeInit */
    /* SDIO DeInit */
    HAL_DMA_DeInit(&hdma_sdio);
    /* SDIO DMA Init */
    /* SDIO Init */
    hdma_sdio.Instance = DMA2_Channel4;
    hdma_sdio.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_sdio.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio.Init.Mode = DMA_NORMAL;
    hdma_sdio.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_sdio) != HAL_OK) {
        Error_Handler();
    }

    __HAL_LINKDMA(hsd, hdmarx, hdma_sdio);

    Return_Status = HAL_SD_ReadBlocks_DMA(hsd, pData, BlockAdd, NumberOfBlocks);

    return Return_Status;
}

HAL_StatusTypeDef
SDIO_WriteBlocks_DMA(SD_HandleTypeDef *hsd, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks) {
    HAL_StatusTypeDef Return_Status;
    HAL_SD_CardStateTypeDef SD_Card_Status;

    do {
        SD_Card_Status = HAL_SD_GetCardState(hsd);
    } while (SD_Card_Status != HAL_SD_CARD_TRANSFER);

    /* SDIO DMA DeInit */
    /* SDIO DeInit */
    HAL_DMA_DeInit(&hdma_sdio);
    /* SDIO DMA Init */
    /* SDIO Init */
    hdma_sdio.Instance = DMA2_Channel4;
    hdma_sdio.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_sdio.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio.Init.Mode = DMA_NORMAL;
    hdma_sdio.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_sdio) != HAL_OK) {
        Error_Handler();
    }

    __HAL_LINKDMA(hsd, hdmatx, hdma_sdio);

    Return_Status = HAL_SD_WriteBlocks_DMA(hsd, pData, BlockAdd, NumberOfBlocks);

    return Return_Status;
}

/* USER CODE END 1 */