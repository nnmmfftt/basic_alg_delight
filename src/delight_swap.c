#include<stdlib.h>
uint32_t delight_swap(uint32_t x, uint32_t y){
/**
 *
 * VC env
 *
 *
 **/
	_asm{		
	mov eax,x
	xchg y eax
	mov x,eax
}
/**
 *
 * GCC
 * 
 *
 **/
 	asm(
	"mov %%eax \n"
	"xchg y eax\n"
	"mov x,%%eax"
	::: "memory"
	)
}
