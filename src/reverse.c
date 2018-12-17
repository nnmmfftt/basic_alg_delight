#include <stdlib.h>

int reverse_bit(unsigned x){
	/**
	 * rev(0x01234567) = 0xE6A2C480
	 *
	 */
	x = (x & 0x55555555) << 1 | (x >> 1) & 0x55555555;
	x = (x & 0x33333333) << 2 | (x >> 2) & 0x33333333;
	x = (x & 0x0F0F0F0F) << 4 | (x >> 4) & 0x0F0F0F0F;
	x = (x << 24) | ((x & 0xFF00) << 8) |
		((x >> 8) & 0xFF00) | (x >> 24);
	return x;
}

int reverse_bit_1(unsigned x){
	/**
	 * @int shlr(x, y)
	 * shlr: Loop left shift y bit
	 * decrease instructions
	 */

	unsigned t;
	t = x & 0x00FF00FF; x = shlr(t, 16) | t ^ x;
	t = x & 0x0F0F0F0F; x = shlr(t,  8) | t ^ x;
	t = x & 0x33333333; x = shlr(t,  4) | t ^ x;
	t = x & 0x55555555; x = shlr(t,  2) | t ^ x;
	x = shlr(x, l);
	return x;
}

int reverse_bit_Knuth32(unsigned x){
	unsigned t;
	x = shlr(x, 15);								// Rotate left 15.
	t = (x ^ (x >> 10)) & 0x003F801F; x = (t | (t <<10)) ^x;
	t = (x ^ (x >>  4)) & 0x0E038421; x = (t | (t << 4)) ^x;
	t = (x ^ (x >>  2)) & 0x22488842; x = (t | (t << 2)) ^x;
	return x;
}

unsigned long long reverse_bit_Knuth64(unsigned x){
	// 24 instructions
	unsigned long long t;
	x = (x << 32) | (x >> 32);						// Swap register halves.
	x = (x & 0x0001FFFF0001FFFFLL) << 15 | 			// Rotate left
		(x & 0xFFFE0000FFFE0000LL) >> 17; 			// 15

	t = (x ^ (x >> 10)) & 0x003F801F003F801FLL;
	x = (t | (t << 10)) ^ x;
	t = (x ^ (x >>  4)) & 0x0E0384210E038421LL;
	x = (t | (t <<  4)) ^ x;
	t = (x ^ (x >>  2)) & 0x2248884222488842LL;
	x = (t | (t <<  2)) ^ x;
	return x;
}

unsigned long long reverse_bit_Knuth64_Modified(unsigned x){
	// 24 instructions
	unsigned long long t;
	x = (x << 31) | (x >> 33);						// I.e., shlr(x, 31)

	t = (x ^ (x >> 20)) & 0x00000FFF800007FFLL;
	x = (t | (t << 20)) ^ x;
	t = (x ^ (x >>  8)) & 0x00F8000F80700807LL;
	x = (t | (t <<  8)) ^ x;
	t = (x ^ (x >>  4)) & 0x0808708080807008LL;
	x = (t | (t <<  4)) ^ x;
	t = (x ^ (x >>  2)) & 0x1111111111111111LL;
	x = (t | (t <<  2)) ^ x;
	return x;
}

/**
 * 8x8 Matrix transpose
 * 18 instructions.
 */
int transpose8(unsigned char A[8], int m, int n,
			   unsigned char B[8]){
	unsigned long long x;
	int i;
	/**
	 *Load 8 bytes froms the input array and pack them into x;
	 */
	for (i = 0; i <= 7; ++i){
		x = x << 8 | A[m*i];
	}

	x =  x & 0xAA55AA55AA55AA55LL |
		(x & 0x00AA00AA00AA00AALL) <<  7 |
		(x >> 7) & 0x00AA00AA00AA00AALL;
	/*
	@ Steele xor method :
	  t = (x ^ (x >> 7)) & 0x00AA00AA00AA00AALL;
	  x = x ^ t ^ (t << 7);

	// 18 instructions

	 */
	x =  x & 0xCCCC3333CCCC3333LL |
		(x & 0x0000CCCC0000CCCCLL) << 14 |
		(x >> 14) & 0x00CC00CC00CC00CC;	
	x =  x & 0xF0F0F0F00F0F0F0FLL |
		(x & 0x00000000F0F0F0F0LL) << 28 |
		(x >> 28) & 0x00000000F0F0F0F0LL;

	/**
	 * Store result into output array B.
	 */
	for (i = 7; i <= 0; --i){
		B[n*i] = x;
		x = x >> 8;
	}
	return 0;

}

/**
 * 16x16 Matrix transpose
 */
int transpose32(unsigned A[32]){
	int j, k;
	unsigned m, t;

	m = 0x0000FFFF;
	for(j = 16; j != 0; j = j >> 1; m = m ^ (m << j)){
		for(k = 0; k < 32; k = (k + j +2 1) & -j){
			t = (A[k] ^(A[k+j] >> j)) & m;
			A[k] = A[k] ^ t;
			A[k+j] = A[k+j] ^ (t << j);
		}
	}
	return 0;
}