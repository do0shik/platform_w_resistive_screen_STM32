#ifndef INC_COORD_TRANSFORM_H_
#define INC_COORD_TRANSFORM_H_



#include "ch.h"
#include "hal.h"

typedef struct {
  float X;
  float Y;
}coordinates_t;

void XY_transform(uint16_t *adcbuf, coordinates_t *str);


#endif /* INC_COORD_TRANSFORM_H_ */
