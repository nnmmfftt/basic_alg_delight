#include <stdlib.h>
/**
 *
 * @compute signed div magic number.
 *
 **/
struct ms {
	int M;			// Magic number
	int s;			// and shift amount.
};
struct ms magic(int d){
	/**
	 *
	 * Must have 2 <= d <= 2 **31-1
	 * or -2 **31 <= d <= -2.
	 *
	 **/
	int p;
	unsigned ad, and, delta ,q1, r1, q2, r2, t;
	const unsigned two31 = 0x80000000;		//2**31.
	struct ms mag;

	ad = abs(d);
	t = two31 + ((unsigned)d >> 31);
	anc = t - 1 - t % ad;					// Absolute value of nc.
	p = 31;									// Init. p.
	q1 = two31/anc;							// Init. q1 = 2**p/|nc|.
	r1 = two31 - q1*anc;					// Init. r1 = rem(2**p,|nc|).
	q2 = two31/ad;							// Init. q2 = 2**p/|d|.
	r2 = two31 - q2*ad;						// Init. r2 = rem(2**p, |d|).
	do{
		p = p+1;
		q1 = 2 * q1;						// Update q1 = 2**p/|nc|.
		r1 = 2 * r1;						// Update r1 = rem(2**p, |nc|).
		if (r1 >= anc){						// (Must be an unsigned
		   q1 = q1 +1;						// comparison here.)
		   r2 = r2 -ad;
		   }
		   delta = ad -r2;
		delta = ad -r2;
	} while(q1 <delta || (q1 == delta && r1 == 0));

	mag.M = q2 +1;
	if (d < 0) mag.M = -mag.M;				// Magic number and
	mag.s = p -32;							// shift amount to return.
	return mag;
}

/**
 *
 * @compute unsigned div magic number
 *
 **/
	struct mu {
	unsigned M;		// Magic number,
	int a;			// "add" indicator,
	int s;			// and shift amount.
}

struct mu magicu(unsigned d){
					// Must have 1 <= d <= 2**32-1.
	int p;
	unsigned nc, delta, q1, r1, q2, r2;
	struct mu magu;

	magu.a = 0;			// Initialize "add" indicator.
	nc = -1 - (-d)%d;	// Unsigned arithmetic here.
	p = 31;				// Init. p.
	q1 = 0x80000000/nc; // Init. q1 = 2**p/nc.
	r1 = 0x80000000 - q1*nc; // Init. r1 = rem(2**p, nc).
	q2 = 0x7FFFFFFF/d;		 // Init. q2 = (2**p - 1)/d.
	r2 = 0x7FFFFFFF - q2*d;  // Init. r2 = rem(2**p -1, d).
	do{
		p = p+1;
		if(r1 >= nc-r1 ){
			q1 = 2*q1 +1;	 // Update q1.
			r1 = 2*r1 -nc;	 // Update r1.
		}
		else {
			q1 = 2*q1;
			r1 = 2*r1;
		}
		if(r2 + 1 >= d - r2){
			if(q2 >= 0x7FFFFFFF) magu.a = 1;
			q2 = 2*q2 +1;	 // Update q2.
			r2 = 2*r2 +1 -d; // Update r2.
		}
		else {
			if(q2 >= 0x80000000) magu.a =1;
			q2 = 2*q2;
			r2 = 2*r2 +1;
			}
		delta = d - 1 -r2;
	} while (p < 64 &&
			(q1 < delta || (q1 == delta && r1 == 0)));

	magu.M = q2 +1;			 // Magic number
	magu.s = p -32;			 // and shift amount to return
	return magu;			 // (magu.a was set above).
}

/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -------------------------(unsigned)------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 **/
unsigned divu3(unsigned n){
	/**
	 *
	 * multiply high unsigned
	 * unsigned div by 3
	 **/
	unsigned n0, n1, w0, w1, w2, t, q;

	n0 = n & 0xFFFF;
	n1 = n >> 16;
	w0 = n0*0xAAAB;
	t = n1*0xAAAB + (w0 >> 16);
	w1 = t & 0xFFFF;
	w2 = t >> 16;
	w1 = n0*0xAAAA + w1;
	q = n1*0xAAAA + w2 + (w1 >> 16);
	return q >> 1;
}

/**
 *
 * more precise than divu3.
 *
 **/
