#ifndef MODBUS_H
#define MODBUS_H

#include "stm32f407xx.h"
#include "usart.h"
#include "gpio.h"
#include "crc16.h"
#include "timer.h"

#define LED1_PORT     GPIOE
#define LED1_PIN_NUM  13
#define BTN_PORT      GPIOE
#define BTN1_PIN_NUM  10


//----------- Modbus timer constants -----------------
#define USART_BAUD_USED		115200
#define USART_BYTE_TIME_US	(1000000 * 12) / USART_BAUD_USED 	// BYTE send in 12 bits maximum

#define DELAY_1_5_BYTE_US	( USART_BYTE_TIME_US * (1.5 + 1) )	// 2.5 bytes = 1.5 bytes pause + 1 byte reception
#define DELAY_3_5_BYTE_US	( USART_BYTE_TIME_US * (3.5 + 1) )	// 4.5 bytes = 3.5 bytes pause + 1 byte reception

//-------- internal modbus timers state codes -------------
#define MB_TIM_IDLE				0x00
#define MB_TIM_DONE				0x01
#define MB_TIM_STARTED			0x02


//-------- internal modbus reception state codes -------------
#define MB_RX_IDLE			0x00
#define MB_RX_DONE			0x01
#define MB_RX_STARTED			0x02


//---- Modbus command codes ------------
#define READ_COILS			0x01
#define READ_DISCRETE_INPUTS            0x02
#define READ_HOLDING_REG                0x03
#define READ_INPUT_REG                  0x04
#define WRITE_SINGLE_COIL		0x05	
#define WRITE_MULTI_COILS		0x0F

//-------- Modbus ERROR codes ----------
#define ERROR_OP_CODE			0x01
#define ERROR_DATA_ADDR			0x02
#define ERROR_DATA_VAL			0x03
#define ERROR_EXECUTION			0x04	
#define ERROR_05			0x05	// reserved
#define ERROR_06			0x06	// reserved
#define ERR_ANSWER_ADD			0x80	// add for answer command code

//-------- Internal ERROR Codes --------------
#define MODBUS_OK			0x00
#define ERROR_CRC			0x0F	// ошибка по CRC16 
#define ERROR_PACK_LEN			0x1F	// неверная длина пакета
#define MODBUS_RX_DONE			0x2F	// прием пакета завершен
#define ERROR_DEV_ADDR			0x3F	// неверный адрес устройства в пакете

//------- Modbus device address----------
#define DEVICE_ADDR			0xAD

//------Modbus internal addresses--------
// LEDS, BTNS
#define COILS_NUM			3	// LEDS
#define DISCRETE_INPUTS_NUM		3	// BTNS
#define HOLDING_REGS_NUM           	0	
#define INPUT_REGS_NUM           	1	// ADC

#define COIL_ON_CODE			0xFF00
#define COIL_OFF_CODE			0x0000





/******
Функция запуска таймера Modbus.
*******/
void ModbusTimerStart(uint16_t timer_cycles);


/*****
Ф-ия вызывается из прерываний TIM2_Handler. 
Отслеживает состояние таймеров timer35 И timer15 
*****/
void ModbusTimersIRQ(void);



/*****
Ф-ия приема байтов по протоколу Modbus и складывает их в глобальный массив ModbusRxArray[].
вызывается в прерываний от USART6
*****/
void ModbusReception(void);





/******
Ф-ия разбирает массив принятого пакета и выполняет требуемые операции.
В зависимости от кода операции по разному обрабатываются поле DATA
возвращает коды ошибок Modbus Error codes если были ошибки,
или MODBUS_OK, если операция выполнена успешно.
входные параметры - массив с запросом rx_request[] и длина этого массива request_len.
функция формирует массив для ответного пакета - tx_answer[] и длина его - answer_len . 
CRC16 также вычисляется для выходного пакета.
******/
uint8_t RequestParsingOperationExec(void);

//uint8_t rx_request[],		// received request array
//						uint8_t request_len,		// request array length in bytes
//						uint8_t tx_answer[],		// tx_answer array
//						uint8_t *answer_len			// answer array length in bytes
//						);





