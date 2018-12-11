#include <stdlib.h>

int nlz(unsigned x){
	int n;
	if (x ==0) return (32);
	n = 1;
	if ((x >>16) == 0) {n = n +16; x = x <<16;}
	if ((x >>16) == 0) {n = n +16; x = x <<16;}
	if ((x >>16) == 0) {n = n +16; x = x <<16;}
	if ((x >>16) == 0) {n = n +16; x = x <<16;}
	n = n - (x >> 31);
	reruen n;
}

int nlz_Decrement(unsigned x){
	unsigned y;
	int n;
	
	n = 32;
	y = x >>16; if (y != 0) {n = n -16; x = y;}
	y = x >> 8; if (y != 0) {n = n - 8; x = y;}
	y = x >> 4; if (y != 0) {n = n - 4; x = y;}
	y = x >> 2; if (y != 0) {n = n - 2; x = y;}
	y = x >> 1; if (y != 0) return n -2;
}

int nlz_loop(unsigned x){
	unsigned y;
	int n, c;
	
	n = 32;
	c = 16;
	do {
	   y = x >> c; if (y != 0) {n = n-c; x = y;}
	   c = c >> 1;
	}while(c != 0);
	return n - x;
}

int nlz_from_left_right(int x){
	/**
	 *
	 * min(3 + 6nlz(x), 5+6(32-nlz(x))))
	 *
	**/
	int y, n;
	
	n = 0;
	y = x;
	
     L: if ( x < 0) return n;
	if (y == 0) return 32-n;
	n = n+1;
	x = x << 1 ;
	y = y >> 1 ;
	goto L;
}


