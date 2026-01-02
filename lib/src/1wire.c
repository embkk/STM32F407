
#include "main.h"
uint8_t Start_1wire(void){ // функция начала транзакции 1-wire
  tx_mode_1wire();     // Переключить пин в режим вывода
  pull_low_1wire();    // Master reset pulse - опустить пин в низкое состояние
  delay_us_tim10(500);       // Задержка на 500 мкс (для импульса сброса)
  release_1wire();     // Отпустить пин (станет высоким из-за подтяжки)
  rx_mode_1wire();     // Переключить пин в режим ввода для чтения ответа
  delay_us_tim10(100);       // wait 100 us = 60 us pause + 40 us presence pulse

  if(check_1wire()){   // Проверить состояние пина (ожидается низкий уровень от устройства)
    return 1;          // no presence pulse from 1-wire device (пин остался высоким)
  }
  else{
    delay_us_tim10(200);     // received presence pulse from 1-wire device (пин опустился в низкое состояние)
    return 0;
  }
}

void WriteByte_1wire(uint8_t byte_value){
  uint8_t write_bit_code = 0;
  uint8_t tmp = 0;
  tx_mode_1wire(); // Переключаем пин в режим вывода

  for(uint8_t i = 0; i < 8; i++){
    write_bit_code = 0;
    tmp = (1 << i); // Выбираем текущий бит для записи
    write_bit_code = (byte_value & tmp); // Проверяем, установлен ли бит

    pull_low_1wire(); // Начинаем импульс записи, опуская пин в низкое состояние
    delay_us_tim10(5);      // Задержка на 5 мкс (часть временного слота записи)

    if(write_bit_code != 0){ // Если бит, который нужно записать, равен 1
      release_1wire();       // Отпускаем пин, чтобы он поднялся в высокое состояние
    }
    // Если бит, который нужно записать, равен 0, пин останется в низком состоянии

    delay_us_tim10(55); // write bit slot time = 60 us (общая задержка для временного слота бита)
    release_1wire(); // Гарантируем, что пин отпущен после завершения слота (для бита 0 он мог быть еще низким)
    delay_us_tim10(2);     // пауза между битами 2 мкс
  }
  rx_mode_1wire(); // После записи байта переключаем пин обратно в режим ввода
}

uint8_t ReadByte_1wire(void){
  uint8_t rx_byte = 0; // Переменная для хранения прочитанного байта

  for(uint8_t i = 0; i < 8; i++){ // Цикл для чтения 8 бит
    tx_mode_1wire();     // Переключаем пин в режим вывода
    pull_low_1wire();    // Мастер начинает импульс чтения, опуская пин в низкое состояние
    delay_us_tim10(2);         // Задержка на 2 мкс
    release_1wire();     // Отпускаем пин, чтобы он поднялся в высокое состояние
    rx_mode_1wire();     // Переключаем пин в режим ввода для чтения ответа от ведомого
    delay_us_tim10(12);        // Задержка на 12 мкс (для стабилизации сигнала и чтения бита)

    if(check_1wire()){   // Проверяем состояние пина
      rx_byte |= (1 << i); // if received one (если пин высокий, это бит '1')
    }
    // Если пин низкий, бит '0', rx_byte не изменится

    delay_us_tim10(60-14);     // read bit slot time = 60 us (общая задержка для временного слота бита)
                         // (60 - 2 - 12 = 46, поэтому Delay_us(46))
    tx_mode_1wire();     // Переключаем пин обратно в режим вывода
    release_1wire();     // Гарантируем, что пин отпущен и подтянут к VCC (высокий)
    delay_us_tim10(2);         // пауза между битами 2 мкс
  }
  return rx_byte;        // Возвращаем прочитанный байт
}

