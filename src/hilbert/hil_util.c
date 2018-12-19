#include <stdio.h>
#include <stdlib.h>


void hil_xy_from_s_a(unsigned s, int n, unsigned *xp,
									  unsigned *yp){
	int i;
	unsigned state, x, y, row;

	state = 0;								// Initialize.
	x = y = 0;

	for (i = 2*n - 2; i >= 0; i -= 2){		// Do n times.
		row = 4*state | (s >> i) & 3;		// Row in table.
		x = (x << 1) | (0x936C >> row) & 1;
		y = (y << 1) | (0x39C6 >> row) & 1;
		state = (0x3E6B94C1 >> 2*row) & 3;  // New state.
	}
	*xp = x;								// Pass back.
	*yp = y;								// results.
}



void hil_xy_from_s_b(unsigned s, int n, unsigned *xp,
									  unsigned *yp){
/**
 *
 * [L & S]
 *
 *
 **/
	int i, sa, sb;
	unsigned x, y, temp;

	for (i = 0; i < 2*n; i += 2){
		sa = (s >> (i + 1) & 1);			// Get bit i+1 of s.
		sb = (s >> i) & 1;					// Get bit i of s.

		if ((sa ^ sb) == 0){				// If sa, sb = 00 or 11,
			temp = x;						// swap x and y,
			x = y ^ (-sa);					// and if sa = 1,
			y = temp ^ (-sa);				// complement them.
		}
		x = (x >> 1) | (sa >> 31); 			// Prepend sa to x and
		y = (y >> 1) | ((sa ^ sb) << 31);	// (sa ^ sb) to y.
	}
	*xp = x >> (32 - n);					// Right-adjust x and y
	*yp = y >> (32 - n);					// and return them to
}											// the caller.

void hil_xy_from_s_c(unsigned s, int n, unsigned *xp,
									  unsigned *yp){
	unsigned comp, swap, cs, t, sr;

	s = s | (0x55555555 << 2*n);	// Pad s on left with 01
	sr = (s >> 1) & 0x55555555;		// (no change) groups.
	cs = ((s & 0x55555555) + sr) 	// Compute complement &
		 ^0x55555555;				// swap info in two-bit
		 							// groups.

	// Parallel prefix xor op to propagate both complement
	// and swap info together from left to right (there is 
	// no step "cs ^= cs >> 1", so in effect it computes
	// two independent parallel prefix operations on two
	// interleaved sets of sixteen bits).

	cs = cs ^ (cs >> 2);
	cs = cs ^ (cs >> 4);
	cs = cs ^ (cs >> 8);
	cs = cs ^ (cs >> 16);
	swap = cs & 0x55555555;			// Separate the swap and
	comp = (cs >> 1) & 0x55555555;	// complement bits.

	t = (s & swap) ^ comp;			// Calculate x and y in 
	s = s ^ sr ^ t ^ (t << 1);		// the odd & even bit
									// positions, resp.
	s = s & (( 1 << 2*n) - 1);		// Clear out any junk
									// on the left(unpad).

	// Now "unshuffle" to separate the x and y bits/

	t = (s ^ (s >> 1)) & 0x22222222; s = s ^ t ^ (t << 1);
	t = (s ^ (s >> 1)) & 0x0C0C0C0C; s = s ^ t ^ (t << 2);
	t = (s ^ (s >> 1)) & 0x00F000F0; s = s ^ t ^ (t << 4);
	t = (s ^ (s >> 1)) & 0x0000FF00; s = s ^ t ^ (t << 8);

	*xp = s >> 16;					// Assign the weo halves
	*yp = s & 0xFFFF;				// of t to x and y.
}


/**
 *
 * @ Compute s from coordinate
 * @ 1. compute nlz(x),nlz(y)
 * @ 2. Scan the bin(x),bin(y) and construct the s.
 *
 **/
unsigned hil_s_from_xy_a(unsigned x, unsigned y, int n){

	int i;
	unsigned state, s, row;

	state = 0;						// Initialize.
	s = 0;

	for (i = n - 1; i >= 0; i--){
		row = 4*state | 2*((x >> i) & 1) | (y >> i) & 1;
		s = (s << 2) | (0x361E9CB4 >> 2*row) & 3;
		state = (0x8FE65831 >> 2*row) & 3;
	}
	return s;
}


/**
 *
 * @ Compute s from coordinate
 * @ Lam and Shapiro Algorithm
 *
 **/
unsigned hil_s_from_xy_b(unsigned x, unsigned y, int n){

	int i, xi, yi;
	unsigned s, temp;

	s = 0;							// Initialize.
	for (i = n - 1; i >= 0; --i){
		xi = (x >> i) & 1;			// Get bit i of x.
		yi = (y >> i) & 1;			// Get bit i of y.

		if (yi == 0){
			temp = x;				// Swap x and y and,
			x = y ^ (-xi);			// if xi = 1,
			y = temp ^ (-xi);		// complement them.
		}
		s =4*s + 2*xi + (xi^yi);	// Append two bits to s.
	}
	return s;
}

/**
 *
 * @ Compute the next coordinate of current hilbert curve.
 * 
 **/
void hil_next_xy(unsigned *xp, unsigned *yp, int n){

	int i;
	unsigned x, y, state, dx, dy, row, dochange;

	x = *xp;
	y = *yp;
	state = 0;						// Initialize.
	dx = -((1 << n) - 1);			// Init. -(2**n - 1).
	dy = 0;

	for (i = n - 1; i >= 0; --i){	// Do n times.
		row = 4*state | 2*((x >> i) & 1) | (y >> i) & 1;
		dochange = (0xBDDB >> row) & 1;
		if (dochange){
			dx = ((0x16451659 >> 2*row) & 3) - 1;
			dy = ((0x51166516 >> 2*row) & 3) - 1;
		}
		state = (0x8FE65831 >> 2*row) & 3;
	}
	*xp = *xp + dx;
	*yp = *yp + dy;
}

