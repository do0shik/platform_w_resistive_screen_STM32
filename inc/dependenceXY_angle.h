#ifndef INC_DEPENDENCEXY_ANGLE_H_
#define INC_DEPENDENCEXY_ANGLE_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "motor_control.h"
#include "coord_transform.h"

#define CENTER_X 0.4  // ����������� ���������� �� ��� X �� ����������� ������
#define CENTER_Y 0.56 // ����������� ���������� �� ��� Y �� ����������� ������
#define kP 0.5  // ����������� ���������������� ������������
#define kI 0.3  // ����������� ������������ ������������

void screenControl(circular_t* circular, coordinates_t* current_coordinates);
float csX(void);
float csY(void);


#endif /* INC_DEPENDENCEXY_ANGLE_H_ */
