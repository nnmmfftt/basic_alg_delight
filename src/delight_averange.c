#include <stdlib.h>

/**
 *
 * compute two unsigned int numbers' average by bitset without overflow.
 * Dietz fomula
 *
 **/
uint32_t delight_abs_floor(uint32_t x, uint32_t y){
	if(x<=y) return (y-x) >>1;
	return ((x&y) + ((x^y)>>1));
} 

uint32_t delight_abs_ceiling(uint32_t x, uint32_t y){
	return ((x|y) - ((x^y)>>1));
}

/** 
 * 
 * when calculate two signed int numbers' average,
 * only regard unsigned int method forward as signed int.
 * ------------------------------------------------------
 * Sometimes need to compute truncated average,
 * //truncated average (-3 ,8 ) = -2 (answer is - 2.5 but -2 is closer to 0 than -3)	
 * we need to compute step by step:
 * 1) compute ceiling average
 * 2) if ceiling average is negative odd, add one to the ceiling average
 * 3) if and only if 2) is negative, x+y is negative
 * 
 **/

int32_t delight_abs(int32_t x, int32_t y){
	if(x >0 && y>0) return (x+y) >>1;
	else if(x <=y) return (y-x)>>1;
	int32_t t = (x&y)+((x^y)>>1);
	return t+((t>>31)&(x^y));
	}