/*******
ф-ия возвращает код ошибки если полученный код операции не поддерживается
или возвращает MODBUS_OK если полученный код операции поддерживается 
в выходной параметр op_code_out сохраняется значение кода операции
*******/
uint8_t GetOperationCode(uint8_t rx_request[], uint8_t *op_code_out);
	
	
	


/********
Ф-ия возвращает код ошибки, если адрес данных больше чем адресуемых объектов в устройстве
или возвращает MODBUS_OK, если адресация данных верная.
*******/
uint8_t CheckDataAddress(uint8_t op_code, uint8_t rx_request[]);		




/********
Ф-ия возвращает код ошибки, если значение данных больше чем допустимый диапазон в устройстве
или возвращает MODBUS_OK, если значения данных верные.
*******/
uint8_t CheckDataValue(uint8_t op_code_in, uint8_t rx_request[]);





/*******
Ф-ия проверяет правильность поля DATA и выполняет команду по запросу.
	op_code			- код операции в принятом запросе
	rx_request[]	- массив запроса
	req_len,		- длина массива запроса
	tx_answer[]		- выходной массив ответа. Без CRC16
	*answer_len		- длина выходного массива ответа


*******/
uint8_t ExecOperation(uint8_t op_code, 
						uint8_t rx_request[], 
						uint8_t req_len, 
						uint8_t tx_answer[], 
						uint8_t *answer_len);
						
									




/********
Ф-ия выполняет операцию READ_COILS и возвращает код ошибки выполнения, либо MODBUS_OK, если все хорошо.
ответный пакет формируется в выходной параметр массив answer_tx[], НО БЕЗ CRC16! 
********/
uint8_t Exec_READ_COILS( uint16_t start_addr_in, 
							uint16_t quantity_in, 
							uint8_t answer_tx[],
							uint8_t *answer_len);





/********
Ф-ия выполняет операцию READ_DISCRETE_INPUTS и возвращает код ошибки выполнения, 
либо возвращает MODBUS_OK, если все хорошо.
ответный пакет формируется в выходной параметр массив answer_tx[], БЕЗ CRC16! 
********/
uint8_t Exec_READ_DISCRETE_INPUTS( uint16_t start_addr_in, 
							uint16_t quantity_in, 
							uint8_t answer_tx[],
							uint8_t *answer_len);

uint8_t Exec_READ_HOLDING_REG( uint16_t start_addr_in, 
							uint16_t quantity_in, 
							uint8_t answer_tx[],
							uint8_t *answer_len);


uint8_t Exec_READ_INPUT_REG( uint16_t start_addr_in, 
							uint16_t quantity_in, 
							uint8_t answer_tx[],
							uint8_t *answer_len);



/********
Ф-ия выполняет операцию WRITE_SINGLE_COIL и возвращает код ошибки выполнения, 
либо возвращает MODBUS_OK, если все хорошо.
ответный пакет формируется в выходной параметр массив answer_tx[], БЕЗ CRC16! 
********/
uint8_t Exec_WRITE_SINGLE_COIL( uint16_t start_addr_in, 
							uint16_t value_in, 
							uint8_t answer_tx[],
							uint8_t *answer_len);




/********
Ф-ия выполняет операцию WRITE_MULTI_COILS и возвращает код ошибки выполнения, 
либо возвращает MODBUS_OK, если все хорошо.
ответный пакет формируется в выходной параметр массив answer_tx[], БЕЗ CRC16! 
********/
uint8_t Exec_WRITE_MULTI_COILS(uint8_t rx_request[],
							uint8_t req_len, 
							uint8_t answer_tx[],
							uint8_t *answer_len);
		
		
		
										

/********
Ф-ия отправки ответного сообщения. 
либо отправка сообщения об ошибке/
По содержимому ответного сообщения посчитано CRC16 и добавлено в конец массива 
младший байт CRC16 идет первый, потом - старший.
********/
uint8_t AnswerTransmit(uint8_t err_code, uint8_t tx_array[], uint8_t *tx_array_len, uint8_t op_code);





#endif
