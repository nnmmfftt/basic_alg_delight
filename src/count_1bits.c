#include <stdlib.h>
#include <stdio.h>




/** 
 *********************************************************************************
 *********************************************************************************
 *********************************************************************************
 *********************************************************************************
 *********************************************************************************
 *********************************************************************************
 *********************************************************************************
 *********************************************************************************
/**
 * @pop:
 * -----------------------Population count instruction-----------------------
 **/
int pop_badbits(int num){
	int count = 0;
    unsigned int flag = 1;
    while(flag){
        if(num & flag)
            count++;
        flag = flag << 1;
    }
    return count;
}

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



/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -------------------------(unsigned)------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * ------------------@ using digit summing method ------------------
 **/

/**
 * Lookup register & Population counting method compute remainder signed int div by 3.
**/
int remu3a(unsigned n){
	 n = pop(n ^ 0xAAAAAAAA) + 23;			// Now 23 <= n <= 55.
	 n = pop(n ^ 0x2A) - 3;					// Now -3 <= n <= 2.
	 return n + (((int)n >> 31) & 3); 		// (signed shift)
}


/**
 * Lookup memory & Population counting method compute remainder unsigned int div by 3.
 **/
int remu3b(unsigned n){
	static char table[33] = {2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
			0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
			0, 1, 2, 0, 1};

	n = pop(n ^ 0xAAAAAAAA);
	return table[n];
}

/**
 * Lookup register method compute remainder unsigned int div by 3.
**/
int remu3c(unsigned n){
	n = (n >> 16) + (n & 0xFFFF);				// Max 0x1FFFE.
	n = (n >>  8) + (n & 0x00FF);				// Max 0x2FD.
	n = (n >>  4) + (n & 0x000F);				// Max 0x3D.
	n = (n >>  2) + (n & 0x0003);				// Max 0x11.
	n = (n >>  2) + (n & 0x0003);				// Max 0x6.
	return (0x0924 >> (n << 1)) & 3;
}

/**
 * Lookup memory method compute remainder unsigned int div by 3.
**/
int remu3d(unsigned n){
	static char table[62] =  {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
			0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
			0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
			0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1};

	n = (n >> 16) + (n & 0xFFFF);		// Max 0x1FFFE.
	n = (n >>  8) + (n & 0x00FF);		// Max 0x2FD.
	n = (n >>  4) + (n & 0x000F);		// Max 0x3D.
	return table[n];
}


/**
 * Lookup register method compute remainder unsigned int div by 5.
**/
int remu5(unsigned n){
	n = (n >> 16) + (n & 0xFFFF);				// Max 0x1FFFE.
	n = (n >>  8) + (n & 0x00FF);				// Max 0x2FD.
	n = (n >>  4) + (n & 0x000F);				// Max 0x3D.
	n = (n >>  4) - ((n >> 2) & 3) + (n & 3);	// -3 to 6.
	return (01043210432 >> 3*(n + 3)) & 7;		// Octal const.
}

/**
 * Lookup memory method compute remainder unsigned int div by 7.
**/
int remu7(unsigned n){
	static char table[75] =  {0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6,
	 	 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6,
	 	 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6,
	 	 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4};

	n = (n >> 15) + (n & 0x7FFF);		// Max 0x27FFE.
	n = (n >>  9) + (n & 0x001FF);		// Max 0x33D.
	n = (n >>  6) + (n & 0x0003F);		// Max 0x4A.
	return table[n];
}

/**
 * Lookup memory method compute remainder unsigned int div by 3.
**/
int remu9(unsigned n){
	int r;
	static char table[75] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 
   0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1, 2, 3, 4, 5, 6, 7, 8, 
   0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1, 2, 3, 4, 5, 6, 7, 8,
   0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1, 2, 3, 4, 5, 6, 7, 8, 
   0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1, 2};

	r = (n & 0x7FFF) - (n >> 15);		// FFFE0001 to 7FFF.
	r = (r & 0x01FF) - (r >>  9);   	// FFFFFFC1 to 2FF.
	r = (r & 0x003F) - (r >>  6); 		// 0 to 4A.
	return table[r];
}

/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -------------------------(signed)--------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * ------------------@ using digit summing method ------------------
 **/

/**
 * Lookup memory method compute remainder signed int div by 3.
 **/
int rems3(int n){
	unsigned r;

	static char table[62] =  {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
			0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
			0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
			0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1};

	n = (n >> 16) + (n & 0xFFFF);		// Max 0x1FFFE.
	n = (n >>  8) + (n & 0x00FF);		// Max 0x2FD.
	n = (n >>  4) + (n & 0x000F);		// Max 0x3D.
	r = table[r];
	return r - (((unsigned)n >> 31) << (r & 2));
}


