#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_


#define MCUCSR   (*(volatile unsigned char*)0x54)
#define ISC2 6

#define MCUCR   (*(volatile unsigned char*)0x55)
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define GICR     (*(volatile unsigned char*)0x5B)
#define INT1 7
#define INT0 6
#define INT2 5

#define GIFR    (*(volatile unsigned char*)0x5A)
#define INTF1 7
#define INTF0 6
#define INTF2 5
/*

#define EXTI_PORT		PORT_D
#define EXTI0_PIN		PIN2
#define EXTI1_PIN		PIN3
#define EXTI2_PIN		PIN4
*/
#endif 