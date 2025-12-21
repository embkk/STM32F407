#include "modbus_rtu.h"

uint8_t timer15_state = MB_TIM_IDLE;
uint8_t timer35_state = MB_TIM_IDLE;
uint8_t ModbusRxState = MB_RX_IDLE;

uint8_t ModbusRxArray[256];		// global array for modbus request reception in USART interrupt
uint8_t RxByteNum;





void ModbusTimersIRQ(void){
	if(timer35_state == MB_TIM_STARTED){			// wait for 3.5 byte silent on the modbus bud
		timer35_state = MB_TIM_DONE;
		timer15_state = MB_TIM_IDLE;
		RxByteNum = 0;		// clear reception byte number
	}
	else{
		if(timer35_state == MB_TIM_DONE){
			if(timer15_state == MB_TIM_STARTED){		// end of Modbus request reception
				ModbusTimerStart(DELAY_3_5_BYTE_US);	// start timer45 for 3.5 bytes silent on modbus bus
				timer15_state = MB_TIM_DONE;
				ModbusRxState = MB_RX_DONE;
			}
			else{
				timer35_state = MB_TIM_IDLE;
				timer15_state = MB_TIM_IDLE;
			}
		}
		else{
			timer35_state = MB_TIM_IDLE;
			timer15_state = MB_TIM_IDLE;
		}
	}
}







void ModbusReception(void){
	
	uint8_t RxByte = USART6->DR;

	if(timer35_state == MB_TIM_STARTED){
		ModbusTimerStart(DELAY_3_5_BYTE_US);	// restart timer45
	}
	else{
		if(timer35_state == MB_TIM_DONE){	// если паузу на шине выждали и пришел байт по USART6
			
			if((timer15_state == MB_TIM_IDLE) || (timer15_state == MB_TIM_STARTED)){	// if timer15 not started or not done
																						//  receive data byte 
				
				if(RxByteNum < 255){
					ModbusRxArray[ RxByteNum ] = RxByte;	// read USART6 DR into ModbusRxArray[]
					RxByteNum++;
					ModbusTimerStart(DELAY_1_5_BYTE_US);	//restart timer15
					ModbusRxState = MB_RX_STARTED;
				}
				else{ // игнорируем слишком длинные пакеты. 
					timer15_state = MB_TIM_IDLE;
					ModbusTimerStart(DELAY_3_5_BYTE_US);	// start timer35 for bus pause wait
					ModbusRxState = MB_RX_IDLE;
				}
			}
			else{	// reception not started. Wait for bus pause.
				timer15_state = MB_TIM_IDLE;
				ModbusTimerStart(DELAY_3_5_BYTE_US);	// start timer35 for bus pause wait
				ModbusRxState = MB_RX_IDLE;
			}
		}
		else{
			ModbusTimerStart(DELAY_3_5_BYTE_US);	// start timer35 for bus pause wait
		}
	}
}




void ModbusTimerStart(uint16_t timer_cycles){
	TIM2_Start(timer_cycles);
	if(timer_cycles == DELAY_1_5_BYTE_US) timer15_state = MB_TIM_STARTED;
	else{
		if(timer_cycles == DELAY_3_5_BYTE_US) timer35_state = MB_TIM_STARTED;
	}
}





uint8_t GetOperationCode(uint8_t rx_request[], uint8_t *op_code_out){
	uint8_t op_code_rx = rx_request[1];

	*op_code_out = op_code_rx;

	if(( op_code_rx == READ_COILS ) ||
		( op_code_rx == READ_DISCRETE_INPUTS ) ||
		( op_code_rx == WRITE_SINGLE_COIL ) ||
		( op_code_rx == WRITE_MULTI_COILS ) ){

		return MODBUS_OK;
	} 
	else {
		return ERROR_OP_CODE;
		}
}




