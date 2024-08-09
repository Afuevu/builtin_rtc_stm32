#ifndef INC_RTC_H_
#define INC_RTC_H_
#include "main.h"
#include <stdint.h>
#include <stdio.h>

//extern char value[10];
void rtc_init(void);
void rtc_wrtie(uint8_t hours, uint8_t minutes, uint8_t seconds);
void rtc_read(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

#endif /* INC_UART_H_ */
