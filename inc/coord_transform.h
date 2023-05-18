#ifndef INC_COORD_TRANSFORM_H_
#define INC_COORD_TRANSFORM_H_
#define X_LOWER_LIMIT     1350
#define X_UPPER_LIMIT     2900

#define Y_LOWER_LIMIT     950
#define Y_UPPER_LIMIT     2600
#define ARRAY_SIZE        50


#include "ch.h"
#include "hal.h"
#include "string.h"
#include "math.h"


typedef struct {
  float X;
  float Y;
}coordinates_t;

typedef struct circular{
  float X[ARRAY_SIZE];
  float Y[ARRAY_SIZE];
  int start;
  uint16_t current;
}circular_t;

void XY_transform(uint16_t *adcbuf, coordinates_t *str);
void coord_save(coordinates_t *points, coordinates_t *str);
void putElement(circular_t* circular, coordinates_t* value);

#endif /* INC_COORD_TRANSFORM_H_ */