uint8_t CheckDataAddress(uint8_t op_code_in, uint8_t rx_request[]){
	uint16_t start_addr_rx = (rx_request[2] << 8) + rx_request[3];
	
	switch(op_code_in){
	case(READ_COILS):
		if((start_addr_rx >= 0) && (start_addr_rx < COILS_NUM)){
			return MODBUS_OK;
		}
		break;

	case(READ_DISCRETE_INPUTS):
		if((start_addr_rx >= 0) && (start_addr_rx < DISCRETE_INPUTS_NUM)){
			return MODBUS_OK;
		}
		break;


	case(WRITE_SINGLE_COIL):
		if((start_addr_rx >= 0) && (start_addr_rx < COILS_NUM)){
			return MODBUS_OK;
		}
		break;

	case(WRITE_MULTI_COILS):
		if((start_addr_rx >= 0) && (start_addr_rx < COILS_NUM)){
			return MODBUS_OK;
		}
		break;

	}
	return ERROR_DATA_ADDR;

}


/*
	дискретный выход с номером 1 адресуется как 0.
*/
uint8_t CheckDataValue(uint8_t op_code_in, uint8_t rx_request[]){
	uint16_t start_addr_rx = (rx_request[2] << 8) + rx_request[3];
	uint16_t quantity_rx = (rx_request[4] << 8) + rx_request[5];
	uint16_t rx_data_range = start_addr_rx + quantity_rx;

	uint16_t wr_data_coil = (rx_request[4] << 8) + rx_request[5];
	uint16_t wr_addr_coil = (rx_request[2] << 8) + rx_request[3];

	switch(op_code_in){
	case(READ_COILS):
		if((rx_data_range >= 0) && (rx_data_range <= COILS_NUM)){
			return MODBUS_OK;
		}
		else return ERROR_DATA_VAL;
		break;

	case(READ_DISCRETE_INPUTS):
		if((rx_data_range > 0) && (rx_data_range <= DISCRETE_INPUTS_NUM)){
			return MODBUS_OK;
		}
		else return ERROR_DATA_VAL;
		break;


	case(WRITE_SINGLE_COIL):
		if((wr_data_coil == COIL_OFF_CODE) || (wr_data_coil == COIL_ON_CODE) && (wr_addr_coil < COILS_NUM)){
				return MODBUS_OK;
		}
		else return ERROR_DATA_VAL;
		break;

	case(WRITE_MULTI_COILS):
		if((rx_data_range > 0) && (rx_data_range <= COILS_NUM)){
			return MODBUS_OK;
		}
		else return ERROR_DATA_VAL;
		break;

	}


}



uint8_t Exec_READ_COILS( uint16_t start_addr_in, 
							uint16_t quantity_in, 
							uint8_t answer_tx[],
							uint8_t *answer_len){
	uint8_t bytes_num = 1;
	uint8_t Value_D0 = (((LED1_PORT -> ODR) & 0xE000) >> (LED1_PIN_NUM + start_addr_in));	// 0xE0 = pins 13 - 15 masked
	
	answer_tx[0] = DEVICE_ADDR;
	answer_tx[1] = READ_COILS;
	answer_tx[2] = bytes_num;
	answer_tx[3] = Value_D0;
	*answer_len = bytes_num + 3; // answer_len = all listed bytes, without CRC16 bytes

	return MODBUS_OK;

}




uint8_t Exec_READ_DISCRETE_INPUTS( uint16_t start_addr_in, 
							uint16_t quantity_in, 
							uint8_t answer_tx[],
							uint8_t *answer_len){

	uint8_t bytes_num = 1;
	
	uint8_t Value_D0 = (((BTN_PORT -> IDR) & 0x1C00) >> (BTN1_PIN_NUM + start_addr_in));	// 0x1C00 = pins 10 - 12 masked

	answer_tx[0] = DEVICE_ADDR;
	answer_tx[1] = READ_DISCRETE_INPUTS;
	answer_tx[2] = bytes_num;
	answer_tx[3] = Value_D0;
	*answer_len = bytes_num + 3; // answer_len = all listed bytes, without CRC16 bytes

	return MODBUS_OK;

}







