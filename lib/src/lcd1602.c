#include "lcd1602.h"



void LCD1602_PinsInit4bits(void){
	//-------- GPIO ports ckock enable --------
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

	//------ pins output mode enable ------------
	RS_PORT -> MODER |= (1 << RS_PIN_NUM*2);
	RW_PORT -> MODER |= (1 << RW_PIN_NUM*2);
	E_PORT -> MODER |= (1 << E_PIN_NUM*2);

	DB7_PORT -> MODER |= (1 << DB7_PIN_NUM*2);
	DB6_PORT -> MODER |= (1 << DB6_PIN_NUM*2);
	DB5_PORT -> MODER |= (1 << DB5_PIN_NUM*2);
	DB4_PORT -> MODER |= (1 << DB4_PIN_NUM*2);
	
	RS_CLR();
	RW_CLR();
}





void LCD1602_SendHalfInstruction4bits(uint8_t InstructionCode){
	RS_CLR();
	RW_CLR();
	E_SET();
	//----- Set half byte onto DB7-DB4 bus --------
	if(InstructionCode & 0x80) DB7_SET();
	else DB7_CLR();
	
	if(InstructionCode & 0x40) DB6_SET();
	else DB6_CLR();
	
	if(InstructionCode & 0x20) DB5_SET();
	else DB5_CLR();
	
	if(InstructionCode & 0x10) DB4_SET();
	else DB4_CLR();
	
	Delay_us( E_CYCLE_US/2 );
	E_CLR();		// latch half byte into LCD1602
	
	Delay_us( E_CYCLE_US/2 );
	RW_SET();
}






void LCD1602_SendFullInstruction4bits(uint8_t InstructionCode){
	uint8_t LocalCode = InstructionCode;

	for(uint8_t i = 0; i < 2; i++){
		LCD1602_SendHalfInstruction4bits( LocalCode );
		LocalCode = LocalCode << 4;	// shift InstructionCode for second half byte send into LCD1602
	}

	RW_SET();
}





// Datasheet HD44780U PAGE 46 
void LCD1602_ScreenInit4bits(void){

	Delay_ms(20);
	LCD1602_SendHalfInstruction4bits( FUNC_SET | BITS_8);

	Delay_ms(5);
	LCD1602_SendHalfInstruction4bits( FUNC_SET | BITS_8);

	Delay_us(300);
	LCD1602_SendHalfInstruction4bits( FUNC_SET | BITS_8);
	Delay_us(LCD1602_WAIT_OPERATION_US);

	LCD1602_SendHalfInstruction4bits( FUNC_SET | BITS_4);
	Delay_us(LCD1602_WAIT_OPERATION_US);
	
	LCD1602_SendFullInstruction4bits( FUNC_SET | BITS_4 | LINES_2 | DOTS_5x8);
	Delay_us(LCD1602_WAIT_OPERATION_US);
	
	LCD1602_SendFullInstruction4bits( DISPLAY_OFF );	// display OFF
	Delay_us(LCD1602_WAIT_OPERATION_US);

	LCD1602_SendFullInstruction4bits( CLEAR_DISPLAY );
	Delay_us(LCD1602_WAIT_OPERATION_US);

	LCD1602_SendFullInstruction4bits( ENTRY_MODE | MODE_INC );
	Delay_ms(5);

	LCD1602_SendFullInstruction4bits( DISPLAY_ON | CURSOR_ON );	// display ON
	Delay_us(LCD1602_WAIT_OPERATION_US); 
}


void LCD1602_WriteChar4bits(uint8_t CharCode){
	uint8_t DataByte = CharCode;
	
	RS_SET();
	RW_CLR();
	
	for(uint8_t i = 0; i < 2; i++){
		E_SET();
		//----- Set half byte onto DB7-DB4 bus --------
		if(DataByte & 0x80) DB7_SET();
		else DB7_CLR();
		
		if(DataByte & 0x40) DB6_SET();
		else DB6_CLR();
		
		if(DataByte & 0x20) DB5_SET();
		else DB5_CLR();
		
		if(DataByte & 0x10) DB4_SET();
		else DB4_CLR();
		
		Delay_us( E_CYCLE_US/2 );
		E_CLR();					// latch half byte into LCD1602
		
		Delay_us( E_CYCLE_US/2 );

		DataByte = DataByte << 4;
	}
	
	Delay_us(LCD1602_WAIT_OPERATION_US);
}




