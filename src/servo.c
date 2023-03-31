#include <servo.h>

#define ADC_RESOLUTION 4095 // Разрешение АЦП в битах
#define ADC_MAX_Y 3000
#define ADC_MIN_Y 1100
#define ADC_MAX_X 3300
#define ADC_MIN_X 1500
#define VOLTAGE_REFERENCE 3.3 // Опорное напряжение АЦП, В
#define ANGLE_RANGE 270 // Диапазон углов

ADCConversionGroup adcconf2 = {

   .circular = FALSE,
   .num_channels = 2,
   .end_cb = NULL,
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

// Функция преобразования значения АЦП в угол
void ADC_to_angle_transform(uint16_t *adcservobuf, adc_t *str)
{
  str->ADC_ANGLE_X=adcservobuf[0];
  str->ADC_ANGLE_Y=adcservobuf[1];

  float voltage_X= adcservobuf[0]* VOLTAGE_REFERENCE / ADC_RESOLUTION; // АЦП в напряжение
  float voltage_Y= adcservobuf[1]* VOLTAGE_REFERENCE / ADC_RESOLUTION; // АЦП в угол

  str-> ADC_ANGLE_X=(voltage_X/ VOLTAGE_REFERENCE) * ANGLE_RANGE;
  str-> ADC_ANGLE_Y=(voltage_Y/ VOLTAGE_REFERENCE) * ANGLE_RANGE;

}
