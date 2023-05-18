#include <dependenceXY_angle.h>
#include <uart_lld.h>
#include <servo.h>
#include <stdlib.h>

bool priority = 0;
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

  if (control_signal_X > control_signal_Y){
    priority = 1;
  }
  else if (control_signal_X < control_signal_Y){
    priority = 0;
  }

  int diff = (int) (control_signal_X - control_signal_Y);
  int difference = abs(diff);

  /*Движение влево-вниз*/
  if (control_signal_X > 0 && control_signal_Y > 0) {
     if (get_flag_dirB1() == 0 && get_flag_dirA2() == 0){
        set_motor_LEFTdirection_A1();
        set_motor_DOWNdirection_B2();
        chThdSleepMilliseconds(difference);
        if (priority == 0){
          chThdSleepMilliseconds(control_signal_X);
          disable_motors_B();
          chThdSleepMilliseconds(difference);
          disable_motors_A();
        }
        else {
          chThdSleepMilliseconds(control_signal_Y);
          disable_motors_A();
          chThdSleepMilliseconds(difference);
          disable_motors_B();
        }
     }
     else if (get_flag_dirB1() == 1 && get_flag_dirA2() == 1){
       set_motor_UPdirection_B1();
       chThdSleepMilliseconds(100);
       set_motor_RIGHTdirection_A2();
       chThdSleepMilliseconds(100);
       set_flag_dirA1(false);
       set_flag_dirB2(false);
     }
  }
  /*Движение вправо-вверх*/
  if (control_signal_X < 0 && control_signal_Y < 0) {
     if (get_flag_dirB2() == 0 && get_flag_dirA1() == 0){
        set_motor_UPdirection_B1();
        set_motor_RIGHTdirection_A2();
        chThdSleepMilliseconds(difference);
        if (priority == 0){
          chThdSleepMilliseconds(control_signal_X);
          disable_motors_B();
          chThdSleepMilliseconds(difference);
          disable_motors_A();
        }
        else {
          chThdSleepMilliseconds(control_signal_Y);
          disable_motors_A();
          chThdSleepMilliseconds(difference);
          disable_motors_B();
        }
     }
     else if (get_flag_dirB2() == 1 && get_flag_dirA1() == 1){
       set_motor_LEFTdirection_A1();
       chThdSleepMilliseconds(100);
       set_motor_DOWNdirection_B2();
       chThdSleepMilliseconds(100);
       set_flag_dirA1(false);
       set_flag_dirB2(false);
     }
  }

  /*Движение вправо-вниз*/
  if (control_signal_X > 0 && control_signal_Y < 0) {
     if (get_flag_dirB1() == 0 && get_flag_dirA1() == 0){
        set_motor_DOWNdirection_B2();
        set_motor_RIGHTdirection_A2();
        chThdSleepMilliseconds(difference);
        if (priority == 0){
          chThdSleepMilliseconds(control_signal_X);
          disable_motors_B();
          chThdSleepMilliseconds(difference);
          disable_motors_A();
        }
        else {
          chThdSleepMilliseconds(control_signal_Y);
          disable_motors_A();
          chThdSleepMilliseconds(difference);
          disable_motors_B();
        }
     }
     else if (get_flag_dirB1() == 1 && get_flag_dirA1() == 1){
       set_motor_UPdirection_B1();
       chThdSleepMilliseconds(100);
       set_motor_LEFTdirection_A1();
       chThdSleepMilliseconds(100);
       set_flag_dirA1(false);
       set_flag_dirB2(false);
     }
  }

  /*Движение влево-вверх*/
  if (control_signal_X < 0 && control_signal_Y > 0) {
     if (get_flag_dirB2() == 0 && get_flag_dirA2() == 0){
        set_motor_UPdirection_B1();
        set_motor_LEFTdirection_A1();
        chThdSleepMilliseconds(difference);
        if (priority == 0){
          chThdSleepMilliseconds(control_signal_X);
          disable_motors_B();
          chThdSleepMilliseconds(difference);
          disable_motors_A();
        }
        else {
          chThdSleepMilliseconds(control_signal_Y);
          disable_motors_A();
          chThdSleepMilliseconds(difference);
          disable_motors_B();
        }
     }
     else if (get_flag_dirB1() == 1 && get_flag_dirA2() == 1){
       set_motor_DOWNdirection_B2();
       chThdSleepMilliseconds(100);
       set_motor_RIGHTdirection_A2();
       chThdSleepMilliseconds(100);
       set_flag_dirA1(false);
       set_flag_dirB2(false);
     }
  }
}

float csX(void){
  return control_signal_X;
}
float csY(void){
  return control_signal_Y;
}




