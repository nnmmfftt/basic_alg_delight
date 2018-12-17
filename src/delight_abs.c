#include <stdlib.h>
/**
 *
 * 
 * 
 * 
 **/

uint32_t delight_abs(int32_t x){
	return (~x)+1;
}
int abs_bitsimp(int n){
    return (n ^ n >> 31) - (n >> 31);
}