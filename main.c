#include "main.h"
  


#define CMD_START "_start_"
#define CMD_STOP "_stop_"

uint8_t state_writestream = 0;
uint8_t state_started = 0;

char input_buffer[MAX_BYTES_TO_READ];

void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_RXNE) {
        uint8_t data = USART1->DR; // Читаем данные, это автоматически сбросит флаг прерывания
        if(!state_started) {
          
        }
    }
    NVIC_ClearPendingIRQ(USART1_IRQn);
}


int main(void) {

  SystemInit();
  
  SD_Error SD_ErrorState = SD_OK;
  RCC_Init();
  APP_GPIO_Init();
  USART1_Init();

  printf("----- System started! -----\n");
  printf("----- SD-card initialization started! -----\n");

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

      res = SD_CardMount();

      // чтение файла с карты памяти, если она инициализировалась верно.
      if (res == FR_OK) {
          res = SD_CardFileRead();
      }
      else {
          printf("- SD-card mounting failed... \n");
      }

      // создание нового файла на карте и запись в него тестовой строки
      if (res == FR_OK) {
          res = SD_CardCreateFile();
      }
      else {
          printf("--- ERROR reading file on SD-card \n");
          printf("--- New file was NOT CREATED on SD-card \n");
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
