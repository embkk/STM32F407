#include "main.h"
  

#define BUFFER_SIZE_BYTES   (uint16_t)2048
#define START_SECTOR_NUM    (uint32_t)4    //0-3 sectors for FAT markup

uint8_t readData_8[BUFFER_SIZE_BYTES];
uint8_t writeBuffer_bytes[BUFFER_SIZE_BYTES];

SD_CardInfo SDCardInfo;



int main(void) {

  SystemInit();
  
  SD_Error SD_ErrorState = SD_OK;
  RCC_Init();
  APP_GPIO_Init();
  USART1_Init();

    // Тестовые данные для записи
  for (uint16_t i = 0; i < BUFFER_SIZE_BYTES; i++){
      writeBuffer_bytes[i] = (i & 0x00FF);  // take LSB only. So get bytes value 0x00 - 0xFF
  }

  printf("----- System started! -----\n");
  printf("----- SD-card initialization started! -----\n");

  char* x = "hello";
  usart1_send((uint8_t*)x, 6);
  // Инициализация карты
  SD_ErrorState = SD_Init();

  if (SD_ErrorState == SD_OK) {

      printf("----- SD-card Getting information! -----\n");
      // Получаем информацию о карте
      SD_GetCardInfo(&SDCardInfo);

      printf("----- SD-card Selecting! -----\n");
      // Выбор карты
      SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));

      // настройка режима работы POLLING MODE - режим опроса карты
      SD_SetDeviceMode(SD_POLLING_MODE);

      printf("----- SD-card Block %d bytes writing! -----\n", BUFFER_SIZE_BYTES);

      // запись блока данных, начиная с сектора START_SECTOR_NUM. Пишется один сектор данных.
      SD_ErrorState = SD_WriteBlockBytes(START_SECTOR_NUM, writeBuffer_bytes, SD_BLOCK_SIZE_BYTES);

      if(SD_ErrorState == SD_OK){
          printf("----- SD-card Block %d bytes reading! -----\n", BUFFER_SIZE_BYTES);

          // чтение данных. Начиная с сектора № 65544, чтение 4-х секторов подряд
          SD_ErrorState = SD_ReadMultiBlocksBytes(18752, readData_8, SD_BLOCK_SIZE_BYTES, 4);

          // отправка считанного текста в USART1
          if(SD_ErrorState == SD_OK) {
            //LOG_MESSAGE((char*)readData_8, BUFFER_SIZE_BYTES);
            usart1_send(readData_8, BUFFER_SIZE_BYTES);
          }
          else printf("----- SD-card reading error! -----\n");
      }
      else{
          printf("----- Error SD-card writing FAILED \n");
      }
  } else {
    printf("----- SD-card not found! -----\n");
  }


  while(1) {
  }
}

void SysTick_Handler(void)
{
  //timer_counter();
}
