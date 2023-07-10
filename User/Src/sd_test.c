//#define WRITE_READ_ADDR 0x100
//#define NUMBER_OF_BLOCKS 1
//#define BLOCK_SIZE 512
//HAL_StatusTypeDef Return_Status;
//HAL_SD_CardStateTypeDef SD_Card_Status;
//HAL_DMA_StateTypeDef DMA_Status;
//uint8_t Buffer_Tx[512];
//uint8_t Buffer_Rx[512];
//
//int sd_test() {
//    uint16_t temp;
//    printf(" changed?\r\n");
//    printf("\r\n Initialize SD card successfully!\r\n\r\n");
//    printf(" SD card information! \r\n");
//    printf(" CardCapacity  : %llu \r\n", ((unsigned long long) hsd.SdCard.BlockSize * hsd.SdCard.BlockNbr));
//    printf(" CardBlockSize : %d \r\n", hsd.SdCard.BlockSize);
//    printf(" RCA           : %d \r\n", hsd.SdCard.RelCardAdd);
//    printf(" CardType      : %d \r\n", hsd.SdCard.CardType);
//
////    Return_Status = HAL_SD_Erase(&hsd, WRITE_READ_ADDR, WRITE_READ_ADDR + NUMBER_OF_BLOCKS * 4);
////    printf("erase status :%d\r\n", Return_Status);
////
////    Return_Status = SDIO_ReadBlocks_DMA(&hsd, Buffer_Rx, WRITE_READ_ADDR, NUMBER_OF_BLOCKS);
////    printf("read status :%d\r\n", Return_Status);
//
////    for (temp = 0; temp < 512; temp++) {
////        printf("%4d", Buffer_Rx[temp]);
////    }
//
////    memset(Buffer_Tx, 55, sizeof(Buffer_Tx) - 1);
////    SDIO_WriteBlocks_DMA(&hsd, Buffer_Tx, WRITE_READ_ADDR, NUMBER_OF_BLOCKS);
////    printf("write status :%d\r\n", Return_Status);
////
////    Return_Status = SDIO_ReadBlocks_DMA(&hsd, Buffer_Rx, WRITE_READ_ADDR, NUMBER_OF_BLOCKS);
////    printf("read status :%d\r\n", Return_Status);
//
////    for (temp = 0; temp < 512; temp++) {
////        printf("%4d", Buffer_Rx[temp]);
////    }
//    printf("\n");
//    return 0;
//}