/*
	выход с номером 1 адресуется как 0.
*/
uint8_t Exec_WRITE_SINGLE_COIL( uint16_t start_addr_in, 
							uint16_t value_in, 
							uint8_t answer_tx[],
							uint8_t *answer_len){
	uint8_t bytes_num = 1;
	if(value_in == COIL_ON_CODE){
		LED1_PORT -> ODR |= ( 1 << ( LED1_PIN_NUM + start_addr_in ) );	// put 1 to LED_pin 
		
		answer_tx[0] = DEVICE_ADDR;
		answer_tx[1] = WRITE_SINGLE_COIL;
		answer_tx[2] = ( start_addr_in >> 8 );
		answer_tx[3] = ( start_addr_in & 0x00FF );
		answer_tx[4] = ( value_in >> 8 );
		answer_tx[5] = ( value_in & 0x00FF );
	
		*answer_len = 6;

		return MODBUS_OK;

	}
	else{
		if(value_in == COIL_OFF_CODE){
			LED1_PORT -> ODR &= ~( 1 << ( LED1_PIN_NUM + start_addr_in ) );	// put 0 to LED_pin 

			answer_tx[0] = DEVICE_ADDR;
			answer_tx[1] = WRITE_SINGLE_COIL;
			answer_tx[2] = ( start_addr_in >> 8 );
			answer_tx[3] = ( start_addr_in & 0x00FF );
			answer_tx[4] = ( value_in >> 8 );
			answer_tx[5] = ( value_in & 0x00FF );
			
			*answer_len = 6;

			return MODBUS_OK;

		}
		else return ERROR_EXECUTION;
	}
}






uint8_t Exec_WRITE_MULTI_COILS(uint8_t rx_request[],
							uint8_t req_len, 
							uint8_t answer_tx[],
							uint8_t *answer_len){
	
	uint16_t start_addr_in = ( rx_request[2] << 8 ) +  rx_request[3];
	uint16_t quantity_rx = ( rx_request[4] << 8 ) +  rx_request[5];
	
	uint8_t bytes_num = rx_request[6];

	uint8_t CoilsPortValue = rx_request[7] << (start_addr_in); // (XOR ^) inversion couse LEDs turned by zero.

	uint16_t turn_on_coils_num = 0;

	LED1_PORT->ODR = ( CoilsPortValue << LED1_PIN_NUM );
	
	answer_tx[0] = DEVICE_ADDR;
	answer_tx[1] = WRITE_MULTI_COILS;
	answer_tx[2] = ( start_addr_in >> 8 );
	answer_tx[3] = ( start_addr_in & 0x00FF );
	answer_tx[4] = 0;
	answer_tx[5] = quantity_rx;
	
	*answer_len = 6;

	return MODBUS_OK;
}






uint8_t ExecOperation(uint8_t op_code, 
						uint8_t rx_request[], 
						uint8_t req_len, 
						uint8_t tx_answer[], 
						uint8_t *answer_len){
	
	uint16_t start_addr_rx = (rx_request[2] << 8) + rx_request[3];
	uint16_t quantity_rx = (rx_request[4] << 8) + rx_request[5];
	uint8_t bytes_number_rx;
	uint8_t err;
	uint8_t answer_array[256];
	uint8_t array_answer_len = 0;

			
	// для каждого case написать свою функцию выполнения операции		
	switch(op_code){
	case(READ_COILS):
		err = Exec_READ_COILS(start_addr_rx, quantity_rx, answer_array, &array_answer_len);
		break;

	case(READ_DISCRETE_INPUTS):
		err = Exec_READ_DISCRETE_INPUTS(start_addr_rx, quantity_rx, answer_array, &array_answer_len);
		break;


	case(WRITE_SINGLE_COIL):
		err = Exec_WRITE_SINGLE_COIL(start_addr_rx, quantity_rx, answer_array, &array_answer_len);
		break;

	case(WRITE_MULTI_COILS):
		err = Exec_WRITE_MULTI_COILS(rx_request, req_len, answer_array, &array_answer_len);
		break;

	}
	
	*answer_len = array_answer_len;
	for(uint8_t i=0; i < array_answer_len; i++) 
		tx_answer[i] = answer_array[i]; // copy answer_array into tx_answer
	
	return err;
}