unsigned divu3_percise(unsigned n){

	unsigned q, r;

	q = (n >> 2) + (n >> 4);		// q = n*0.0101 (approx).
	q = q + (q >> 4);				// q = n*0.01010101.
	q = q + (q >> 8);
	q = q + (q >> 16);
	r = n - q*3;					// 0 <= r <= 15.
	return q + (11*r >> 5);			// Returning q + r/3.
 // return q + (5*(r + 1) >> 4);	// Alternative 1.
 // return q + ((r + 5 + (r << 2)) >> 4);
									// Alternative 2.
}

// div by 5 (unsigned)
unsigned divu5a(unsigned n){
	unsigned q, r;

	q = (n >> 3) + (n >> 4);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	r = n - q*5;
	return q + (13*r >> 6);
}

// div by 5 (unsigned)
unsigned divu5b(unsigned n){
	unsigned q, r;

	q = (n >> 1) + (n >> 2);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	q = q >> 2;
	r = n - q*5;
	return q + (7*r >> 5);
 // return q + (r>4) + (r>9);
}

// div by 6 (unsigned)
unsigned divu6a(unsigned n){
	unsigned q, r;

	q = (n >> 3) + (n >> 5);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	r = n - q*6;
	return q + (11*r >> 6);
}

// div by 6 (unsigned)
unsigned divu6b(unsigned n){
	unsigned q, r;

	q = (n >> 1) + (n >> 3);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	q = q >> 2;
	r = n - q*6;
	return q + ((r + 2) >> 3);
 // return q + (r > 5);
}

// div by 7 (unsigned)
unsigned divu7(unsigned n){
	unsigned q, r;

	q = (n >> 1) + (n >> 4);
	q = q + (q >> 6);
	q = q + (q >> 12) + (q >> 24);
	q = q >> 2;
	r = n - q*7;
	return q + ((r + 1) >> 3);
 // return q + (r > 6);
}

// div by 9 (unsigned)
unsigned divu9(unsigned n){
	unsigned q, r;

	q = n - (n >> 3);
	q = q + (q >> 6);
	q = q +( q >> 12) + (q >> 24);
	q = q >> 3;
	r = n - q*9;
	return q + ((r + 7) >> 4);
 // return q + (r > 8);
}



/**
 * the div al based:
 * 8/10 ≈ 0.1100 1100 1100 1100 1100 1100 1100 1100,
 * 8/11 ≈ 0.1011 1010 0010 1110 1000 1011 1010 0010,
 * 8/12 ≈ 0.1010 1010 1010 1010 1010 1010 1010 1010,
 * 8/13 ≈ 0.1001 1101 1000 1001 1101 1000 1001 1101.
 *
 **/
// div by 10 (unsigned)
unsigned divu10(unsigned n){
	unsigned q, r;

	q = (n >> 1) + (n >> 2);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	q = q >> 3;
	r = n - q*10;
	return q + ((r + 6) >> 4);
 // return q + (r > 9);
}

// div by 11 (unsigned)
unsigned divu11(unsigned n){
	unsigned q, r;

	q = (n >> 1) + (n >> 2) -
		(n >> 5) + (n >> 7);
	q = q + (q >> 10);
	q = q + (q >> 20);
	q = q >> 3;
	r = n - q*11;
	return q + ((r + 5) >> 4);
 // return q + (r > 10);
}

// div by 12 (unsigned)
unsigned divu12(unsigned n){
	unsigned q, r;

	q = (n >> 1) + (n >> 3);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	q = q >> 3;
	r = n - q*12;
	return q + ((r + 4) >> 4);
 // return q + (r > 11);
}

// div by 13 (unsigned)
unsigned divu13(unsigned n){
	unsigned q, r;

	q = (n >> 1) + (n >> 4);
	q = q + (q >> 4) + (q >> 5);
	q = q + (q >> 12) + (q >> 24);
	q = q >> 3;
	r = n - q*13;
	return q + ((r + 3) >> 4);
 // return q + (r > 12);
}

/**
 *
 *   64/100 ≈ 0.1010 0011 1101 0111 0000 1010 0011 1101,
 * 512/1000 ≈ 0.1000 0011 0001 0010 0110 1110 1001 0111.
 *
 **/
// div by 100 (unsigned)
unsigned divu100(unsigned n){
	unsigned q, r;

	q = (n >> 1) + (n >> 3) + (n >> 6) - (n >> 10) +
		(n >> 12) + (n >> 13) - (n >> 16);
	q = q + (q >> 20);
	q = q >> 6;
	r = n - q*100;
	return q + ((r + 28) >> 7);
 // return q + (r > 99);
}

