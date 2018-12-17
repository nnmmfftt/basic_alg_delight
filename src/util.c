#include <stdlib.h>
#include <stdio.h>

int add_before_overflow(){
	unsigned int i = 0;
	for (i ;i<0xFFFFFFFF;++i){
		continue;
	}
	printf("%u",i);
}

void ld_Gosper(int (*f)(int), int X0, int *mu_1,
							  int *mu_u, int *lambda){
	int Xn, k, m, kmax, n, lg1;
	int T[33];

	T[0] = X0;
	Xn = X0;
	for (n = 1;; n++){
		Xn = f(Xn);
		kmax = 31-nlz(n);		// Floor(log2 n).
		for(k = 0; k <= kmax; k++){
			if(Xn == T[k]) goto L;
		}
		T[ntz(n+1)] = Xn;		// No match.
	}
L:
	// Compute m = max{i|i<n and ntz(i+1) = k}.

	m = ((((n >> k) -1) |1) << k) -1;
	*lambda = n-m;
	lg1 = 31 - nlz(*lambda -1);     // Ceil(log2 lambda) -1.
	*mu_u = m;					    // Upper bound on mu.
	*mu_l = m - max(1, 1<< lg1) +1; // Lower bound on mu.

}

int zbytel_FromtestSequence(unsigned x){
	if 				((x >>24) == 0) return 0;
	else if ((x & 0x00FF0000) == 0) return 1;
	else if ((x & 0x0000FF00) == 0) return 2;
	else if ((x & 0x000000FF) == 0) return 3;
	else return 4;
}

int zbytel_Nobranch(unsigned x){
	unsigned y;
	int n;
						//Original byte: 00 80 other
	y = (x & 0x0F0F0F0F) + 0x7F7F7F7F; //7F 7F 1xxxxxxx
	y = -(y | x | 0x7F7F7F7F);		   //80 00 00000000
	n = nlz(y) >> 3;	// n = 0 ... 4, 4 if x
//  12 instructions
//  n = (32-nlz(-y & (y-1))) >> 3;
	return n;			// has no 0-byte.
}


/*
int main(){
	add_before_overflow();
	return 0;
}

*/
