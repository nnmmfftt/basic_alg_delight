#include <stdlib.h>
/**
 * 
 * First full 1-bit string of a given length
 * 
 **/
int ffstr1_1(unsigned x, int n){
	int k, p;

	p = 0;				// Initialize position to return.
	while(x != 0){
		k = nlz(x); 	// Skip over initial 0's
		x = x << k; 	// (if any).
		p = p + k;
		k = nlz(-x);	// Count first/nest group of 1's.
		if (k >= n) 	// If enough,
			return p;	// return .
		x = x << k; 	// Not enough 1's, skip over
		p = p + k; 		// them.
	}
	return 32;
}

int ffstr1_2(unsigned x, int n){
	int s;

	while(n > 1){
		s = n >> 1;
		x = x & (x << s);
		n = n-s;
	}
	return nlz(x);
}

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

/**
 * Min length of 1-bit string and position
**/
int fminstr1_rightmost(unsigned x, int *apos){
	int k;
	unsigned b, e; 			//Beginnings, ends.

	if(x == 0) {*apos = 32; return 0;}
	b = -x(x >> 1) & x;		// 0-1 transitions.
	e = x & ~(x << 1);		// 1-0 transitions.
	for (k = 1; (b & e) == 0; k++)
		e = e << 1;
	*apos = nlz( b&e );
	return k;
}

int fminstr1(unsigned x, int *apos){
//
	int k, kin, y0, y;
	unsigned int x0, xmin;

	kmin = 32;
	y0 = pop(x);
	x0 = x;
	do{
		x = ((x & -x) + x) & x;	// Turn off rightmost
		y = pop(x);				// string.
		k = y0 - y;				// k = length of string
		if(k <= kmin){			// turned off.
			kmin = k;			// Save shortest length
			xmin = x;			// found, and the string.
		}
		y0 =y;
	}while(x!=0);
	*apos = nlz(x0^xmin);
	return kmin;
}
/**
 * test 6.1
 * add func for Hsieh, find Max length and position of 1-bit string .
 * Can use nlz function. 
**/
int fmaxstr1_Hsieh(unsigned x, int *apos){
	int k;
	unsigned oldx;

	oldx = 0;
	for( k = 0; x != 0; k++){
		oldx = x;
		x &= 2*x;
	}
	*apos = nlz(oldx);
	return k;
	
}

/**
 * test 6.2
 * find position and length longer than given x in 1-bit string.
 * return or print the length & position.
 **/
int bestfit(unsigned x, int n, int  *apos){
	int m, s;

	m = n;
	while(m >1){
		s = m >> 1;
		x = x & (x << s);
		m = m - s;
	}
	return fminstr1(x, apos) + n -1;
}