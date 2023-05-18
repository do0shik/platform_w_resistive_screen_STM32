#include <coord_transform.h>
#include <uart_lld.h>
#include <math.h>


void XY_transform(uint16_t *adcbuf, coordinates_t *str){

  str->X = (float)(adcbuf[0] - X_LOWER_LIMIT)/(X_UPPER_LIMIT - X_LOWER_LIMIT);
  str->Y = (float)(adcbuf[1] - Y_LOWER_LIMIT)/(Y_UPPER_LIMIT - Y_LOWER_LIMIT);

  if (str->X <= 0){
    str->X = 0;
  }
  if  (str->Y <= 0){
    str->Y = 0;
  }
  if (str->X >= 1){
      str->X = 1;
    }
  if (str->Y >= 1){
      str->Y = 1;
    }
}



void putElement(circular_t* circular, coordinates_t *str) {
  float first = str->X;
  float second = str->Y;
  circular->X[circular->current] = first;
  circular->Y[circular->current] = second;
  circular->current = circular->current + 1;

  if (circular->current == ARRAY_SIZE) {
    circular->current = 0;
    if (circular->start == -1){
      circular->start = 1;
    }
  }
  if (circular->current == circular->start) {
    circular->start = circular->start + 1;
    if (circular->start >= ARRAY_SIZE) {
      circular->start = 0;
    }
  }
}




