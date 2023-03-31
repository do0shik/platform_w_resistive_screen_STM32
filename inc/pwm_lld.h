#ifndef INC_PWM_LLD_H_
#define INC_PWM_LLD_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

void pwm_init(void);
void pwmChangeWidth(uint16_t width);

#endif