/*
Алгоритм вычислении CRC:
  Циклически сдвигаем CRC и вычисляем бит shift_in_bit = CRC[7] XOR data_bit_in
  Если shift_in_bit == 1, то после сдвига выполняем еще (CRC xor POLY)
  Пока не кончатся биты в последовательности данных
  data_bit_in - это младший бит в байте.
  В CRC в младший бит задвигаются байты входных данных начиная с младшего бита.
*/
uint8_t CRC_Calc(uint8_t mass[], uint8_t mass_size, uint8_t POLY){
  uint8_t crc = 0;
  uint8_t crc_out = 0;
  uint8_t in_data;
  uint8_t in_bits; // Эта переменная не используется в данном коде, но была объявлена на изображении.

  for(uint8_t j = 0; j < mass_size; j++){ // Перебираем все байты во входном массиве
    in_data = mass[j]; // Получаем текущий байт

    for(uint8_t i = 0; i < 8; i++){ // Перебираем все биты в текущем байте
      // Проверяем бит CRC[7] (старший бит crc) и младший бит in_data
      if(((crc & 0x80) >> 7) != (in_data & 0x01)){
        crc = crc << 1; // Сдвигаем CRC влево
        crc = crc ^ POLY; // Выполняем XOR с полиномом, если биты не совпадают
      }
      else{
        crc = crc << 1; // Просто сдвигаем CRC влево
      }
      in_data = in_data >> 1; // Сдвигаем входные данные для перехода к следующему биту
    }
  }

  // разворачиваем CRC биты в правильном порядке
  // (обратная перестановка битов для окончательного CRC)
  for(uint8_t i = 0; i < 8; i++){
    if(crc & (1 << i)) crc_out |= (1 << (7-i));
  }
  return crc_out;
}


uint8_t Read_ROM64(uint8_t *family_code, uint8_t ser_num[], uint8_t *crc){
  uint8_t tmp_array[ROM64_BYTE_LEN]; // Временный массив для хранения ROM
  uint8_t crc_calculated = 0;
  uint8_t err_code = 0; // Эта переменная объявлена, но не используется напрямую в этом фрагменте.

  if(Start_1wire() == OK_1WIRE){ // 1-wire device found (Если устройство 1-wire найдено)
    WriteByte_1wire(READ_ROM);   // Отправляем команду READ_ROM
    delay_us_tim10(100);               // Задержка

    *family_code = ReadByte_1wire(); // Читаем байт кода семейства
    tmp_array[0] = *family_code;     // Сохраняем его во временном массиве

    for(uint8_t i = 0; i < 6; i++){  // Читаем 6 байтов серийного номера
      ser_num[i] = ReadByte_1wire(); // Сохраняем в ser_num
      tmp_array[i+1] = ser_num[i];   // И во временном массиве
    }

    *crc = ReadByte_1wire();       // Читаем байт CRC
    tmp_array[7] = *crc;             // Сохраняем его во временном массиве

    // Вывод информации (отладочный вывод)
    printf("==========\n");
    printf("===== READ ROM 64 bits ...\n");
    printf("===== SCRATCH = ");
    for (uint8_t i = 0; i < ROM64_BYTE_LEN; i++){
      printf("0x%X ", tmp_array[i]);
    }
    printf("\n==== CRC Rx = 0x%X \n", tmp_array[7]);

    // Вычисляем CRC для прочитанных данных
    crc_calculated = CRC_Calc(tmp_array, 7, CRC_POLYNOM);
    printf("==== CRC calculated = 0x%X \n", crc_calculated);

    // Сравниваем полученный CRC с вычисленным
    if(crc_calculated == tmp_array[7]) return OK_1WIRE; // Если CRC совпадает, все ОК
    else return CRC_ERR_1WIRE;                           // error ROM64 read (CRC не совпал)
  }
  else{
    return NO_DEVICE_1WIRE; // error. 1-wire device are not found
  }
}

uint8_t ReadScratchpad(uint8_t scratch_array[]){
  uint8_t err_code = 0;       // Объявлена, но не используется напрямую.
  uint16_t temp = 0;          // Объявлена, но не используется напрямую.
  uint8_t scratch_tmp[ROM64_BYTE_LEN] = {}; // Временный массив для scratchpad (инициализирован нулями)
  uint8_t crc_calculated = 0;

  if(Start_1wire() == OK_1WIRE){ // 1-wire device found (Если устройство 1-wire найдено)
    WriteByte_1wire(SKIP_ROM);     // Отправляем команду SKIP_ROM
    delay_us_tim10(100);                 // Задержка
    WriteByte_1wire(READ_SCRATCH); // Отправляем команду READ_SCRATCH
    delay_us_tim10(100);                 // Задержка

    for(uint8_t i = 0; i < SCRATCH_BYTE_LEN; i++){ // read all 9 bytes from scratchpad
      scratch_tmp[i] = ReadByte_1wire();           // Читаем байт
      delay_us_tim10(100);                               // Задержка после каждого байта
    }

    // Вычисляем CRC для прочитанных данных (последний байт scratch_tmp - это CRC)
    crc_calculated = CRC_Calc(scratch_tmp, (SCRATCH_BYTE_LEN - 1), CRC_POLYNOM);

    // Сравниваем вычисленный CRC с тем, что был прочитан
    if(crc_calculated == scratch_tmp[SCRATCH_BYTE_LEN - 1]){
      for(uint8_t i = 0; i < SCRATCH_BYTE_LEN; i++) scratch_array[i] = scratch_tmp[i];
      return OK_1WIRE; // Если CRC совпадает, все ОК
    }
    else{
      printf("--- ERROR: Scratch Read CRC mismatch \n"); // Сообщение об ошибке
      return NO_DEVICE_1WIRE; // Возвращаем ошибку, если CRC не совпал
    }
  }
  else{
    return NO_DEVICE_1WIRE; // Возвращаем ошибку, если устройство 1-wire не найдено
  }
}

