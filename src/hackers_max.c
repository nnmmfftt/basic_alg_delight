#include <stdlib.h>
#include "delight_doz.h"

uint32_t delight_max_unsigned(uint32_t x, uint32_t y){
	/**
	 *
	 * unsigned max : max(x,y) = y + doz(x,y) 
	 * unsigned max : min(x,y) = x - doz(x,y)
	 *
	 **/
	return y + doz(x,y);

uint32_t delight_mix_unsigned(uint32_t x, uint32_t y){
	return x - doz(x,y);

int32_t delight_max_signed(int32_t x, int32_t y){
	/**
	 * 
	 * If x,y are signed int and the x-y were overflow, the doz(x,y) will overflow too.
	 * Means x-y + y or x - (x-y) will be a correct answer.
	 * So we need to regard signed int as unsigned int, the answer will be correct.
	 *
	 **/
	return delight_max_ungsined(x,y);

int32_t delight_min_signed(int32_t x, int32_t y){
	return delight_min_unsigned(x,y);
}
