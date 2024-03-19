#ifndef SEGMENT_7_INTERFACE_H_
#define SEGMENT_7_INTERFACE_H_

#include "StdTypes.h"
#include "BitMath.h"

#include "DIO_interface.h"





void SevSeg_4Dig_init (void );
//void Seg_status(u8 seg_num , SEG_Status_t status);
void SevSeg_Write ( u8 index , u8 num );
void SevSeg_4Dig ( u16 num );

#endif /* SEGMENT_7_INTERFACE_H_ */