#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "motor_control.h"
#include "coord_transform.h"

#define ADC_RESOLUTION 4095 // Разрешение АЦП в битах
//#define ADC_MAX_Y 3000
//#define ADC_MIN_Y 1300
//#define ADC_MAX_X 2500
//#define ADC_MIN_X 1000

#define ADC_MAX_Y 2400
#define ADC_MIN_Y 1880

#define ADC_MAX_X 1850
#define ADC_MIN_X 1450

#define VOLTAGE_REFERENCE 3.3 // Опорное напряжение АЦП, В
#define ANGLE_RANGE 270 // Диапазон углов
#define ANGLE_UP 20
#define ANGLE_DOWN -20

extern float start_angle_X;
extern float start_angle_Y;

typedef struct {
  float ADC_ANGLE_X;
  float ADC_ANGLE_Y;
}adc_t;

void motor_location_init(void);
void motor_location_read (uint16_t *adcservobuf);
void ADC_to_angle_transform(uint16_t *adcservobuf, adc_t *str);
void ADC_conversion_end_cb(ADCDriver* adcp);
//bool get_flag_A(void);
//bool get_flag_B(void);

bool get_flag_dirA1(void);
bool get_flag_dirA2(void);
bool get_flag_dirB1(void);
bool get_flag_dirB2(void);
void processing_flags(bool flagA1, bool flagA2, bool flagB1, bool flagB2);


#endif /* INC_SERVO_H_ */
