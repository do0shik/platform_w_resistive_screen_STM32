#ifndef INC_MOTOR_CONTROL_H_
#define INC_MOTOR_CONTROL_H_

#include "ch.h"
#include "hal.h"

#define DRIVER_PWM_FREQ 200000
#define PWM_MIN 1000 // минимальная длительность импульса ШИМ, мкс
#define PWM_MAX 2000 // максимальная длительность импульса ШИМ, мкс
#define SERVO_MIN_ANGLE_Y     95
#define SERVO_MAX_ANGLE_Y     165
#define SERVO_MIN_ANGLE_X     95
#define SERVO_MAX_ANGLE_X     195
#define SERVO_STEP    5

void init_motors(void);
void pwm_motors_ChangeWidth_A(uint16_t width);
void pwm_motors_ChangeWidth_B(uint16_t width);
void set_motor_LEFTdirection_A1(void);
void set_motor_RIGHTdirection_A2(void);
void set_motor_UPdirection_B1(void);
void set_motor_DOWNdirection_B2(void);
void disable_motors_A(void);
void disable_motors_B(void);



#endif /* INC_MOTOR_CONTROL_H_ */
