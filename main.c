#include "main.h"
  
#define CMD_START "_start_"
#define CMD_STOP "_stop_"

uint8_t state_started = 0;
uint8_t state_cmd = 0;

char input_buffer[MAX_BYTES_TO_READ] ={'\0'};
char output_buffer[MAX_BYTES_TO_READ] ={'\0'};
uint8_t input_buffer_len;
uint8_t output_buffer_len;


uint8_t check_cmd(const char* cmd, uint8_t cmd_len ) {
  for (int i = 0; i < cmd_len-1; i++) {
    if(i>=input_buffer_len) {
      return 2; // Part of a command
    }
    if (cmd[i] != input_buffer[i]) {
      return 1; // Not a command
    }
  }
  //LOG_MESSAGE("True");
  return 0; // Complete command
}

uint8_t parse_buffer_char(char c) {
  //LOG_MESSAGE("[%d] Input buffer %s", buffer_len, input_buffer);
  uint8_t cmd_status = 1; // Not a command
  if(!state_started) {
    cmd_status = check_cmd(CMD_START, sizeof(CMD_START));
    if(cmd_status == 0) {
      LOG_MESSAGE("CMD: _start_");
      state_started = 1;
    }
  } else {
    cmd_status = check_cmd(CMD_STOP, sizeof(CMD_STOP));
    if(cmd_status == 0) {
      LOG_MESSAGE("CMD: _stop_");
      state_started = 0;
    }
  }

  //LOG_MESSAGE("%s, check_cmd = %d, state_cmd = %d", state_started ? "Started" : "Not started", cmd_status, state_cmd);
  return cmd_status;
}

void USART1_IRQHandler(void) {
  if (USART1->SR & USART_SR_RXNE) {
    input_buffer[input_buffer_len] = USART1->DR;
    input_buffer_len++;
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

  uint8_t parse_result;
  
  while(1) {
    for(int i=0; i<input_buffer_len;i++) {
      parse_result = parse_buffer_char(input_buffer[i]);

      if(parse_result == 0) {
        //command
        input_buffer_len = 0;
        break;
      } else if(state_started && parse_result==1) {
        //write a symbol
        output_buffer[output_buffer_len] = input_buffer[i];
        output_buffer_len++;
        input_buffer_len--;
      }
    }

    for(int i=0; i<output_buffer_len; i++ ) {
      LOG_MESSAGE("Writen %c", output_buffer[i]);
      output_buffer_len = 0;
    }
  }
}

void SysTick_Handler(void)
{
  //timer_counter();
}
