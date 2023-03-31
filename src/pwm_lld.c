#include <pwm_lld.h>

static PWMDriver *pwm1Driver = &PWMD1;

PWMConfig pwm1conf = {
    .frequency = 1000000,  // 1MHz
    .period    = 2500,     // 2.5ms ~ 400Hz
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

void pwm_init(void)
{
  palSetLineMode(PAL_LINE(GPIOA, 8), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
  pwmStart(pwm1Driver, &pwm1conf);
}

void pwmChangeWidth(uint16_t width)
{
  pwmEnableChannel(pwm1Driver, 0, PWM_PERCENTAGE_TO_WIDTH(pwm1Driver, width));
}
