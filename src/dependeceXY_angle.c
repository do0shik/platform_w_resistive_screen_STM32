#include <dependenceXY_angle.h>
#include <uart_lld.h>
#include <servo.h>


float control_signal_X = 0;
float control_signal_Y = 0;

void screenControl(circular_t* circular, coordinates_t *current_coordinates) {

  int current = circular->current - 1;
  if (current == -1){
    current = 0;
  }

  float coord11 = circular->X[current - 1];
  float coord22 = circular->Y[current - 1];
  current_coordinates->X = coord11;
  current_coordinates->Y = coord22;

  // Вычисление ошибки
  float error_X = current_coordinates->X - CENTER_X;
  float error_Y = current_coordinates->Y - CENTER_Y;

  // Расчет пропорциональной составляющей
  control_signal_X = kP * error_X;
  control_signal_Y = kP * error_Y;

  float error_integral_X = 0;  // Интегральная ошибка по оси X
  float error_integral_Y = 0;  // Интегральная ошибка по оси Y
  // Расчет интегральной составляющей
  error_integral_X = error_integral_X + error_X;
  error_integral_Y = error_integral_Y + error_Y;
  control_signal_X = control_signal_X + kI * error_integral_X;
  control_signal_Y = control_signal_Y + kI * error_integral_Y;

  dbgprintf("cs_X  %.3f, cs_Y  %.3f\n\r", control_signal_X, control_signal_Y);

  // Применение управляющего сигнала к сервам

  if (control_signal_X > 0) {
    if (get_flag_dirB1() == 0){
      chThdSleepMilliseconds(80);
      set_motor_UPdirection_B2();
      chThdSleepMilliseconds(80);
      dbgprintf("\n\rDOWN\n\r \n\r");
    }
    else {
      set_motor_DOWNdirection_B1();
      chThdSleepMilliseconds(200);
    }
  }
  else if (control_signal_X < 0) {
    if (get_flag_dirB2() == 0){
      set_motor_DOWNdirection_B1();
      chThdSleepMilliseconds(200);
      dbgprintf("\n\rUP\n\r \n\r");
    }
    else {
      set_motor_UPdirection_B2();
      chThdSleepMilliseconds(100);
    }
  }

  if (control_signal_Y > 0) {
    if (get_flag_dirA2() == 0){
     set_motor_DOWNdirection_A1();
     chThdSleepMilliseconds(200);

     dbgprintf("\n\rLEFT\n\r \n\r");
    }
    else {
      chThdSleepMilliseconds(80);
      set_motor_UPdirection_A2();
      chThdSleepMilliseconds(80);
    }
  }
  else if (control_signal_Y < 0) {
    if (get_flag_dirA1() == 0){
     chThdSleepMilliseconds(80);
     set_motor_UPdirection_A2();
     chThdSleepMilliseconds(80);

     dbgprintf("\n\rRIGHT\n\r \n\r");
     }
    else {
      set_motor_DOWNdirection_A1();
      chThdSleepMilliseconds(200);
    }
   }

}

float csX(void){
  return control_signal_X;
}
float csY(void){
  return control_signal_Y;
}





