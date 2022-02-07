/*
 * Bit_Math.h
 *
 *  Author: Mahmoud Ayoub
 */ 

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BITNO) (REG)|= 1<<(BITNO)
#define CLEAR_BIT(REG,BITNO) (REG)&=~(1<<(BITNO))
#define TOGGLE_BIT(REG,BITNO) (REG)^= 1<<(BITNO)



#endif /* BIT_MATH_H_ */