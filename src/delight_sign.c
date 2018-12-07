#include <stdlib.h>

/**
 * sign function (signum function)
 * [Hop}
 * 4 CPU instructions in most computers
 * 
 * 1) signed int shifting
 * 2) use unsigned int shifting to simulation
 * 3) use comparison predicate 
 * 
 **/

int32_t  delight_sign_function(uint32_t x){
/**
 *
 *              ----------------
 *             / -1  , x <0
 *     sign(x)=   0  , x =0
 *             \  1  , x >0
 *              ----------------
 *
 **/
	//return (x>>31)|((-x)>>31);               (-x>>31)-(x>>31) can compute abs except x = -2^31
	//return -(x>>31)|((-x)>>31);
	bool tmp1 = (x>0);//bool tmp1 = (x>=0);
	bool tmp2 = (x<0);//bool tmp2 = (x<=0);
	return tmp1-tmp2;
}