void LCD1602_WriteString4bits(char String[], char StringLen){
	for(uint8_t i = 0; i < StringLen; i++){
		LCD1602_WriteChar4bits(String[i]);
                Delay_us(LCD1602_WAIT_OPERATION_US);
	}
	
}





// !!! bit 7 in NewAddress allways must be 1.
void LCD1602_SetDDRAMAddress(uint8_t NewAddress){
	uint8_t DDR_Address = ( NewAddress | 0x80 );
       // for (int i = 0; i<10000;i++);
       Delay_us(LCD1602_WAIT_OPERATION_US);
	LCD1602_SendFullInstruction4bits( DDR_Address );

}



// !!! bit 6 in NewAddress allways must be 1.
void LCD1602_SetCGRAMAddress(uint8_t NewAddress){
	uint8_t CGR_Address = ( NewAddress | 0x40 );
	LCD1602_SendFullInstruction4bits( CGR_Address );
}




uint8_t LCD1602_ReadBusyFlagAC(void){
	uint8_t RxByte = 0;
	
	//------ switch Data bus into input mode------
	DB7_PORT-> MODER &= ~(3 << (DB7_PIN_NUM*2));
	DB6_PORT-> MODER &= ~(3 << (DB6_PIN_NUM*2));
	DB5_PORT-> MODER &= ~(3 << (DB5_PIN_NUM*2));
	DB4_PORT-> MODER &= ~(3 << (DB4_PIN_NUM*2));

	RS_CLR();
	RW_SET();
	
	for(uint8_t i = 0; i < 2; i++){
		E_SET();
		Delay_us( E_CYCLE_US/2 );
		//----- Set high half byte onto DB7-DB4 bus --------
		if( DB7_CHECK() ) RxByte = RxByte | 0x08;
		if( DB6_CHECK() ) RxByte = RxByte | 0x04;
		if( DB5_CHECK() ) RxByte = RxByte | 0x02;
		if( DB4_CHECK() ) RxByte = RxByte | 0x01;
		
		E_CLR();					// latch high half byte into LCD1602
		Delay_us( E_CYCLE_US/2 );
		
		if(i == 0) RxByte = ( RxByte << 4 ) & 0xF0;
	}
	
	//------ switch Data bus into output mode------
	DB7_PORT-> MODER |= (1 << (DB7_PIN_NUM*2));
	DB6_PORT-> MODER |= (1 << (DB6_PIN_NUM*2));
	DB5_PORT-> MODER |= (1 << (DB5_PIN_NUM*2));
	DB4_PORT-> MODER |= (1 << (DB4_PIN_NUM*2));

	return RxByte;
}



void LCD1602_WaitBusyFlag(void){
	uint8_t BF_AC = 0;
	while(! ( BF_AC & 0x80) ){
		BF_AC = LCD1602_ReadBusyFlagAC();
	}
}



void LCD1602_CursorShow(void){
	LCD1602_SendFullInstruction4bits( DISPLAY_ON | CURSOR_ON );
	Delay_us(LCD1602_WAIT_OPERATION_US);
	
}




void LCD1602_CursorHide(void){
	LCD1602_SendFullInstruction4bits( DISPLAY_ON | CURSOR_OFF );
	Delay_us(LCD1602_WAIT_OPERATION_US);

}





void LCD1602_CursorBlink_ON(void){
	LCD1602_SendFullInstruction4bits( DISPLAY_ON | CURSOR_ON | CURSOR_BLINK );
	Delay_us(LCD1602_WAIT_OPERATION_US);

}





void LCD1602_CursorBlink_OFF(void){
	LCD1602_SendFullInstruction4bits( DISPLAY_ON | CURSOR_ON );
	Delay_us(LCD1602_WAIT_OPERATION_US);

}



