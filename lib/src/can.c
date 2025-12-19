#include "can.h"
#include "stm32f407xx.h"

void CAN2_init(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;             // мастер обоих CAN
  RCC->APB1ENR |= RCC_APB1ENR_CAN2EN;

  GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5;       // high speed
  GPIOB->MODER   |= GPIO_MODER_MODE5_1;           // alt func
  GPIOB->AFR[0]  |= (9 << GPIO_AFRL_AFSEL5_Pos);  // AF9 B5 - CAN2_RX

  GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;       // high speed
  GPIOB->MODER   |= GPIO_MODER_MODE6_1;           // alt func
  GPIOB->AFR[0]  |= (9 << GPIO_AFRL_AFSEL6_Pos);  // AF9 B5 - CAN2_TX

  CAN2->MCR |= CAN_MCR_INRQ;               // init can2
  while((CAN2->MSR & CAN_MSR_INAK) == 0) ; //wait init

  CAN2->MCR |= CAN_MCR_NART;  // auto retranslation off, no need
  CAN2->MCR |= CAN_MCR_AWUM;  // auto sleepmode off on message receive
  CAN2->BTR  = 0x00;          // RESET
  
  // 42 MHz / 250 000 / 15 = 11.2
  // 42 / 12 = 3.5 MHz
  // 3.5 MHz / 250 000 = 14
  // CAN_Bit_time = (1 + BS1 + BS2 ) = 14*tq
  CAN2 -> BTR |= (11 << CAN_BTR_BRP_Pos);      // предделитель равен 12: 42 / 12 = 3.5 МГц частота тактирования CAN
  CAN2 -> BTR |= (9 << CAN_BTR_TS1_Pos);     // TS1 = 9, BS1 = 10
  CAN2 -> BTR |= (2 << CAN_BTR_TS2_Pos);      // TS2 = 2 , BS2 = 3

  CAN2->BTR &= ~(CAN_BTR_SILM | CAN_BTR_LBKM); // LOOP OFF, SILENT OFF
  //CAN2->BTR |= CAN_BTR_LBKM;   // добавить в CAN2_init() после настройки BTR

  // фильтрация по Frame ID
  // list mode
  // принимаем сообщения только с RX_FRAME_ID 0x567

  CAN1->FMR   |=  CAN_FMR_FINIT;            // режим инит фильтров
  CAN1->FM1R  |=  CAN_FM1R_FBM14;           // 14 банк фильтров ( 0-13 кан1, 14-28 кан2 )
  CAN1->FS1R  &= ~(CAN_FS1R_FSC14);         // 16 бит длина фильтра
  CAN1->FFA1R &= ~(CAN_FFA1R_FFA14);        // сохранение в FIFO0
  CAN1->sFilterRegister[14].FR1 = (CAN_RX_FRAME_LED_CONTROL <<5); // FRAME_ID фильтрая
  CAN1->sFilterRegister[14].FR2 = (CAN_RX_FRAME_LED_STATE <<5); // FRAME_ID фильтрая
  CAN1->FA1R  |=  (1<<CAN_FA1R_FACT14_Pos); // активируем фильтр 14
  CAN1->FMR   &= ~CAN_FMR_FINIT;            // режим инит выключаем  (фильтры включаются)

  CAN2->MCR &= ~(CAN_MCR_INRQ);             // кан2 инит выключаем (то есть модуль включаем)
  while((CAN2->MSR & CAN_MSR_INAK) !=0) {}; // ждем пока не активируется
}

uint8_t CAN2_Receive_msg(uint16_t *frame_ID, uint16_t *data_len_bytes, char rx_array[]) {
  if((CAN2->RF0R & CAN_RF0R_FMP0) != 0) { // FIFO не пустая?
    *frame_ID = ((CAN2 -> sFIFOMailBox[0].RIR >> CAN_RI0R_STID_Pos) & 0x0FFF);
    *data_len_bytes = ((CAN2 -> sFIFOMailBox[0].RDTR >> CAN_RDT0R_DLC_Pos) & 0x000F);

    for(uint16_t i=0; i< *data_len_bytes; i++) {
      if(i < 4) {
        rx_array[i] = ((CAN2 -> sFIFOMailBox[0].RDLR >> 8*i) & 0x00FF);
      } else {
        rx_array[i] = ((CAN2 -> sFIFOMailBox[0].RDHR >> 8*(i-4)) & 0x00FF);
      }
    }
    CAN2 -> RF0R |= CAN_RF0R_RFOM0; //освобождение fifo0
    return 0;
  } else {
    return 1; //fifo0 is empty! cant read
  }
}

uint8_t CAN2_Send_msg(const uint16_t frame_ID, const uint16_t data_len_bytes, const char tx_array[]) {

  if((CAN2-> TSR & CAN_TSR_TME0) == 0) { //mailbox0 пустой?
    return 1;                            //не пустой
  }

  CAN2 -> sTxMailBox[0].TIR = 0x0000;
  CAN2 -> sTxMailBox[0].TDTR = 0X0000;
  CAN2 -> sTxMailBox[0].TIR &= ~(CAN_TI0R_IDE);   // стандартный 11бит айди
  CAN2 -> sTxMailBox[0].TIR &= ~(CAN_TI0R_RTR);   // RTR - передача фрейма данных
  CAN2 -> sTxMailBox[0].TIR &= ~(CAN_TI0R_TXRQ);  // отключаем запрос на отправку
  
  // айди фрейма
  CAN2 -> sTxMailBox[0].TIR |= (frame_ID << 21); 
  // длина поля данных
  CAN2 -> sTxMailBox[0].TDTR |= ((data_len_bytes & 0x000F) << CAN_TDT0R_DLC_Pos);

  // заполняем данные фрейма
  CAN2 -> sTxMailBox[0].TDLR = 0x0000;
  CAN2 -> sTxMailBox[0].TDHR = 0x0000;
  for(uint16_t i=0; i<data_len_bytes; i++) {
    if(i<4) {
      CAN2->sTxMailBox[0].TDLR |= (tx_array[i] << 8*i);
    } else {
      CAN2->sTxMailBox[0].TDHR |= (tx_array[i] << 8*(i-4));
    }
  }
  
  // НАЧАТЬ ОТПРАВКУ СООБЩЕНИЯ
  CAN2->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;

  // RQCP - request completed?
  if((CAN2->TSR &CAN_TSR_RQCP0) == 0) {
    return ((CAN2->ESR & CAN_ESR_LEC) >> CAN_ESR_LEC_Pos); //КОД ОШИБКИ
  } else {
    CAN2->TSR |= CAN_TSR_RQCP0;
    return 0;
  }

} 