#include <motor_control.h>
#include <servo.h>
#include <math.h>

#define SERVO_X_NUM 1
#define SERVO_Y_NUM 2
#define DRIVER_PWM_FREQ 200000
#define PWM_MIN 1000 // минимальная длительность импульса ШИМ, мкс
#define PWM_MAX 2000 // максимальная длительность импульса ШИМ, мкс
#define SERVO_MIN_ANGLE_Y     95
#define SERVO_MAX_ANGLE_Y     165
#define SERVO_MIN_ANGLE_X     95
#define SERVO_MAX_ANGLE_X     195
#define SERVO_STEP    5

static PWMDriver *pwm1Driver = &PWMD1;

PWMConfig pwm2conf = {
    .frequency = DRIVER_PWM_FREQ,  // 1MHz
    .period    = 10000,     // 2.5ms ~ 400Hz
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

void init_driver_servo(void) {
    pwmStart(pwm1Driver, &pwm2conf); // Инициализация PWM
//    palSetLineMode(PAL_LINE(GPIOA, 8), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
//    palSetLineMode(PAL_LINE(GPIOA, 9), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
}

void pwmMotorChangeWidth(uint16_t width)
{
  pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, width));
}


//void control_servos(void) {
//  static uint16_t servo_x_angle = SERVO_MIN_ANGLE_X;
//  static uint16_t servo_y_angle = SERVO_MIN_ANGLE_Y;
//  static bool servo_x_direction = true;
//  static bool servo_y_direction = true;
//  static bool servo1_initialized = false;
//  static bool servo2_initialized = false;
//
//  if (!servo1_initialized) {
//      if (servo_x_angle <= SERVO_MIN_ANGLE_X) {
//        servo_x_direction = true;
//      } else if (servo_x_angle >= SERVO_MAX_ANGLE_X) {
//        servo_x_direction = false;
//      }
//      servo1_initialized = true;
//  }
//  if (!servo2_initialized) {
//      if (servo_y_angle <= SERVO_MIN_ANGLE_Y) {
//        servo_y_direction = true;
//      } else if (servo_y_angle >= SERVO_MAX_ANGLE_Y) {
//        servo_y_direction = false;
//      }
//      servo2_initialized = true;
//  }
//
//    if (servo_x_direction) {
//        servo_x_angle += SERVO_STEP;
//        if (servo_x_angle >= SERVO_MAX_ANGLE_X) {
//            servo_x_angle = SERVO_MAX_ANGLE_X;
//            servo_x_direction = false;
//        }
//    } else {
//        servo_x_angle -= SERVO_STEP;
//        if (servo_x_angle <= SERVO_MIN_ANGLE_X) {
//            servo_x_angle = SERVO_MIN_ANGLE_X;
//            servo_x_direction = true;
//        }
//    }
//
//    if (servo_y_direction) {
//        servo_y_angle += SERVO_STEP;
//        if (servo_y_angle >= SERVO_MAX_ANGLE_Y) {
//            servo_y_angle = SERVO_MAX_ANGLE_Y;
//            servo_y_direction = false;
//        }
//    } else {
//        servo_y_angle -= SERVO_STEP;
//        if (servo_y_angle <= SERVO_MIN_ANGLE_Y) {
//            servo_y_angle = SERVO_MIN_ANGLE_Y;
//            servo_y_direction = true;
//        }
//    }
//    set_servo_angle(SERVO_X_NUM, servo_x_angle, false);
//    set_servo_angle(SERVO_Y_NUM, servo_y_angle, false);
//}
//
//void set_servo_angle(uint8_t servo_num, uint16_t angle, bool direction) {
//
//    // Преобразование угла поворота в соответствующую длительность импульса (мин. ширина испульса 1000мкс + пересчет угла в мкс)
//    int pulse_width =  PWM_MIN + angle * (PWM_MAX - PWM_MIN)/ 80;
//
////    //Если нужно изменить направление поворота, меняем местами минимальную и максимальную длительности импульса
////    if (direction) {
////           pulse_width = PWM_MAX - pulse_width;
////    }
//
//    // Ограничение длительности импульса ШИМ в диапазоне PWM_MIN - PWM_MAX
//    if (pulse_width < PWM_MIN) {
//        pulse_width = PWM_MIN;
//    } else if (pulse_width > PWM_MAX) {
//        pulse_width = PWM_MAX;
//    }
//
//    switch (servo_num) {
//       case 1:
//           pwmEnableChannel(pwm1Driver, 0, PWM_PERCENTAGE_TO_WIDTH(pwm1Driver, pulse_width));
//           break;
//       case 2:
//           pwmEnableChannel(pwm1Driver, 1, PWM_PERCENTAGE_TO_WIDTH(pwm1Driver, pulse_width));
//           break;
//       default:
//           break;
//   }
//}