/**
 * Lookup memory method compute remainder signed int div by 5.
**/
int rems5(int n){
	int r;
	static char table[62] = {2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4,
		0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 
		0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 
		0, 1, 2, 3, 4, 0, 1, 2, 3};
	r = (r >> 16) + (n & 0xFFFF);				// FFFF8000 to 17FFE.
	r = (r >>  8) + (r & 0x00FF);				// FFFFFF80 to 27D.
	r = (r >>  4) + (r & 0x000F);				// -8 to 53 (decimal).
	r = table[r+8];
	return r - (((int)(n & -r) >> 31) & 5);
}

/**
 * Lookup memory method compute remainder signed int div by 7.
**/
int rems7(int n){
	int r;
	static char table[75] =        {5,6, 0,1,2,3,4,5,6,
		   0,1,2,3,4,5,6, 0,1,2,3,4,5,6, 0,1,2,3,4,5,6,
		   0,1,2,3,4,5,6, 0,1,2,3,4,5,6, 0,1,2,3,4,5,6,
		   0,1,2,3,4,5,6, 0,1,2,3,4,5,6, 0,1,2,3,4,5,6, 0,1,2};
	r = (r >> 15) + (n & 0x7FFF);				// FFFF8000 to 17FFE.
	r = (r >>  9) + (r & 0x001FF);				// FFFFFF80 to 2BD.
	r = (r >>  6) + (r & 0x0003F);				// -2 to 72 (decimal).
	r = table[r+2];
	return r - (((int)(n & -r) >> 31) & 7);
}

/**
 * Lookup memory method compute remainder signed int div by 9.
**/
int rems9(int n){
	int r;
	static char table[75] =  {7,8, 0,1,2,3,4,5,6,7,8,
				0,1,2,3,4,5,6,7,8, 0,1,2,3,4,5,6,7,8,
				0,1,2,3,4,5,6,7,8, 0,1,2,3,4,5,6,7,8,
				0,1,2,3,4,5,6,7,8, 0,1,2,3,4,5,6,7,8,
				0,1,2,3,4,5,6,7,8, 0};
	r = (n & 0x7FFF) - (n >> 15);				// FFFF70001 to 17FFF.
	r = (r & 0x001FF) - (r >>  9);				// FFFFFF41 to 0x27F.
	r = (r & 0x0003F) - (r >>  6);				// -2 to 72 (decimal).
	r = table[r+2];
	return r - (((int)(n & -r) >> 31) & 9);
}

/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -------------------------(unsigned)------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -------------------@ using mutiply method------------------------
 **/

/**
 * Using mutiply method to compute remainder unsigned int div. by 3.
**/
int remu3a(unsigned n){
	return (0x55555555*n + (n >> 1) - (n >> 3)) >> 30;
}

/**
 * Using enpanded mutiply method to compute remainder unsigned int div. by 3.
**/
int remu3b(unsigned n){
	unsigned r;

	r = n + (n << 2);
	r = r + (r << 4);
	r = r + (r << 8);
	r = r + (r << 16);
	r = r + (n >> 1);
	r = r - (n >> 3);
	return r >> 30;
}

/**
 * Using mutiply method to compute remainder unsigned int div. by 5.
 * @ (in-register)
 **/
int remu5(unsigned n){
	n = (0x33333333*n + (n >> 3)) >> 29;
	return (0x04432210 >> (n << 2)) & 7;
}

/**
 * Using mutiply method to compute remainder unsigned int div. by 7.
 * @ (in-register)
 **/
int remu7(unsigned n){
	n = (0x24924924*n + (n >> 1) + (n >> 4)) >> 29;
	return n & ((int)(n - 7) >> 31);
}

/**
 * Using mutiply method to compute remainder unsigned int div. by 9.
 * @ (memory)
 **/
int remu9(unsigned n){
	static char table[16] = {0, 1, 1, 2, 2, 3, 3, 4,
							 5, 5, 6, 6, 7, 7, 8, 8};
	n = (0x1C71C71C*n + (n >> 1)) >> 28;
	return table[n];
}

/**
 * Using mutiply method to compute remainder unsigned int div. by 10.
 * @ (memory)
 **/
int remu10(unsigned n){
	static char table[16] = {0, 1, 2, 2, 3, 3, 4, 5,
							 5, 6, 7, 7, 8, 8, 9, 0};
	n = (0x19999999*n + (n >> 1) + (n >> 3)) >> 28;
	return table[n];
}

