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