#include <dependenceXY_angle.h>
#include <uart_lld.h>
#include <servo.h>
#include <stdlib.h>
#include <math.h>


bool priority = 0;
float control_signal_X = 0;
float control_signal_Y = 0;
int difference = 0;
int cs_X = 0;
int cs_Y = 0;

void screenControl(circular_t* circular, coordinates_t *current_coordinates) {

  int curr = circular->current - 1;
  if (curr < 0){
    curr = 0;
  }

  float coord11 = circular->X[curr];
  float coord22 = circular->Y[curr];
//  dbgprintf(" X1  %.3f\n\r", coord11);
//  dbgprintf(" curr  %d\n\r", curr);


  current_coordinates->X = coord11;
  current_coordinates->Y = coord22;

  // Вычисление ошибки
  float error_X = current_coordinates->X - CENTER_X;
  float error_Y = current_coordinates->Y - CENTER_Y;
//  dbgprintf("errX  %.3f, errY  %.3f\n\r", error_X, error_Y);

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

//  dbgprintf("cs_X  %.3f, cs_Y  %.3f\n\r", control_signal_X, control_signal_Y);
//
  // Применение управляющего сигнала к сервам
  cs_X = (int)fabsf(control_signal_X);
  cs_Y = (int)fabsf(control_signal_Y);

  if (cs_X > cs_Y){
    priority = 1;
  }
  else if (cs_X < cs_Y){
    priority = 0;
  }

  difference = (int)(abs (cs_X - cs_Y));

  /*Движение влево-вниз*/
  if (control_signal_X > 0 && control_signal_Y > 0) {
     if (get_flag_dirB1() == 0 && get_flag_dirA2() == 0){
        set_motor_LEFTdirection_A1();
        set_motor_DOWNdirection_B2();
        if (priority == 0){
          chThdSleepMilliseconds(cs_X);
          disable_motors_A();
          chThdSleepMilliseconds(2*difference);
          disable_motors_B();
        }
        else {
          chThdSleepMilliseconds(2*cs_Y);
          disable_motors_B();
          chThdSleepMilliseconds(difference);
          disable_motors_A();
        }
//        dbgprintf("MOVE LEFT-DOWN\n\r\n\r");
     }
     if (get_flag_dirB1() == 1){
       set_motor_UPdirection_B1();
       chThdSleepMilliseconds(50);
       disable_motors_B();
       set_flag_dirB1(false);
//       dbgprintf("RETURN UP B1\n\r\n\r");

     }
     if (get_flag_dirA2() == 1){
       set_motor_RIGHTdirection_A2();
       chThdSleepMilliseconds(20);
       disable_motors_A();
       set_flag_dirA2(false);
//       dbgprintf("RETURN RIGHT A2\n\r\n\r");

     }
     return;
  }

  /*Движение вправо-вверх*/
  if (control_signal_X < 0 && control_signal_Y < 0) {
     if (get_flag_dirB2() == 0 && get_flag_dirA1() == 0){
        set_motor_UPdirection_B1();
        set_motor_RIGHTdirection_A2();
        if (priority == 0){
          chThdSleepMilliseconds(2*cs_X);
          disable_motors_A();
          chThdSleepMilliseconds(difference);
          disable_motors_B();
        }
        else {
          chThdSleepMilliseconds(cs_Y);
          disable_motors_B();
          chThdSleepMilliseconds(2*difference);
          disable_motors_A();
        }
//        dbgprintf("MOVE RIGHT-UP\n\r\n\r");
     }
      if (get_flag_dirA1() == 1){
       set_motor_LEFTdirection_A1();
       chThdSleepMilliseconds(50);
       disable_motors_A();
       set_flag_dirA1(false);
//       dbgprintf("RETURN LEFT A1\n\r\n\r");

      }
      if (get_flag_dirB2() == 1){
       set_motor_DOWNdirection_B2();
       chThdSleepMilliseconds(20);
       disable_motors_B();
       set_flag_dirB2(false);
//       dbgprintf("RETURN DOWN B2\n\r\n\r");

     }
     return;
  }
    /*Движение влево-вверх*/
    if (control_signal_X < 0 && control_signal_Y > 0) {
       if (get_flag_dirB2() == 0 && get_flag_dirA2() == 0){
          set_motor_UPdirection_B1();
          set_motor_LEFTdirection_A1();
          if (priority == 0){
            chThdSleepMilliseconds(2*cs_X);
            disable_motors_A();
            chThdSleepMilliseconds(2*difference);
            disable_motors_B();
          }
          else {
            chThdSleepMilliseconds(2*cs_Y);
            disable_motors_B();
            chThdSleepMilliseconds(2*difference);
            disable_motors_A();
          }
//          dbgprintf("MOVE LEFT-UP\n\r\n\r");

       }
       if (get_flag_dirB2() == 1){
         set_motor_DOWNdirection_B2();
         chThdSleepMilliseconds(50);
         disable_motors_B();
         set_flag_dirB2(false);
//         dbgprintf("RETURN DOWN B2\n\r\n\r");
       }
       if (get_flag_dirA1() == 1){
         set_motor_RIGHTdirection_A2();
         chThdSleepMilliseconds(50);
         disable_motors_A();
         set_flag_dirA1(false);
//         dbgprintf("RETURN RIGHT A2\n\r\n\r");

       }
       return;
    }

  /*Движение вправо-вниз*/
  if (control_signal_Y < 0 && control_signal_X > 0) {
    if (get_flag_dirB1() == 0 && get_flag_dirA1() == 0){
       set_motor_DOWNdirection_B2();
       set_motor_RIGHTdirection_A2();
       if (priority == 0){
         chThdSleepMilliseconds(cs_X);
         disable_motors_A();
         chThdSleepMilliseconds(difference);
         disable_motors_B();
       }
       else {
         chThdSleepMilliseconds(cs_Y);
         disable_motors_B();
         chThdSleepMilliseconds(difference);
         disable_motors_A();
       }
//       dbgprintf("MOVE RIGHT-DOWN\n\r\n\r");

    }
    if (get_flag_dirA1() == 1){
      set_motor_LEFTdirection_A1();
      chThdSleepMilliseconds(50);
      disable_motors_A();
      set_flag_dirA1(false);
//      dbgprintf("RETURN LEFT A1\n\r\n\r");

    }
    if (get_flag_dirB1() == 1){
      set_motor_UPdirection_B1();
      chThdSleepMilliseconds(50);
      disable_motors_B();
      set_flag_dirB1(false);
//      dbgprintf("RETURN UP B1\n\r\n\r");

    }
    return;
  }
}

float csX(void){
  return control_signal_X;
}
float csY(void){
  return control_signal_Y;
}




