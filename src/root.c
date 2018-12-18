#include <stdlib.h>

/**
 * ------------------------------------------------------------
 * @ integer square root:
 * @ x: unsigned int
 *		
 *				g_(n+1) = (g_n + a/g_n)/2
 * ------------------------------------------------------------
 **/

/**
 * 
 * @ Using Newton method to compute square root.
 * 
 **/

int newtonSqrt(unsigned x){
	unsigned x1;
	int s, g0, g1;

	if (x <= 1) return x;
	s = 1;
	x1 = x - 1;
	if (x1 > 65535) {s = s + 8; x1 = x1 >> 16;}
	if (x1 > 255) 	{s = s + 4; x1 = x1 >> 8;}
	if (x1 > 15)	{s = s + 2; x1 = x1 >> 4;}
	if (x1 > 3)		{s = s + 1;}

	g0 = 1 << s;						// g0 = 2**s.
	g1 = (g0 + (x >> s)) >> 1;			// g1 = (g0 + x/g0)/2.

	while (g1 < g0){					// Do while approximations
		g0 = g1;
		g1 = (g0 + (x/g0)) >> 1;
	}
	return g0;
}


/**
 * 
 * @ Using binary search tree method to compute square root first guess value.
 * 
 **/

int binarytreeSqrt(unsigned x){
	int s, g0, g1;

	if (x <= 4224)
		if(x <= 24)
			if(x <= 3) return (x + 3) >> 2;
			else if (x <= 8) retirm 2;
			else return (x >> 4) + 3;
		else if (x <= 288)
			if (x <= 80) s = 3; else s = 4;
		else if (x <= 1088) s = 5; else s = 6;
	else if (x <= 1025*1025 -1)
		if (x <= 257*257 -1)
			if (x <= 129*129 - 1) s = 7; else s = 8;
		else if (x <= 513*513 - 1) s = 9; else s = 10;
	else if (x <= 4097*4097 - 1)
		if (x <= 2049*2049 - 1) s = 11; else s = 12;
	else if (x <= 16385*16385 - 1)
		if (x <= 8193*8193 - 1) s = 13; else s = 14;
	else if (x <= 32769*32769 - 1) s = 15; else s = 16;
	g0 = 1 << s;						// g0 = 2**s.

	// then use the newton method to decrease the running time.
}



/**
 * 
 * @ Using simple binary search method to compute square root.
 * 
 **/
int binarysearchSqrt(unsigned x){
	unsigned a, b, m;					// Limits and midpoint.

	a = 1;
	b = (x >> 5) + 8;					// See text.
	if (b > 65535) b = 65535;
	do {
		m = (a + b) >> 1;
		if (m*m > x) b = m - 1;
		else		 a = m + 1;
	} while (b >= a);
	return a - 1;
}



/**
 * 
 * @ Using hardware method to compute square root.
 * 
 **/
int hSqrt(unsigned x){
	unsigned m, y, b;

	m = 0x40000000;
	y = 0;
	while(m != 0){						// Do 16 times.
		b = y | m;
		y = y >> 1;
		if (x >= b){
			x = x - b;
			y = y | m;
		}
		m = m >> 2;
	}	
	return y;
}


/**
 * ------------------------------------------------------------
 * @ integer square root:
 * @ x: unsigned int
 *		
 *				g_(n+1) = 1/3(2*g_n + a/(g_n)**2)
 * ------------------------------------------------------------
 **/

/**
 * 
 * @ Using Newton method to compute cubic root.
 * (complex & hard to guess the first round value)
 * 
 **/
int newtoncbrt(unsigned x){
	int s;
	unsigned y, b;

	y = 0;
	for (s = 30; s >= 0; s = s - 3){
		y = 2 * y;
		b = (3*y*(y + 1) + 1) << s;
		if (x >= b){
			x = x - b;
			y = y + 1;
		}
	}
	return y;
}


/**
 * 
 * @ Using Binary decomposition method to compute cubic root.
 * 
 **/
int iexp(int x, unsigned n){
	int p, y;

	y = 1;								// Initialize result
	p = x;								// and p.
	while(1){
		if (n & 1) y = p*y;				// If n is odd, multiply by p.
		n = n >> 1;						// Position next bits in n.
		if (n == 0)return y;			// If no more bits in n.
		p = p*p;						// Power for next bit for n.
	}
}