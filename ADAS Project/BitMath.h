
#ifndef BITMATH_H_
#define BITMATH_H_

#define SET_BIT(reg , bit)					 (reg = reg | (1<<bit))
#define CLEAR_BIT(reg , bit)				 (reg = reg & (~(1<<bit)))
#define TOGGLE_BIT(reg , bit)				 (reg = reg  ^ (1<<bit))
#define READ_BIT(reg , bit)					 ( (reg>>bit) & 1)
#define WRITE_BIT(reg , bit , val)			 (reg = (reg & ~(1<<bit)) | ((val) <<bit ))

#endif /* BITMATH_H_ */