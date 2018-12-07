#include <stdlib.h>
/**
 * doz means difference or zero:
 *                     --------------                    
 *                    / 1) x-y ,x>=y                  
 *         doz(x,y)=  |    
 *                    \ 2) 0 ,  x<y 
 *                     --------------
 * 
 *
 **/                   
uint32_t difference_or_zero(uint32_t x, uint32_t y){
	bool flag = x>= y ;
	return (x-y)&(-flag);
