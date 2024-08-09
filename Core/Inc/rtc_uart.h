/*
 * uart.h
 *
 *  Created on: 1 Aug 2024
 *      Author: osonoderin
 */


#ifndef INC_RTC_UART_H_
#define INC_RTC_UART_H_
#include "main.h"
#include <stdint.h>
#include <stdio.h>
void uart_init(void);
void USART1_IRQHandler(void);
void uart_print(uint8_t data);
void uart_printn(float x);
void uart_printf(char *str);
extern char temp_uart_data;
//extern char value[10];



#endif /* INC_UART_H_ */
