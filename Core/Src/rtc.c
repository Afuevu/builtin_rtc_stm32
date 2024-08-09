#include "rtc.h"

#define CR_DBP (1U<<8)
#define CSR_LSION (1U<<0)
#define CSR_LSIRDY (1U<<0)
#define BDCR_BDRST (1U<<16)
#define BDCR_RCCEN (1U<<15)
void rtc_init(void) {
	/* Enable clcck accss to PWR and BKPEN*/
	RCC->APB1ENR |= 1 << 28;
	RCC->APB1ENR |= 1 << 27;
	// Enable backup access t config RTC
	PWR->CR |= CR_DBP;
	//Enable low speed internal(LSi)
	RCC->CSR |= CSR_LSION;
	// wait for LSI to be ready
	while ((RCC->CSR & CSR_LSIRDY) != CSR_LSIRDY) {
	}
	//force backup domain reset
	RCC->BDCR |= BDCR_BDRST;
	//release backup domain reset
	RCC->BDCR &= ~BDCR_BDRST;
	//set rtc clock source to lsi
	RCC->BDCR &= ~(1U << 8);
	RCC->BDCR |= (1U << 9);
	//enable the rtc
	RCC->BDCR |= BDCR_RCCEN;

	// Ensure that the registers are synchronized
	RTC->CRL &= ~(1 << 3);
	while ((RTC->CRL & (1 << 3)) == 0) {
	}

	// set CNF bit to enter configuration mode
	RTC->CRL |= (1 << 4);

	/*// Set the prescaler to achieve 1 Hz from the 32.768 kHz LSE
	 RTC->PRLH = 0;
	 RTC->PRLL = 32767;*/

	// Set the prescaler to achieve 1 Hz from the 40 kHz LSE
	RTC->PRLH = 0;
	RTC->PRLL = 39999;

	//exit the configuration mode
	RTC->CRL &= ~(1 << 4);

	while ((RTC->CRL & (1 << 5)) == 0)
		;
}

void rtc_wrtie(uint8_t hours, uint8_t minutes, uint8_t seconds) {
	// check if the last write operation is sucessful
	while ((RTC->CRL & (1 << 5)) == 0)
		;

	// set CNF bit to enter configuration mode
	RTC->CRL |= (1 << 4);

	//set the time
	uint32_t time_in_seconds = (hours * 3600) + (minutes * 60) + seconds;

	RTC->CNTH = time_in_seconds >> 16;
	RTC->CNTL = time_in_seconds & 0xFFFF;

	//exit the configuration mode
	RTC->CRL &= ~(1 << 4);

	// check if the last write operation is sucessful
	while ((RTC->CRL & (1 << 5)) == 0)
		;

}

void rtc_read(uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
	uint32_t time_counter;

	// Read the RTC counter value
	time_counter = ((uint32_t) (RTC->CNTH << 16)) | RTC->CNTL;

	if (time_counter >= 86400) {
		time_counter %= 86400;
	}
	// Calculate hours, minutes, and seconds from the counter value
	*hours = (uint8_t) (time_counter / 3600);
	time_counter %= 3600;
	*minutes = (uint8_t) (time_counter / 60);
	*seconds = (uint8_t) (time_counter % 60);
}














