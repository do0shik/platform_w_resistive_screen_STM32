#include "ch.h"
#include "hal.h"
#include <motor_control.h>
#include <uart_lld.h>
#include <test_adc.h>
#include <servo.h>
#include <coord_transform.h>

uint16_t servo_num = 1;
uint16_t angle = 0;
bool direction = false;

//static uint16_t adcbuf[2] = {0};
static adcsample_t  adcservobuf[2] = {0};

int main(void) {

//  coordinates_t p = {
//        .X = 0,
//        .Y = 0,
//    };
  adc_t d = {
          .ADC_ANGLE_X = 0,
          .ADC_ANGLE_Y = 0,
      };

  halInit();
  chSysInit();

//  adc_init();
  motor_location_init();

  debug_stream_init();
  dbgprintf("start\n\r");

  palSetLineMode(PAL_LINE(GPIOA, 4), PAL_MODE_INPUT_ANALOG);
  palSetLineMode(PAL_LINE(GPIOA, 5), PAL_MODE_INPUT_ANALOG);

  init_driver_servo();
  palSetLineMode(PAL_LINE(GPIOA, 9), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
  palClearLine(PAL_LINE(GPIOB, 0));
  pwmMotorChangeWidth(5000);

  while(1)
  {

   //Motor_Location_XY
    motor_location_read(&adcservobuf[0]);
    dbgprintf("angle1 - %.3f angle2 - %.3f\n\r", d.ADC_ANGLE_X, d.ADC_ANGLE_Y);
    chThdSleepMilliseconds(500);


//   //Îñü Y
//    palSetLine( PAL_LINE(GPIOA, 6));
//    palSetLine( PAL_LINE(GPIOA, 7));
//    palClearLine( PAL_LINE(GPIOB, 0));
//    palClearLine( PAL_LINE(GPIOB, 1));
//
//    palSetLineMode( PAL_LINE(GPIOA, 0), PAL_MODE_INPUT_ANALOG );
//    chThdSleepMilliseconds(3);
//    adc_read(&adcbuf[0]);
//    //dbgprintf("adc1 - %d\n\r", adcbuf[0]);
//    dbgprintf("start");
//    dbgprintf("%.3f", p.Y);
//    chThdSleepMilliseconds(500);
//
//
//    //Îñü X
//    palClearLine( PAL_LINE(GPIOA, 6));
//    palSetLine( PAL_LINE(GPIOA, 7));
//    palClearLine( PAL_LINE(GPIOB, 0));
//    palSetLine( PAL_LINE(GPIOB, 1));
//
//    palSetLineMode( PAL_LINE(GPIOA, 0), PAL_MODE_INPUT_ANALOG );
//    chThdSleepMilliseconds(3);
//    adc_read(&adcbuf[1]);
//    //dbgprintf("adc2 - %dd,", adcbuf[1]);
//    dbgprintf("%.3f", p.X);
//    chThdSleepMilliseconds(500);
//
//    XY_transform(adcbuf, &p);

      ADC_to_angle_transform(adcservobuf, &d);

  }
}

