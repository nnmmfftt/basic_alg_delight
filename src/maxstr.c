#include <stdlib.h>

/**
 * Max length of 1-bit string
**/
int maxstr1(unsigned x){
	int k;
	for (k = 0; x!= 0; k++) x = x & 2*x;
	return k;
}

/**
 * Max length of 1-bit string and position
**/
int fmaxstr1(unsigned x, int *apos){
	unsigned y;
	int s;
	
	if( x == 0) { *apos = 32; return 0;}
	y = x & (x << 1);
	if( y == 0) { s = 1; goto L1;}
	x = y &(y << 2);
	if (x == 0) { s = 2; x = y; goto L2;}
	y = x & (x << 4);
	if (y == 0) { s = 4; goto L4;}
	x = y & (y << 8);
	if (x == 0) { s = 8; x = y; goto L8;}
	if (x == 0xFFFF8000) {*apos = 0; return 32;}
	s = 16;
	
	L16: y = x & (x <<8);
	     if (y != 0) { s = s +8; x =y;}
	L8 : y = x & (x <<4);
	     if (y != 0) { s = s +4; x =y;}
	L4 : y = x & (x <<2);
	     if (y != 0) { s = s +2; x =y;}
	L2 : y = x & (x <<1);
	     if (y != 0) { s = s +1; s =y;}
	L1 : *apos = nlz(x);
	   return s;
}
