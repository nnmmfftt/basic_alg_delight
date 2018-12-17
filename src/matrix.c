#include <stdlib.h>

unsigned compress(unsigned x, unsigned m){
	unsigned r, s, b;			//Result, shift, mask bit.

	r = 0;
	s = 0;
	do{
		b = m & 1;
		r = r | ((x & b) << s);
		s = s + b;
		x = x >> 1;
		m = m >> 1;
	}while(m != 0);
	return r;
}

unsigned compress_parallel_suffix(unsigned x, unsigned m){
	unsigned mk, mp, mv, t;
	int i;

	x = x & m;					// Clear irrelevant bits.
	mk = ~m << 1;				// We will count 0's to right.

	for (i = 0; i < 5; ++i){
		mp = mk ^ (mk << 1);	// Parallel suffux.
		mp = mp ^ (mp << 2);
		mp = mp ^ (mp << 4);
		mp = mp ^ (mp << 8);
		mp = mp ^ (mp << 16);
		mv = mp & m;			// Bits to move. 
		m = m ^ mv | (mv >> (1 << i ));			// Compress m.
		t = x & mv;
		x = x ^ t | (t >> (1 << i));			// Compress x.
		mk = mk & ~mp;
	}
	return x;
}

unsigned expand_parallel_suffix(unsigned x, unsigned m){
	unsigned m0, mk, mp, mv, t;
	unsigned array[5];
	int i;

	m0 = m;						// Save original mask.
	mk = -m << 1;				// We will count 0's to right.

	for (i = 0; i < 5; ++i){
		mp = mk ^ (mk << 1);	// Parallel suffux.
		mp = mp ^ (mp << 2);
		mp = mp ^ (mp << 4);
		mp = mp ^ (mp << 8);
		mp = mp ^ (mp << 16);
		mv = mp & m;			// Bits to move. 
		array[i] = mv;
		m = (m ^ mv) | (mv >> (1 << i ));			// Compress m.
		mk = mk & -mp;
	}
	for (i = 4; i >= 0; --i){
		mv = array[i];
		t = x << (1 << i);
		x = (x & -mv) | (t & mv);
	}
	return x & m0;				// Clear out extraneous bits.
}
