#ifndef INC_MOTOR_CONTROL_H_
#define INC_MOTOR_CONTROL_H_

#include "ch.h"
#include "hal.h"

void init_motors(void);
void pwm_motors_ChangeWidth_A(uint16_t width);
void pwm_motors_ChangeWidth_B(uint16_t width);
void set_motor_DOWNdirection_A1(void);
void set_motor_UPdirection_A2(void);
void set_motor_DOWNdirection_B1(void);
void set_motor_UPdirection_B2(void);
void disable_motors_A(void);
void disable_motors_B(void);
void enable_motors_A(void);
void enable_motors_B(void);



#endif /* INC_MOTOR_CONTROL_H_ */
