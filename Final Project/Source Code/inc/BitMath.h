#ifndef BITMATH_H_
#define BITMATH_H_

#define SetBit(Reg,No)    Reg|=(1<<No)  // Reg= Reg|(1<<No)
#define ClearBit(Reg,No)  Reg&=~(1<<No)
#define GetBit(Reg,No)    ((Reg>>No)&1)

#ifndef NULL
#define NULL ((void*)0)
#endif

#define NULLChar '\0'

#endif /* BITMATH_H_ */
