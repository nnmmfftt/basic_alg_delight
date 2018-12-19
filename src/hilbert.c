

/**
 * hilbert curve
 *
 * @ex: gcc hilbert.c
 * @		./a.out 2
 *  sys  print:
 *  0    0000    00 00
 *  0    0001    01 00
 *  1    0010    01 01
 *  2    0011    00 01
 *  1    0100    00 10
 *  1    0101    00 11
 *  0    0110    01 11
 * -1    0111    01 10
 *  0    1000    10 10
 *  1    1001    10 11
 *  0    1010    11 11
 * -1    1011    11 10
 * -1    1100    11 01
 * -2    1101    10 01
 * -1    1110    10 00
 *  0    1111    11 00
 *
 **/




#include <stdlib.h>
#include <stdio.h>

int x = -1, y = 0;				// Global variable.
int s = 0;						// Dist. aling curve.
int blen;						// Length to print.

void hilbert(int dir, int rot, int order);

void binary(unsigned k, int len, char *s){
	/**
	 * Convers the unsigned integer k to binary
	 * character form. Result is string s of length len.
	 *
	 **/
	int i;

	s[len] = 0;
	for (i = len - 1; i >= 0; --i){
		if (k & 1) s[i] = '1';
		else	   s[i] = '0';
		k = k >> 1;
	}
}
void step(int dir){
	char ii[33], xx[17], yy[17];

	switch(dir & 3){
		case 0: x = x + 1; break;
		case 1: y = y + 1; break;
		case 2: x = x - 1; break;
		case 3: y = y - 1; break;
	}
	binary(s, 2*blen, ii);
	binary(x, blen, xx);
	binary(y, blen, yy);
	printf("%5d    %s    %s %s\n", dir, ii, xx, yy);
	s = s + 1;				// Increment distance.
}

void hilbert(int dir, int rot, int order){

	if (order == 0) return ;

	dir = dir + rot;
	hilbert(dir, -rot, order - 1);
	step(dir);
	dir = dir - rot;
	hilbert(dir, rot, order - 1);
	step(dir);
	hilbert(dir, rot, order - 1);
	dir = dir - rot;
	step(dir);
	hilbert(dir, -rot, order - 1);
}

int main(int argc, char *argv[]){
	int order;

	order = atoi(argv[1]);
	blen = order;
	step(0);				// Print init. point.
	hilbert(0, 1, order);
	return 0;
}