uint8_t Convert_Temperature(void){
  uint8_t err_code = 0; // Объявлена, но не используется напрямую.
  uint16_t temp = 0;    // Объявлена, но не используется напрямую.

  if(Start_1wire() == OK_1WIRE){ // 1-wire device found (Если устройство 1-wire найдено)
    WriteByte_1wire(SKIP_ROM);   // Отправляем команду SKIP_ROM
    delay_us_tim10(100);               // Задержка
    WriteByte_1wire(CONVERT_T);  // Отправляем команду CONVERT_T (начало измерения температуры)
    delay_us_tim10(100);               // Задержка
    return OK_1WIRE;             // Возвращаем OK
  }
  else{
    return NO_DEVICE_1WIRE;      // Возвращаем ошибку, если устройство 1-wire не найдено
  }
}
uint8_t WriteScratch(uint8_t tx_array[]){ // write only 3 byties from array [0 1 2 ] will be writed
  if(Start_1wire() == OK_1WIRE){      // 1-wire device found (Если устройство 1-wire найдено)
    WriteByte_1wire(SKIP_ROM);        // Отправляем команду SKIP_ROM
    delay_us_tim10(100);                    // Задержка
    WriteByte_1wire(WRITE_SCRATCH);   // Отправляем команду WRITE_SCRATCH
    delay_us_tim10(100);                    // Задержка

    for(uint8_t i = 0; i < 3; i++){   // write only 3 byties from tx_array
      WriteByte_1wire(tx_array[i]);   // Записываем байт из массива
      delay_us_tim10(100);                  // Задержка
    }
    Start_1wire();                    // final reset pulse (завершающий импульс сброса)
    return OK_1WIRE;                  // Возвращаем OK
  }
  else{
    return NO_DEVICE_1WIRE;           // Возвращаем ошибку, если устройство 1-wire не найдено
  }
}

void USART1_Init(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // PA9 = TX, PA10 = RX
// Включение тактирования USART1 от шины APB2
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

// Альтернативная функция для PA9 (USART1 - TX)
  GPIOA->MODER &= ~(GPIO_MODER_MODE9); // Очистка битов MODER для PA9
  GPIOA->MODER |= GPIO_MODER_MODE9_1;  // Установка альтернативной функции (10)
  GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9); // Очистка битов AF для PA9
  GPIOA->AFR[1] |= (7 << GPIO_AFRH_AFSEL9_Pos); // AF7 для PA9
  GPIOA->OTYPER &= ~GPIO_OTYPER_OT9; // Push-pull для TX

// Альтернативная функция для PA10 (USART1 - RX)
  GPIOA->MODER &= ~(GPIO_MODER_MODE10); // Очистка битов MODER для PA10
  GPIOA->MODER |= GPIO_MODER_MODE10_1;  // Установка альтернативной функции (10)
  GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL10); // Очистка битов AF для PA10
  GPIOA->AFR[1] |= (7 << GPIO_AFRH_AFSEL10_Pos); // AF7 для PA10

/* Расчет скорости передачи данных:
   (84МГц/9600)/16 = 546.875;
   Целая часть = 546 = 0x222;
   Дробная часть = 0.875*16 = 14 = 0x0E
*/
  // Выключение USART перед настройкой (если был включен)
  USART1->CR1 &= ~USART_CR1_UE;
  
  // Настройка скорости передачи данных
  USART1->BRR = 0x222E; // 9600
  
  // Настройка формата: 8-бит, без контроля четности, 1 стоповый бит
  USART1->CR1 &= ~(USART_CR1_M | USART_CR1_PCE); // 8-бит, без контроля четности
  USART1->CR2 &= ~(USART_CR2_STOP); // 1 стоповый бит
  
  // Включение приемника и передатчика
  USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
  
  // Включение USART1
  USART1->CR1 |= USART_CR1_UE;
}