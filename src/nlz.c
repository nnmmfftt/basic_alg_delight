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

int nlz_from_both_leftandright(int x){
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

int nlz_no_branch(unsigned x){
	int y, m, n;

	y = -(x >> 16) 		// If left half of x is 0,
	m = (y >> 16) & 16; // set n=16. If left half
	n = 16 - m;			// is nonzero, set n = 0 and
	x = x >> m;			// shift x right 16.
						// Now x is of the form 0000xxxx.
	y = x - 0x100;		// If position 8-15 are 0,
	n = n+m;
	x = x << m;

	y = x - 0x1000;		// If positions 12-15 are 0,
	m = (y >> 16) & 4;	// add 4 to n and shift x left 4.
	x = x << m;

	y = x - 0x4000;		// If positions 14-15 are 0,
	m = (y >> 16) & 2;  // add 2 to n and shift x left 2.
	n = n+m;
	x = x << m;

	y = x >> 14;		// Set y = 0, 1, 2, or 3.
	m = y & -(y >>1);	// Set m = 0, 1, 2, or 2 resp.
	return n+2 -m;
}

int nlz_pop(unsigned x){
		x = x | (x >> 1);
		x = x | (x >> 2);
		x = x | (x >> 4);
		x = x | (x >> 8);
		x = x | (x >>16);
		return pop(-x);
}

int nlz_harleyMethod(unsigned x){
	static char table[64] = 
	/**
	 * @u unused
	 **/
		{32, 31, u, 16, u, 30, 3, u, 15, u, u, u, 29, 10, 2, u,
		  u,  u,12, 14,21,  u,19, u,  u,28, u,25,  u,  9, 1, u,
		 17,  u, 4,  u, u,  u,11, u, 13,22,20, u, 26,  u, u,18,
		  5,  u, u, 23, u, 27, u, 6,  u,24, 7, u,  8,  u, u, 0,};

		  x = x |(x >> 1);	//Prioagate leftmost
		  x = x |(x >> 2);  // 1-bit to the right
		  x = x |(x >> 4);
		  x = x |(x >> 8);
		  x = x |(x >>16);
		  x = x*0x06EB14F9;	//Multiplier is 7*255**3.
		  return table[x >> 26];
}

int ntz_binary_search(unsigned x){
	int n;

	if(x == 0) return (32);
	n = 1;
	if ((x & 0x0000FFFF) == 0) {n = n +16; x = x >>16;}
	if ((x & 0x000000FF) == 0) {n = n + 8; x = x >> 8;}
	if ((x & 0x0000000F) == 0) {n = n + 4; x = x >> 4;}
	if ((x & 0x00000003) == 0) {n = n + 2; x = x >> 2;}
	return n - (x & 1);
}

int ntz_minconst(unsigned x){
	unsigned y;
	int n;

	if (x == 0) return 32;
	n = 31;
	y = x <<16; if(y != 0) {n = n -16; x = y;}
	y = x << 8; if(y != 0) {n = n - 8; x = y;}
	y = x << 4; if(y != 0) {n = n - 4; x = y;}
	y = x << 2; if(y != 0) {n = n - 2; x = y;}
	y = x << 1; if(y != 0) {n = n - 1;}
	return n;
}

int ntz_binary_search_tree(char x){
	if( x & 15){
		if( x & 3){
			if( x & 1) return 0;
			else return 1;
		}
		else if( x & 4) return 2;
		else return 3;
	}
	else if( x & 0x30){
		if(x & 0x10) return 4;
		else return 5;
	}
	else if(x & 0x40) return 6;
	else if (x) return 7;
	else return 8;

}

int ntz_counting_loop(unsigned x){
	int n;

	x = ~x & (x -1);
	n = 0;				// n = 32;
	while(x != 0){		// while( x!=0 ){
		n = n+1;		// n = n-1;
		x = x >>1;		// x = x+x;
	}					// }
	return n;			// return n;
}	

int ntz_GaudentMethod(unsigned x){
	unsigned y, bz, b4, b3, b2, b1, b0;

	y = x & -x;			// Isolate rightmost 1-bit.
	bz = y ? 0 : 1;		// 1 if y = 0.
	b4 = (y & 0x0000FFFF) ? 0 : 16;
	b3 = (y & 0x0000FFFF) ? 0 :  8;
	b2 = (y & 0x0000FFFF) ? 0 :  4;
	b1 = (y & 0x0000FFFF) ? 0 :  2;
	b0 = (y & 0x0000FFFF) ? 0 :  1;
	return bz + b4 + b3 + b2 + b1 + b0;
}

int ntz_Seal(unsigned x){
	static char table[64] = 
		{32, 0, 1,12, 2, 6, u,13, 3, u, 7, u, u, u, u,14,
		 10, 4, u, u, 8, u, u,25, u, u, u, u, u,21,27,15,
		 31,11, 5, u, u, u, u, u, 9, u, u,24, u, u,20,26,
		 30, u, u, u, u,23, u,19,29, u,22,18,28,17,16, u};

		 x = (x & -x)*0x0450FBAF;
		 return table[x >> 26];
}

int ntz_De_Bruijn(unsigned x){
	static char table[32] = 
		{ 0, 1, 2,24, 3,19, 6,25,22, 4,20,10,16, 7,12,26,
		 31,23,18, 5, 21,9,15,11,30,17, 8,14,29,13,28,27};

		 if(x == 0)return 32;
		 x = (x & -x)*0x04D7651F;
		 return table[x >> 27];
}

int ntz_Reiser(unsigned x){
	static char table[37] = {32,  0,  1, 26,  2, 23, 27,
				  u,  3, 16, 24, 30, 28, 11,  u, 13,  4,
				  7, 17,  u, 25, 22, 31, 15, 29, 10, 12,
				  6,  u, 21, 14,  9,  5, 20,  8, 19, 18};

				  x =(x & -x)%37;
				  return table[x];
	
}
