#include <stdio.h>

unsigned mulinv_euclid(d){	// d must be odd.
	unsigned x1, v1, x2, v2, x3, v3, q;

	x1= 0xFFFFFFFF;			
	v1 = -d;
	x2 = 1;					
	v2 = d;
	while (v2 > 1){
		q = v1/v2;
		x3 = x1 - q*x2;
		v3 = v1 - q*v2;
		x2 = x3;
		v2 = v3;
	}
	return x2;
}

unsigned mulinv_newton(unsigned d){		// d must be odd.
	unsigned xn, t;

	xn = d;
loop: t = d*xn;
	if(t == 1) return xn;
	xn = xn*(2 - t);
	goto loop;
}

