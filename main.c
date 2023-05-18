#include "ch.h"
#include "hal.h"
#include <motor_control.h>
#include <uart_lld.h>
#include <test_adc.h>
#include <servo.h>
#include <coord_transform.h>
#include <string.h>
#include <dependenceXY_angle.h>

uint16_t servo_num = 1;
uint16_t angle = 0;
static uint16_t adcbuf[2] = {0};
adcsample_t  adcservobuf[2] = {0};
float start_angle_X = 0;
float start_angle_Y = 0;

int main(void) {

  halInit();
  chSysInit();
  adc_init();
  init_motors();
  debug_stream_init();
  dbgprintf("start\n\r");

  circular_t circular = {
    .X = {0},
    .Y = {0},
    .start = -1,
    .current = 0,
  };

  coordinates_t p = {
    .X = 0,
    .Y = 0,
  };

  coordinates_t coord = {
    .X = 0,
    .Y = 0,
  };

  adc_t d = {
    .ADC_ANGLE_X = 0,
    .ADC_ANGLE_Y = 0,
  };

  palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_OPENDRAIN);
  palSetLineMode(PAL_LINE(GPIOA, 7), PAL_MODE_INPUT_ANALOG);
  palSetLineMode(PAL_LINE(GPIOA, 5), PAL_MODE_INPUT_ANALOG);
  pwm_motors_ChangeWidth_A(1000);
  pwm_motors_ChangeWidth_B(1000);

  while(1)
  {
    processing_flags(get_flag_dirA1(),
                     get_flag_dirA2(),
                     get_flag_dirB1(),
                     get_flag_dirB2());
    screenControl(&circular, &coord);

   /* Положение мотора XY*/
    motor_location_read(&adcservobuf[0]);
    dbgprintf("angleX - %.3f angleY - %.3f\n\r",
              d.ADC_ANGLE_X, d.ADC_ANGLE_Y);
    dbgprintf("angle1 - %d angle2 - %d \n\r",
              adcservobuf[0], adcservobuf[1]);

    dbgprintf("FLAG_A1 = %d FLAG_A2 = %d\n\r"
              "FLAG_B1 = %d FLAG_B2 = %d\n\r",
              get_flag_dirA1(), get_flag_dirA2(),
              get_flag_dirB1(), get_flag_dirB2());

    /*Ось X*/
    X_axis();
    palSetLineMode( PAL_LINE(GPIOA, 0), PAL_MODE_INPUT_ANALOG);
    chThdSleepMilliseconds(3);
    adc_read(&adcbuf[0]);
    dbgprintf("coord_X - %.3f ", p.X);
    chThdSleepMilliseconds(300);

    /*Ось Y*/
    Y_axis();
    palSetLineMode( PAL_LINE(GPIOA, 0), PAL_MODE_INPUT_ANALOG);
    chThdSleepMilliseconds(3);
    adc_read(&adcbuf[1]);
    dbgprintf("coord_Y - %.3f \n\r", p.Y);
    chThdSleepMilliseconds(300);

    XY_transform(adcbuf, &p);
    putElement(&circular, &p);

    int current = circular.current - 1;
    if (current == -1){
      current = 0;
    }
    dbgprintf("Array[%d]: X=%.3f, Y=%.3f\n\r\n\r",
              circular.current,
              circular.X[current], circular.Y[current]);

    ADC_to_angle_transform(adcservobuf, &d);
  }
}

