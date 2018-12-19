#include <stdio.h>

/**
 *
 * @ a receiver and a sender
 * @ checkbits
 *
 **/

/**
 *	Bit 	Checks these bits of u
 *  p[0]	0, 1, 3, 5, ..., 31 (0 and the odd positions).
 *  p[1]	0, 2-3, 6-7, ..., 30-31 (0 and positions xxx1x).
 *  p[2]	0, 4-7, 12-15, 20-23, 28-31 (0 and posns xx1xx).
 *  p[3] 	0, 8-15, 24-31 (0 and positions x1xxx).
 * 	p[4]	0, 16-31 (0 and positions 1xxxx).
 *	p[5]	1-31
 **/

/**
 *
 * Compute the six parity check bits for the
 * message bits given in the 32-bit word u.
 * The check bits are p[5:0]. On sending, an overall parity
 * bit will be prepended to p (by another process).
 *
 **/

unsigned int checkbits(unsigned int u){
	unsigned int p0, p1, p2, p3, p4, p5, p6, p;
	unsigned int t1, t2, t3;

	// First calculate p[5:0] ignoring u[0].
	p0 = u ^ (u >> 2);
	p0 = p0 ^ (p0 >> 4);
	p0 = p0 ^ (p0 >> 8);
	p0 = p0 ^ (p0 >> 16);				// p0 is in posn 1.

	t1 = u ^ (u >> 2);
	p1 = t1 ^ (t1 >> 4);
	p1 = p1 ^ (p0 >> 8);
	p1 = p1 ^ (p0 >> 16);				// p1 is in posn 2.

	t2 = t1 ^ (t1 >> 2);
	p2 = t2 ^ (t2 >> 8);
	p2 = p2 ^ (p2 >> 16);				// p2 is in posn 4.

	t3 = t2 ^ (t2 >> 4);
	p3 = t3 ^ (t3 >> 16);				// p3 is in posn 8.

	p4 = t3 ^ (t3 >> 8);				// p4 is in posn 16.

	p5 = p4 ^ (p4 >> 16);				// p5 is in posn 0.

	p = ((p0>>1) & 1) | ((p1>>1) & 2) | ((p2>>2) & 4) |
		((p3>>5) & 8) | ((p4>>12) & 16) | ((p5 & 1) << 5);

	p = p ^ (-(u & 1) & 0x3F);			// Now account for u[0].
	return p;
}


/**
 *
 * This func looks at the received seven check
 * bits and 32 information bits (p3 and ur) and
 * dertermines how many errors occurred (under the
 * presumption that it must be 0, 1, or 2). It returns
 * with 0, 1, or 2, meaning that no errors, one error, or
 * two errors occurred. It corrects the information word
 * received (ur) if there was one error in it.
 *
 **/
int correct(unsigned int pr, unsigned int *ur){
	unsigned int po, p, syn, b;

	po = parity(pr ^ *ur);				// Compute overall parity
										// if the received data.
	p = checkbits(*ur);					// Calculate check bits
										// for the received info.
	syn = p ^ (pr & 0x3F);				// Syndrome (exclusive of
										// overall parity bit).
	if (po == 0){
		if (syn == 0) return 0;			// If no errors, return 0.
		else return 2;					// Two errors, return 2.
	}
										// One error occurred.
	if (((syn - 1) & syn) == 0)			// If syn has zero or one
		return 1;						// bits set, than the
										// error is in the check
										// bits or the overall
										// parity bit (no
										// correction reqired).

	// One error, and syn bits 5:0 tell where it is in ur.
	b = syn - 31 - (syn >> 5);			// Map syn to range 0 to 31.
 // if(syn == 0x1f) b = 0;				// (These two lines equiv.
 // else b = syn & 0x1f;				// to the one line above.)
	*ur = *ur ^ (1 << b);				// Correct the bit.
	return 1;
}