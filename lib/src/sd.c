#include "sd.h"

#include "usart.h"
#include <stdlib.h>
#include <string.h>

FATFS fs;
FRESULT res;
FIL file;
FILINFO file_info;
DIR dir;

SD_CardInfo SDCardInfo;

FRESULT SD_CardMount(void){
    res = f_mount(&fs, "/", 1); // примонтировать раздел немедленно

    if(res != FR_OK) {
        printf("--- f_mount() failed, res = %d\r\n", res);
        return FR_INT_ERR;
    }
    
    printf("+++ f_mount() done!\r\n");
    return FR_OK;
}

FRESULT SD_CardFileRead(void){
    const char file_name[12] = FILENAME;
    uint8_t readed_data[MAX_BYTES_TO_READ];
    unsigned int BytesReaded = 0;

    printf("--- Checking for existed file %s on SD-card \n", file_name);
    res = f_stat(file_name, &file_info);
    if (res != FR_OK){
        printf("--- File %s does not exist on SD-card \n", file_name);
        return res;
    }
    printf("+++ FOUND file %s \n", file_info.fname);
    printf("+++ file SIZE = %d bytes \n", (uint32_t)file_info.fsize);
    printf("--- opening TXT-file %s ... \n", file_info.fname); // NOTE: <<-- here use file_info.fname from f_stat() instead file_name

    res = f_open(&file, file_info.fname, FA_READ);

    if(res == FR_OK){
        printf("+++ opening file complete sucessfully. ErrorCode res = %d\n", res);
        printf("--- Starting file reading... \n");

        // проверка сколько секторов нужно считать, чтобы весь текст из файла вычитать.
        // ограничение по 2048 байт = 4 сектора

        // чтение всего файла целиком, т.к. размер файла меньше размера массива для считаваемых данных
        if ( (uint16_t)file_info.fsize < MAX_BYTES_TO_READ ) {
            res = f_read(&file, readed_data, (uint16_t)file_info.fsize, &BytesReaded); // read whole file data. file zise less than array length

            if(res == FR_OK){
                printf("\n\n+++ File reading successfully! Readed string: \n");
                usart1_send(readed_data, BytesReaded);
                printf("\n\n--- Readed bytes number = %d \n", BytesReaded );
                f_close(&file);
            }
        } else {
          uint16_t reading_iterations = (uint16_t)file_info.fsize / MAX_BYTES_TO_READ;
          uint16_t bytes_left_to_read = (uint16_t)file_info.fsize % MAX_BYTES_TO_READ; // number of bytes left to read. 1 to 2047 bytes
          uint16_t current_itreation = 0;

          // чтение файла по 2048 байт, по 4 сектора
          printf("--- File reading long data! Readed string: \n");
          while (current_itreation < reading_iterations) {
              res = f_read(&file, readed_data, MAX_BYTES_TO_READ, &BytesReaded);
              if (res == FR_OK) {
                  usart1_send(readed_data, BytesReaded); // отправка в USART1 строк по 2048 байт сразу после чтения.
              }
              current_itreation++;
          }

          // вычитывание оставшихся байтов, которые не были считаны в итерациях по 2048 байт. Это кол-во байтов от 1 до 2047
          if (res == FR_OK) {
              if (bytes_left_to_read > 0) {
                  res = f_read(&file, readed_data, bytes_left_to_read, &BytesReaded);
                  if (res == FR_OK) {
                      usart1_send(readed_data, BytesReaded); // отправка в USART1 оставшейся строки длинной от 1 до 2047 байт
                  }
              }
          }

          if (res == FR_OK) {
              printf("\n\n+++ Long file was readed successfully!\n");
              printf("+++ was readed %d bytes successfully!\n", (uint16_t)file_info.fsize);
              f_sync(&file);
              f_close(&file);
          }
          else {
              printf("--- reading file FAILED! ErrorCode = %d \n", res);
              f_close(&file);
              return res;
          }
        }
    } else {
      printf("---- File open error  res = %d ----", res);
    }
    return res;
}

FRESULT SD_CardCreateFile(void) {
    const char fl_name[12] = "crt0.txt";
    uint16_t WritedBytes = 0;

    res = f_open(&file, fl_name, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);

    if (res != FR_OK) {
        printf("--- Creating file %s FAILED! Error code = %d \n", fl_name, res);
    } 
    else {
        printf("+++ file %s was created successfully \n", fl_name);
        printf("+++ Writing test string into file %s ... \n", fl_name);

        // Резервируем память для строки file_text
        uint8_t *file_text = malloc(128 * sizeof(uint8_t));
        // Записываем тестовую строку в file_text
        sprintf((char*)file_text, "Test string for file creation!!! \n");

        // Записываем строку file_text в файл
        res = f_write(&file, file_text, strlen((char*)file_text), (UINT*)&WritedBytes);

        if (res != FR_OK) {
            printf("--- Writing into file %s FAILED! Error code = %d \n", fl_name, res);
        } else {
            printf("+++ Writing string into file %s successfully \n", fl_name);
        }

        f_close(&file);
        free(file_text); // Рекомендуется добавить освобождение памяти
    }

    return res;
}

FRESULT SD_CardWriteStream(const char* stream, const uint32_t len) {
    printf("Write %d symbols..", len);
    const char fl_name[12] = FILENAME;
    uint16_t WritedBytes = 0;

    res = f_open(&file, fl_name, FA_OPEN_APPEND | FA_READ | FA_WRITE);

    if (res != FR_OK) {
        printf("> Creating file %s FAILED! Error code = %d \n", fl_name, res);
    } else {
        printf("> file stream opened %s\n", fl_name);

        if(len>0) {

          // Резервируем память для строки file_text
          uint8_t *file_text = malloc(len * sizeof(uint8_t));
          // Записываем тестовую строку в file_text
          sprintf((char*)file_text, stream, len);

          // Записываем строку file_text в файл
          res = f_write(&file, file_text, strlen((char*)file_text), (UINT*)&WritedBytes);

          if (res != FR_OK) {
              printf(">> Writing into file %s FAILED! Error code = %d \n", fl_name, res);
          } else {
              printf(">> Writing %d into file %s successfully \n", len, fl_name);
          }
          free(file_text); // Рекомендуется добавить освобождение памяти
        }

        f_sync(&file);
        f_close(&file);
    }

    return res;
}


