#include "main.h"
  
#define CMD_START "_start_"
#define CMD_STOP "_stop_"

#define OUTPUT_BUFFER_DELAY 84000
#define INPUT_BUFFER_DELAY 8400

SD_Error SD_ErrorState = SD_OK;

uint8_t state_started = 0;

char input_buffer[MAX_BYTES_TO_READ] ={};
char output_buffer[MAX_BYTES_TO_READ] ={};

uint8_t input_buffer_len;
uint8_t output_buffer_len;

uint32_t output_counter;
uint32_t input_counter;

void SD_Start(void) {
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

    res = SD_CardWriteStream(NULL, 0);

    // создание нового файла на карте и запись в него тестовой строки
    if (res != FR_OK) {
        printf("--- ERROR reading file on SD-card \n");
        printf("--- New file was NOT CREATED on SD-card, error code = %d \n", res);
    }
  } else {
    printf("----- SD-card not found! -----\n");
  }
}

uint8_t check_cmd(const char* cmd, uint8_t cmd_len ) {
  for (int i = 0; i < cmd_len-1; i++) {
    if(i>=input_buffer_len) {
      return 2; // Part of a command
    }
    if (cmd[i] != input_buffer[i]) {
      return 1; // Not a command
    }
  }
  return 0; // Complete command
}

uint8_t parse_buffer_char(char c) {
  //LOG_MESSAGE("[%d] Input buffer %s", buffer_len, input_buffer);
  uint8_t cmd_status = 1; // Not a command
  if(!state_started) {
    cmd_status = check_cmd(CMD_START, sizeof(CMD_START));
    if(cmd_status == 0) {
      printf("CMD: _start_\n");
      SD_Start();
      state_started = 1;
    }
  } else {
    cmd_status = check_cmd(CMD_STOP, sizeof(CMD_STOP));
    if(cmd_status == 0) {
      printf("CMD: _stop_\n");
      f_close(&file);
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
    output_counter = 0;
    input_counter = 0;
  }
  NVIC_ClearPendingIRQ(USART1_IRQn);
}


int main(void) {

  SystemInit();

  RCC_Init();
  APP_GPIO_Init();
  USART1_Init();

  printf("----- System started! -----\n");
  printf("----- SD-card initialization started! -----\n");

  uint8_t parse_result = 3; // unknown
  
  while(1) {
    __disable_irq();
    output_counter++;
    input_counter++;

    //parse input buffer
    for(int i=0; i<input_buffer_len;i++) {
      parse_result = parse_buffer_char(input_buffer[i]);

      if(parse_result == 0) {
        //command
        input_buffer_len = 0;
      }
    }
    if(input_counter>INPUT_BUFFER_DELAY) {

      // clear garbage input
      if(!state_started && parse_result==1) input_buffer_len = 0;

      // pack input buffer
      if(state_started && parse_result==1 && input_buffer_len>0) {
      
        for(int i=0;i<input_buffer_len;i++) {
          output_buffer[output_buffer_len] = input_buffer[i];
          output_buffer_len++;
        }

        /*printf("Drop input buffer [%d]: ", input_buffer_len);
        for(int i=0;i<input_buffer_len;i++) printf("%c", input_buffer[i]);
        printf("\n");*/

        input_buffer_len = 0;
        input_counter = 0;
      }
    }
    __enable_irq();
    
    if(output_counter>OUTPUT_BUFFER_DELAY && output_buffer_len>0) {
      res = SD_CardWriteStream(output_buffer, output_buffer_len);

      /*printf("Writen output buffer [%d]: ", output_buffer_len);
      for(int i=0;i<output_buffer_len;i++) printf("%c", output_buffer[i]);
      printf("\n");*/

      output_buffer_len = 0;
      output_counter = 0;
    }
  }
}
