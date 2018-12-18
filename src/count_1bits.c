#include <stdlib.h>
#include <stdio.h>

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
	n = (n >> 4) - ((n >> 2) & 3) + (n & 3);	// -3 to 6.
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
int remu5(int n){
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
int remu7(int n){
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
int remu9(int n){
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