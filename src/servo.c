#include <servo.h>
#include <math.h>
#include <uart_lld.h>

static bool flagA1 = false;
static bool flagB1 = false;
static bool flagA2 = false;
static bool flagB2 = false;
extern adcsample_t adcservobuf[2];

ADCConversionGroup adcconf2 = {
   .circular = FALSE,
   .num_channels = 2,
   .end_cb = ADC_conversion_end_cb,
   .error_cb = NULL,
   .cr1 = 0,
   .cr2 = 0,
   .smpr1 = 0,
   .smpr2 = ADC_SMPR2_SMP_AN5(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN4(ADC_SAMPLE_239P5),
   .sqr1 = ADC_SQR1_NUM_CH(2),
   .sqr2 = 0,
   .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN5) | ADC_SQR3_SQ2_N(ADC_CHANNEL_IN4)
};

void motor_location_init(void){
 adcStart(&ADCD1, NULL);
}

void motor_location_read (adcsample_t  *adcservobuf) {
 adcConvert(&ADCD1, &adcconf2, adcservobuf, 1);
}

/* Функция преобразования значения АЦП в угол*/
void ADC_to_angle_transform(uint16_t *adcservobuf, adc_t *str){

  str->ADC_ANGLE_X=adcservobuf[0];
  str->ADC_ANGLE_Y=adcservobuf[1];

  float voltage_X= adcservobuf[0]* VOLTAGE_REFERENCE / ADC_RESOLUTION; // АЦП в напряжение
  float voltage_Y= adcservobuf[1]* VOLTAGE_REFERENCE / ADC_RESOLUTION; // АЦП в угол

  str-> ADC_ANGLE_X=(voltage_X/ VOLTAGE_REFERENCE) * ANGLE_RANGE;
  str-> ADC_ANGLE_Y=(voltage_Y/ VOLTAGE_REFERENCE) * ANGLE_RANGE;
}

/* Callback*/
void ADC_conversion_end_cb(ADCDriver* adcp) {

  (void)adcp;
  // Проверка границ по X
  if (adcservobuf[0] < ADC_MIN_X){
    flagA1 = true;
  }
  else {
    flagA1 = false;
  }
  if (adcservobuf[0] >= ADC_MAX_X){
    flagA2 = true;
    }
  else {
    flagA2 = false;
  }

  // Проверка границ по Y
  if (adcservobuf[1] < ADC_MIN_Y){
    flagB1 = true;
  }
  else{
    flagB1 = false;
  }
  if (adcservobuf[1] >= ADC_MAX_Y){
    flagB2 = true;
  }
  else{
    flagB2 = false;
  }
}

bool get_flag_dirA1(void){
  return flagA1;
}

bool get_flag_dirA2(void){
  return flagA2;
}

bool get_flag_dirB1(void){
  return flagB1;
}

bool get_flag_dirB2(void){
  return flagB2;
}

void set_flag_dirA1(bool f_A1){
  flagA1 = f_A1;
}

void set_flag_dirA2(bool f_A2){
  flagA2 = f_A2;
}
void set_flag_dirB1(bool f_B1){
  flagB1 = f_B1;
}
void set_flag_dirB2(bool f_B2){
  flagB2 = f_B2;
}

void processing_flags(bool flagA1, bool flagA2, bool flagB1, bool flagB2){
  if (flagA1 == true){
    disable_motors_A();
    chThdSleepMilliseconds(100);
  }
  if (flagA2 == true){
    disable_motors_A();
    chThdSleepMilliseconds(100);
  }
  if (flagB1 == true){
    disable_motors_B();
    chThdSleepMilliseconds(100);
  }
  if (flagB2 == true){
    disable_motors_B();
    chThdSleepMilliseconds(100);
  }
}