// Адрес данных верный?
// Значение данных верное? В нашем диапазоне?
// Выполнение требуемой операции
// вычисление CRC16 для ответного пакета
// формирование ответного пакета
uint8_t RequestParsingOperationExec(void){ 
//uint8_t rx_request[], 
//						uint8_t request_len,
//						uint8_t tx_answer[], 
//						uint8_t *answer_len )
						//{

	uint8_t err;
	uint16_t crc;
	uint16_t crc_rx;
	uint8_t op_code_rx;
	uint8_t tx_answer_tmp[256];
	uint8_t answer_len_tmp;

	uint8_t RxArraySafe[256];		// safe array for modbus request reception
	uint8_t RxByteNumSafe;


	if(ModbusRxState == MB_RX_DONE){

		RxByteNumSafe = RxByteNum;
		for(uint8_t i = 0; i < RxByteNumSafe; i++){	// save received request into internal array
			RxArraySafe[i] = ModbusRxArray[i];
		}
		
		// if Device Address match and packet length is not short
		if( (RxArraySafe[0] == DEVICE_ADDR) && (RxByteNumSafe > 4) ){	
			
			crc_rx = (RxArraySafe[((RxByteNumSafe) - 1)] << 8) + (RxArraySafe[((RxByteNumSafe) - 2)] & 0x00FF);
			// CRC16 compare
			crc = CRC16_Calc(RxArraySafe, ((RxByteNumSafe) - 2));
			
			if(crc == crc_rx) {		// Get OperationCode value
				err = GetOperationCode(RxArraySafe, &op_code_rx);
				
				if(err == MODBUS_OK){	// check data address 
					err = CheckDataAddress(op_code_rx, RxArraySafe);
					
					if(err == MODBUS_OK){	// check data value
						err = CheckDataValue(op_code_rx, RxArraySafe); 

						if(err == MODBUS_OK){	// operation execution
							err = ExecOperation(op_code_rx, RxArraySafe, RxByteNumSafe, tx_answer_tmp, &answer_len_tmp);
						}
					}
				}
			}
			else{ 
				err = ERROR_CRC;
			}
		
			AnswerTransmit(err, tx_answer_tmp, &answer_len_tmp, op_code_rx);
			return err;
		}
		else{ 
			err = ERROR_DEV_ADDR;
		}	// if dev_address
	}	// if ModbusRxState == DONE
	
	

	return err;
}


// answer array assebmly, CRC16 calculation
uint8_t AnswerTransmit(uint8_t err_code, uint8_t tx_array[], uint8_t *tx_array_len, uint8_t op_code){
	uint16_t crc_calc;
	
	if(err_code != MODBUS_OK){
		tx_array[1] = op_code + ERR_ANSWER_ADD;
		tx_array[2] = err_code;
		*tx_array_len = 3; // CRC16 2-bytes will be calculated later
	}

	crc_calc = CRC16_Calc(tx_array, *tx_array_len);		// answer CRC16 calculation
		
	tx_array[*tx_array_len] = (crc_calc & 0x00FF);		// CRC16 LSB send first 
	tx_array[*tx_array_len+1] = (crc_calc >> 8);			// CRC16 MSB send last
	
	USART_send_bytes(USART6, tx_array, (*tx_array_len+2) );
	
	ModbusRxState = MB_RX_IDLE;

	return MODBUS_OK;

}



