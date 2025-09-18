#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_


#define CS00_Bit 0
#define CS01_Bit 1
#define CS02_Bit 2

#define COM00_Bit 4
#define COM01_Bit 5

#define WGM01_Bit 3
#define WGM00_Bit 6

#define TOIE0_Bit 0
#define OCIE0_Bit 1

#define TOV0_Bit 0
#define OCF0_Bit 1

#define Timer0Disabled              0 
#define Timer0Prescaler_1          1 
#define Timer0Prescaler_8          2 
#define Timer0Prescaler_64         3 
#define Timer0Prescaler_256        4 
#define Timer0Prescaler_1024       5 
#define Timer0ExternalCLK_Fallin    6   
#define Timer0ExternalCLK_Rising    7  

#define nin_inverting   1
#define inverting   2

#endif