// div by 1000 (unsigned)
unsigned divu1000(unsigned n){
	unsigned q, r, t;

	t = (n >> 7) + (n >> 8) + (n >> 12);
	q = (n >> 1) + t + (n >> 15) + (t >> 11) + (t >> 14);
	q = q >> 9;
	r = n - q*1000;
	return q + ((r + 24) >> 10);
 // return q + (r > 999);
}

/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -------------------------(signed)--------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 **/

// div by 3 (signed)
int divs3(int n){
	int q, r;

	n = n + (n >>31 & 2);			// Add 2 if n < 0.
	q = (n >> 2) + (n >> 4);		// q = n*0.0101 (approx).
	q = q + (q >> 4);				// q = n*0.01010101.
	q = q + (q >> 8);
	q = q + (q >> 16);
	r = n - q*3;					// 0 <= r <= 14.
	return q + (11*r >> 5);			// Returning q + r/3.
 // return q + (5*(r + 1) >> 4);	// Alternative 1.
 // return q + ((r + 5 + (r << 2)) >> 4);
									// Alternative 2.
}

// div by 5 (signed)
int divs5(int n){
	int q, r;

	n = n + (n >> 31 & 4);
	q = (n >> 1) + (n >> 2);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	q = q >> 2;
	r = n - q*5;
	return q + (7*r >> 5);
 // return q + (r > 4) + (r > 9);
}

// div by 6 (unsigned)
int divs6(int n){
	int q, r;

	n = n + (n >> 31 & 5);
	q = (n >> 1) + (n >> 3);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	q = q >> 2;
	r = n - q*6;
	return q + ((r + 2) >> 3);
 // return q + (r > 5);
}

// div by 7 (unsigned)
int divs7(int n){
	int q, r;

	n = n + (n >> 31 & 6);
	q = (n >> 1) + (n >> 4);
	q = q + (q >> 6);
	q = q + (q >> 12) + (q >> 24);
	q = q >> 2;
	r = n - q*7;
	return q + ((r + 1) >> 3);
 // return q + (r > 6);
}

// div by 9 (unsigned)
int divs9(int n){
	int q, r;

	n = n + (n >> 31 & 8);
	q = (n >> 1) + (n >> 2) + (n >> 3);
	q = q + (q >> 6);
	q = q + (q >> 12) + (q >> 24);
	q = q >> 3;
	r = n - q*9;
	return q + ((r + 7) >> 4);
 // return q + (r > 8);
}

// div by 10 (unsigned)
int divs10(int n){
	int q, r;

	n = n + (n >> 31 & 9);
	q = (n >> 1) + (n >> 2);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	q = q >> 3;
	r = n - q*10;
	return q + ((r + 6) >> 4);
 // return q + (r > 9);
}

// div by 11 (unsigned)
int divs11(int n){
	int q, r;

	n = n + (n >> 31 & 10);
	q = (n >> 1) + (n >> 2) - 
		(n >> 5) + (n >> 7);
	q = q + (q >> 10);
	q = q + (q >> 20);
	q = q >> 3;
	r = n - q*11;
	return q + ((r + 5) >> 4);
 // return q + (r > 10);
}

// div by 12 (unsigned)
int divs12(int n){
	int q, r;

	n = n + (n >> 31 & 11);
	q = (n >> 1) + (n >> 3);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	q = q >> 3;
	r = n - q*12;
	return q + ((r + 4) >> 4);
 // return q + (r > 11);
}

// div by 13 (unsigned)
int divs13(int n){
	int q, r;

	n = n + (n >> 31 & 12);
	q = (n >> 1) + (n >> 4);
	q = q + (q >> 4) + (q >> 5);
	q = q + (q >> 12) + (q >> 24);
	q = q >> 3;
	r = n - q*13;
	return q + ((r + 3) >> 4);
 // return q + (r > 12);
}

// div by 100 (signed)
int divu100(int n){
	int q, r;

	n = n + (n >> 31 & 99);
	q = (n >> 1) + (n >> 3) + (n >> 6) - (n >> 10) +
		(n >> 12) + (n >> 13) - (n >> 16);
	q = q + (q >> 20);
	q = q >> 6;
	r = n - q*100;
	return q + ((r + 28) >> 7);
 // return q + (r > 99);
}

// div by 1000 (signed)
int divu1000(int n){
	int q, r, t;

	n = n + (n >> 31 & 999);
	t = (n >> 7) + (n >> 8) + (n >> 12);
	q = (n >> 1) + t + (n >> 15) + (t >> 11) + (t >> 14) +
		(n >> 26) (t >> 21);
	q = q >> 9;
	r = n - q*1000;
	return q + ((r + 24) >> 10);
 // return q + (r > 999);
}