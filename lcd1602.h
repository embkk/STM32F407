#ifndef LCD1602_H
#define LCD1602_H

#include "stm32f407xx.h"
#include "delay.h"

//-------- LCD1602 pinout ---------------
//WARNING: Function LCD1602_PinsInit() must be edited, if pinout was changed.

#define RS_PORT		GPIOB
#define RW_PORT		GPIOD
#define E_PORT		GPIOE
#define DB7_PORT	GPIOC
#define DB6_PORT	GPIOE
#define DB5_PORT	GPIOE
#define DB4_PORT	GPIOE

#define RS_PIN_NUM	7
#define RW_PIN_NUM	4
#define E_PIN_NUM	1
#define DB7_PIN_NUM	13
#define DB6_PIN_NUM	6
#define DB5_PIN_NUM	5
#define DB4_PIN_NUM	4


//======= macros pins operations ===========
//-------- set pins to 1 -------------
#define RS_SET()	( RS_PORT->BSRR |= ( 1 << RS_PIN_NUM ) )
#define RW_SET()	( RW_PORT->BSRR |= ( 1 << RW_PIN_NUM ) )
#define E_SET()		( E_PORT->BSRR |= ( 1 << E_PIN_NUM ) )
#define DB7_SET()	( DB7_PORT->BSRR |= ( 1 << DB7_PIN_NUM ) )
#define DB6_SET()	( DB6_PORT->BSRR |= ( 1 << DB6_PIN_NUM ) )
#define DB5_SET()	( DB5_PORT->BSRR |= ( 1 << DB5_PIN_NUM ) )
#define DB4_SET()	( DB4_PORT->BSRR |= ( 1 << DB4_PIN_NUM ) )

//-------- clear pins to 0 -------------
#define RS_CLR()	( RS_PORT->BSRR |= ( 1 << ( RS_PIN_NUM + 16 ) ) )
#define RW_CLR()	( RW_PORT->BSRR |= ( 1 << ( RW_PIN_NUM + 16 ) ) )
#define E_CLR()		( E_PORT->BSRR |= ( 1 << ( E_PIN_NUM + 16 ) ) )
#define DB7_CLR()	( DB7_PORT->BSRR |= ( 1 << ( DB7_PIN_NUM + 16 ) ) )
#define DB6_CLR()	( DB6_PORT->BSRR |= ( 1 << ( DB6_PIN_NUM + 16 ) ) )
#define DB5_CLR()	( DB5_PORT->BSRR |= ( 1 << ( DB5_PIN_NUM + 16 ) ) )
#define DB4_CLR()	( DB4_PORT->BSRR |= ( 1 << ( DB4_PIN_NUM + 16 ) ) )

//-------- check DB7-DB4 -----------------
#define DB7_CHECK()	( DB7_PORT->IDR & ( 1 << DB7_PIN_NUM ) )
#define DB6_CHECK()	( DB6_PORT->IDR & ( 1 << DB6_PIN_NUM ) )
#define DB5_CHECK()	( DB5_PORT->IDR & ( 1 << DB5_PIN_NUM ) )
#define DB4_CHECK()	( DB4_PORT->IDR & ( 1 << DB4_PIN_NUM ) )


//-------- LCD1602 maximum symbols and strings number --------
#define LCD_CHAR_NUM_MAX	16
#define LCD_STRING_NUM_MAX	2


//------------ LCD1602 Instructions Codes -------------
#define CLEAR_DISPLAY			0x01
#define RETURN_HOME				0x02
								
#define ENTRY_MODE				0x04
#define MODE_INC				0x02
#define MODE_DEC				0x00
#define MODE_DISPLAY_SHIFT		0x01
								
#define DISPLAY_ON				0x0C
#define DISPLAY_OFF				0x08
#define CURSOR_ON				0x02
#define CURSOR_OFF				0x00
#define CURSOR_BLINK			0x01
								
#define CURSOR_SHIFT_LEFT		0x10
#define CURSOR_SHIFT_RIGHT		0x14
#define DISPLAY_SHIFT_LEFT		0x18
#define DISPLAY_SHIFT_RIGHT		0x1C
								
#define FUNC_SET				0x20
#define BITS_8					0x10					
#define BITS_4					0x00
#define LINES_1					0x00
#define LINES_2					0x08
#define DOTS_5x10				0x04
#define DOTS_5x8				0x00


#define E_CYCLE_US					10
#define LCD1602_WAIT_OPERATION_US	50



/****
	Ф-ия инициализации портов ввода-вывода для LCD1602
***/
//WARNING: если менятеся распиновка подключения LCD1602 к МК, 
// то в этой функции нужно править инициализацию тактирования портов GPIO.
void LCD1602_PinsInit4bits(void);



/*****
Ф-ия отправики старшей половины кода инструкции в индикатор LCD1602 4-х битный интерфейс
*****/
void LCD1602_SendHalfInstruction4bits(uint8_t InstructionCode);



/*****
Ф-ия отправики полного кода инструкции в индикатор LCD1602 4-х битный интерфейс
*****/
void LCD1602_SendFullInstruction4bits(uint8_t InstructionCode);

/****
	Ф-ия инициализации индикатора LCD1602 после включения питания
***/
void LCD1602_ScreenInit4bits(void);



/****
	Ф-ия отображения одного символа на индикаторе LCD1602
***/
void LCD1602_WriteChar4bits(uint8_t CharCode);



/****
	Ф-ия отображения строки или слова на индикаторе LCD1602
	если строка короче 16-ти символов то переноса автоматического нет 
***/
void LCD1602_WriteString4bits(uint8_t String[], uint8_t StringLen);





/******
	Ф-ия устанавливает адрес в памяти DDRAM куда будем писать символы. 
	Этот адрес показывает положение символа на экране LCD1602
	0x00 - 0x0F - первая строка
	0x40 - 0x4F - вторая строка
	И в эту же позицию на ЖК-индикаторе ставится курсор

	!!! bit 7 in NewAddress allways must be 1.
******/
void LCD1602_SetDDRAMAddress(uint8_t NewAddress);



void LCD1602_SetCGRAMAddress(uint8_t NewAddress);


/*****
	Функция читает Busy Flag из LCD1602 и возврвщает байт в котором:
	бит 7 = Busy Flag. 
	биты с 6 по 0 = AC
	Если Busy Flag = 1 значит LCD1602 занят выполнением текущей инструкции
	Если Busy Flag = 0 значит LCD1602 свободен для выполнения следующей инструкции
*****/
uint8_t LCD1602_ReadBusyFlagAC(void);

void LCD1602_WaitBusyFlag(void);


void LCD1602_CursorShow(void);

void LCD1602_CursorHide(void);

void LCD1602_CursorBlink_ON(void);

void LCD1602_CursorBlink_OFF(void);


#endif
