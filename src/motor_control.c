#include <motor_control.h>
#include <servo.h>
#include <math.h>

static PWMDriver *pwm1Driver = &PWMD1;

PWMConfig pwmAconf = {
    .frequency = DRIVER_PWM_FREQ,  // 1MHz
    .period    = 10000,     // 2.5ms ~ 400Hz
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

PWMConfig pwmBconf = {
    .frequency = DRIVER_PWM_FREQ,  // 1MHz
    .period    = 10000,     // 2.5ms ~ 400Hz
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

void init_motors(void){

    // PWM A
    palSetLineMode(PAL_LINE(GPIOA, 9), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    pwmStart(pwm1Driver, &pwmAconf);  // ШИМ на A

    palSetLineMode(PAL_LINE(GPIOA, 11), PAL_MODE_OUTPUT_PUSHPULL); // EN1
    palSetLineMode(PAL_LINE(GPIOA, 8), PAL_MODE_OUTPUT_PUSHPULL); // AIN1
    palSetLineMode(PAL_LINE(GPIOB, 9), PAL_MODE_OUTPUT_PUSHPULL); //AIN2

//    palSetLine(PAL_LINE(GPIOA, 11)); //EN2

//     PWM B
    palSetLineMode(PAL_LINE(GPIOA, 10), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    pwmStart(pwm1Driver, &pwmAconf);  // ШИМ на B

    palSetLineMode(PAL_LINE(GPIOB, 15), PAL_MODE_OUTPUT_PUSHPULL); //EN2
    palSetLineMode(PAL_LINE(GPIOB, 14), PAL_MODE_OUTPUT_PUSHPULL); //BIN1
    palSetLineMode(PAL_LINE(GPIOB, 13), PAL_MODE_OUTPUT_PUSHPULL); //BIN2

//    palSetLine(PAL_LINE(GPIOB, 15)); // вкл EN2
}

void pwm_motors_ChangeWidth_A(uint16_t width)
{
  pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, width));
}

void pwm_motors_ChangeWidth_B(uint16_t width)
{
  pwmEnableChannel(&PWMD1, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, width));
}

void disable_motors_A(void){
  palClearLine(PAL_LINE(GPIOA, 11)); //выкл EN2
}

void disable_motors_B(void){
  palClearLine(PAL_LINE(GPIOB, 15)); //выкл EN2
}

void set_motor_LEFTdirection_A1(void){
  palSetLine(PAL_LINE(GPIOA, 9));  // вкл серво A
  palSetLine(PAL_LINE(GPIOA, 11)); //вкл EN2
  // направление 2 для A (влево)
  palClearPad(GPIOB, 9); //AIN1
  palSetLine(PAL_LINE(GPIOA, 8)); //AIN2
}

void set_motor_RIGHTdirection_A2(void){
  palSetLine(PAL_LINE(GPIOA, 9));  // вкл серво A
  palSetLine(PAL_LINE(GPIOA, 11)); //вкл EN2
  // направление 1 для A (вправо)
  palClearPad(GPIOA, 8); //AIN1
  palSetLine(PAL_LINE(GPIOB, 9)); //AIN2
}

void set_motor_UPdirection_B1(void){
  palSetLine(PAL_LINE(GPIOA, 10));
  palSetLine(PAL_LINE(GPIOB, 15)); //EN2
  // направление 1 для B (вверх)
  palClearPad(GPIOB, 13); //BIN1
  palSetLine(PAL_LINE(GPIOB, 14)); //BIN2
}

void set_motor_DOWNdirection_B2(void){
  palSetLine(PAL_LINE(GPIOA, 10));
  palSetLine(PAL_LINE(GPIOB, 15)); //EN2
  // направление 2 для B (вниз)
  palClearPad(GPIOB, 14); //BIN1
  palSetLine(PAL_LINE(GPIOB, 13)); //BIN2
}






