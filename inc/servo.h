#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

typedef struct {
  float ADC_ANGLE_X;
  float ADC_ANGLE_Y;
}adc_t;

void motor_location_init(void);
void motor_location_read (uint16_t *adcservobuf);
void ADC_to_angle_transform(uint16_t *adcservobuf, adc_t *str);

#endif /* INC_SERVO_H_ */
