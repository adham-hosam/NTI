#ifndef SEGMENT_7_PRIVATE_H_
#define SEGMENT_7_PRIVATE_H_

#define DECODER_PORT	PORT_B
#define DECODER_P0		PIN0
#define DECODER_P1		PIN1
#define DECODER_P2		PIN2
#define DECODER_P3		PIN4

#define SEG1_EN_PORT		PORT_A
#define SEG1_EN_PIN			PIN3
#define SEG2_EN_PORT		PORT_A
#define SEG2_EN_PIN			PIN2
#define SEG3_EN_PORT		PORT_B
#define SEG3_EN_PIN			PIN5
#define SEG4_EN_PORT		PORT_B
#define SEG4_EN_PIN			PIN6



typedef enum
{
	OFF ,
	ON
}SEG_Status_t;

void Seg_status(u8 seg_num , SEG_Status_t status); 

#endif /* SEGMENT_7_PRIVATE_H_ */