#include <stdlib.h>
#include <stdio.h>

int pop(unsigned x){
	/**
	 * Compute 1 bits.
	 * Ex: compute hamming distance
	 *     pop(x^y)
	 *
	 **/
	x = x - ((x>>1) & 0x55555555);
	x = (x & 0x33333333) + (( x>>2 ) & 0x33333333);
	x = (x + (x >> 4)) & 0x0F0F0F0F;
	x = x + (x >>8);
	x = x + (x >>16);
	return x & 0x0000003F;
}
int pop2(unsigned x){
	/** 
	 * FROM HAKMEM MEMO
	 **/
	unsigned n;
	n = (x >>1) & 033333333333;          // Count bits in
	x = x-n;		             // each 3-bit
	n = (n>>1) & 033333333333;           // field.
	x = x-n;
	x = (x + (x >>3)) & 030707070707;    //6-bit sums.
	return x%63;			     // Add 6-bit sums.
//	return ((x*0404040404) >> 26) + //Add 6-bit sums.
//		(x>>30);		//More fast in most computers/
}
int pop3(unsigned x){
	/** 
	 * ANOTHER HAKMEM
	 **/
	unsigned n;
	n = (x >> 1) & 0x77777777;
	x = x-n;
	n = (n >> 1) & 0x77777777;
	x = x-n;
	n = (n >> 1) & 0x77777777;
	x = x-n;
	x = (x + (x >> 4 )) & 0x0F0F0F0F;
	x = x*0x01010101;
	return  x>>24;
}
/**
int pop4(unsigned x){
	unsigned long long y;
	y = x * 0x0002000400080010ULL;
	y = y & 0x1111111111111111ULL;
	y = y * 0x1111111111111111ULL;
	y = y >> 60;
	return y;
}
**/
int main(){
	printf("%d\n", pop(5));
	printf("%d\n", pop(24));
	printf("%d\n", pop(55));
	printf("%d\n" ,pop(1577962638));
	printf("%d\n", pop(1727613287));
	printf("%d\n",pop2(1577962638));
	printf("%d\n",pop2(1727613287));
	printf("%d\n",pop3(1577962638));
	printf("%d\n",pop3(1727613287));
	printf("%d\n",pop4(1577962638));
	printf("%d\n",pop4(1727613287));
	return 0;
}
