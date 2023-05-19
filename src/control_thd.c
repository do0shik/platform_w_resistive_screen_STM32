#include "control_thd.h"
#include "ch.h"
#include "hal.h"
#include <motor_control.h>
#include <test_adc.h>
#include <servo.h>
#include <coord_transform.h>
#include <string.h>
#include <dependenceXY_angle.h>
#include <control_thd.h>


static THD_WORKING_AREA(THREAD_NAME, 256); // 256 - stack size

static THD_FUNCTION(FUNCTION_NAME, arg)
{
  adc_init();
  init_motors();

  static uint16_t adcbuf[2] = {0};
  adcsample_t  adcservobuf[2] = {0};
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
  palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_OPENDRAIN);
  pwm_motors_ChangeWidth_A(1000);
  pwm_motors_ChangeWidth_B(1000);

    arg = arg;
    while(1) {

      processing_flags(get_flag_dirA1(),
                       get_flag_dirA2(),
                       get_flag_dirB1(),
                       get_flag_dirB2());
      screenControl(&circular, &coord);
//
     /* Положение мотора XY*/
      motor_location_read(&adcservobuf[0]);

      /*Ось X*/
      X_axis();
      palSetLineMode( PAL_LINE(GPIOA, 0), PAL_MODE_INPUT_ANALOG);
      adc_read(&adcbuf[0]);

      /*Ось Y*/
      Y_axis();
      palSetLineMode( PAL_LINE(GPIOA, 0), PAL_MODE_INPUT_ANALOG);
      adc_read(&adcbuf[1]);
      XY_transform(adcbuf, &p);
      putElement(&circular, &p);

      int current = circular.current - 1;
      if (current == -1){
        current = 0;
      }
      ADC_to_angle_transform(adcservobuf, &d);
      chThdSleepMilliseconds(10);

      palTogglePad(GPIOC, 13);
    }
}

void init_control_thd(void)
{
    chThdCreateStatic(THREAD_NAME, sizeof(THREAD_NAME), NORMALPRIO, FUNCTION_NAME, NULL);

}


