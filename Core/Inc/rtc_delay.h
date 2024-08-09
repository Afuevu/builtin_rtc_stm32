/*
 * custom_delay.h
 *
 *  Created on: 1 May 2024
 *      Author: osonoderin
 */

#ifndef INC_RTC_DELAY_H_
#define INC_RTC_DELAY_H_

#include <stdio.h>
#include <stdint.h>
#include "main.h"

void delay_ms(int ms);
void delay_us(int us);
void TIM4_IRQHandler(void);
void timer4_Init(void);

#endif /* INC_CUSTOM_DELAY_H_ */
