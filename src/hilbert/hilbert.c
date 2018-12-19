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