#ifndef INC_TEST_ADC_H_
#define INC_TEST_ADC_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

void adc_init(void);
void adc_read (uint16_t *adcbuf);


#endif /* INC_TEST_ADC_H_ */