/**
 * Using Keane method to compute remainder unsigned int div. by 63.
 * @ Keane Method
 **/
int remu63(unsigned n){
	unsigned t;

	t = (((n >> 12) + n) >> 10) + (n << 2);
	t = ((t >> 6) + t + 3) & 0xFF;
	return (t -(t >> 6)) >> 2;
}

/**
 * Using mutiply method to compute remainder unsigned int div. by 63.
 * @ (in-register)
 **/
int remu10(unsigned n){
	n = (0x04104104*n + (n >> 4) + (n >> 10)) >> 26;
	return n & ((n - 63) >> 6);				// Change 63 to 0.
}

/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * --------------------------(signed)-------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -------------------@ using mutiply method------------------------
 **/

/**
 * Using mutiply method to compute remainder signed int div. by 3.
 * @ (in-register)
 **/
int rems3(int n){
	unsigned r;

	r = n;
	r = (0x55555555*r + (r >> 1) - (r >> 3)) >> 30;
	return r - (((unsigned)n >> 31) << (r & 2));
}


/**
 * Using mutiply method to compute remainder signed int div. by 5.
 * @ (Memory)
 **/
int rems5(int n){
	unsigned r;
	static signed char table[16] = {0, 1, 2, 2, 3, u, 4, 0,
									u, 0,-4, u,-3,-2,-2,-1};
	r = n;
	r = ((0x33333333*r) + (r >> 3)) >> 29;
	return table[r + (((unsigned)n >> 31) << 3)];
}

/**
 * Using mutiply method to compute remainder signed int div. by 7.
 * @ (in-register)
 **/
int rems7(int n){
	unsigned r;
	
	r = n - (((unsigned)n >> 31) << 2);			// Fix for sign.
	r = ((0x24924924*r) + (r >> 1) + (r >> 4)) >> 29;
	r = r & ((int)(r - 7) >> 31);				// Change 7 to 0.
	return r - (((int)(n & -r) >> 31) & 7);		// Fix n < 0 case.
}



/**
 * Using mutiply method to compute remainder signed int div. by 9.
 * @ (Memory)
 **/
int rems9(int n){
	unsigned r;
	static signed char table[32] = {0, 1, 1, 2, u, 3, u, 4,
									5, 5, 6, 6, 7, u, 8, u,
								   -4, u,-3, u,-2,-1,-1, 0,
									u,-8, u,-7,-6,-6,-5,-5};
	r = n;
	r = ((0x1C71C71C*r) + (r >> 1)) >> 28;
	return table[r + (((unsigned)n >> 31) << 4)];
}



/**
 * Using mutiply method to compute remainder signed int div. by 10.
 * @ (Memory)
 **/
int rems9(int n){
	unsigned r;
	static signed char table[32] = {0, 1, u, 2, 3, u, 4, 5,
									5, 6, u, 7, 8, u, 9, u,
								   -6,-5, u,-4,-3,-3,-2, u,
								   -1, 0, u,-9, u,-8,-7, u};
	r = n;
	r = ((0x19999999*r) + (r >> 1) + (r >> 3)) >> 28;
	return table[r + (((unsigned)n >> 31) << 4)];
}


/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -------------------------(unsigned)------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -------------------@ using exact division------------------------
 **/


/**
 * Using exact division method to compute remainder unsigned int div. by 3.
 * @ (in-register)
 **/
unsigned divu3(unsigned n){
	unsigned r;

	r = (0x55555555*n + (n >> 1) - (n >> 3)) >> 30;
	return (n - r)*0xAAAAAAAB;
}



/**
 * Using exact division method to compute remainder unsigned int div. by 10.
 * @ (Memory)
 **/
unsigned divu10(unsigned n){
	unsigned r;
	static char table[16] = {0, 1, 2, 2, 3, 3, 4, 5,
							 5, 6, 7, 7, 8, 8, 9, 0};

	r = (0x19999999*n + (n >> 1) + (n >> 3)) >> 28;
	r = table[r];
	return ((n - r) >> 1)*0xCCCCCCCD;
}




/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * --------------------------(signed)-------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -------------------@ using exact division------------------------
 **/

/**
 * Using exact division method to compute remainder unsigned int div. by 3.
 * @ (in-register)
 **/
int divu3(int n){
	unsigned r;
	
	r = n;
	r = (0x55555555*r + (r >> 1) - (r >> 3)) >> 30;
	r = r - (((unsigned)n >> 31) << (r & 2));
	return (n - r)*0xAAAAAAAB;
}

/**
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
**/