#include <coord_transform.h>

#define X_LOWER_LIMIT     916.
#define X_UPPER_LIMIT     3027.

#define Y_LOWER_LIMIT     836.
#define Y_UPPER_LIMIT     3083.


void XY_transform(uint16_t *adcbuf, coordinates_t *str)
{
  str->X=(adcbuf[0]-X_LOWER_LIMIT)/(X_UPPER_LIMIT-X_LOWER_LIMIT);
  str->Y=(adcbuf[1]-Y_LOWER_LIMIT)/(Y_UPPER_LIMIT-Y_LOWER_LIMIT);
  if (str->X <= 0){
    str->X=0;
  }
  else if  (str->Y <= 0){
    str->Y=0;
  }
}



