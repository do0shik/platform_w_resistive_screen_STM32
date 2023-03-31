#ifndef INC_MOTOR_CONTROL_H_
#define INC_MOTOR_CONTROL_H_

#include "ch.h"
#include "hal.h"

void init_driver_servo(void);
void set_servo_angle(uint8_t servo_num, uint16_t angle, bool direction);
void control_servos(void);
void pwmMotorChangeWidth(uint16_t width);


#endif /* INC_MOTOR_CONTROL_H_ */
