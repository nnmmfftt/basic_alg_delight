#include <stdlib.h>

/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 **/

/**
 * Lookup method to compute log unsigned int base 10.
 * @ (Memory)
 **/
int ilog10a(unsigned x){
	int i;
	static unsigned table[11] = {0, 9, 99, 999, 9999,
		99999, 999999, 9999999, 99999999, 999999999,
		0xFFFFFFFF};

	for (i = -1; ; i++){
		if (x <= table[i+1]) return i;
	}
}


/**
 * Lookup method to compute log unsigned int base 10.
 * @ (in-register)
 **/
int ilog10b(unsigned x){
	int i,p;
	p = 1;
	for (i = -1; i <= 8; i++){
		if(x < p) return i;
		p = 10*p;
	}
	return i;
}



/**
 * Binary search method to compute log unsigned int base 10.
 * @ (in-register)
 **/
int ilog10c(unsigned x){
	if (x > 99)
		if (x < 1000000)
			if (x < 10000)
				return 3 + ((int)(x - 1000) >> 31);
			else 
				return 5 + ((int)(x - 100000) >> 31);
		else
			if (x < 100000000)
				return 7 + ((int)(x - 10000000) >> 31);
			else return 9 + ((int)((x - 1000000000)&-x) >> 31);
	else 
		if(x > 9) return 1;
		else	  return ((int)(x - 1) >> 31);
}



/**
 * Lookup method with 2 list to compute log unsigned int base 10.
 * @ (Memory)
 **/
int ilog10d(unsigned x){
	int y;
	static unsigned char table1[33] = {9, 9, 9, 8, 8, 8, 
		7, 7, 7, 6, 6, 6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 3, 
		2, 2, 2, 1, 1, 1, 0, 0, 0, 0};
		static unsigned table2[10] = {1, 10, 100, 1000, 10000, 
			100000, 1000000, 10000000, 100000000, 1000000000};

	y = table1[nlz(x)];
	if (x < table2[y]) y = y - 1;
	return y;
}	




/**
 * Lookup 2 list and no branch method to compute log unsigned int base 10.
 * @ (Memory)
 **/
int ilog10d(unsigned x){
	int y;
	static unsigned char table1[33] = {10, 9, 9, 8, 8, 8,
		7, 7, 7, 6, 6, 6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 3,
		2, 2, 2, 1, 1, 1, 0, 0, 0, 0};
		static unsigned table2[11] = {1, 10, 100, 1000, 10000, 
			100000, 1000000, 10000000, 100000000, 1000000000,
			0};

	y = table1[nlz(x)];
	y = y - ((x - table2[y]) >> 31);
	return y;
}





/**
 * Lookup 1 list method to compute log unsigned int base 10.
 * @ (Memory)
 **/
int ilog10e(unsigned x){
	int y;
	static unsigned char table[10] = {0, 9, 99, 999, 9999,
		99999, 999999, 9999999, 99999999, 99999999};

	y = (9*(31 - nlz(x))) >> 5;
	if (x > table[y+1]) y = y + 1;
	return y;
}






/**
 * Lookup 1 list method and no branch to compute log unsigned int base 10.
 * @ (Memory)
 **/
int ilogf(unsigned x){
	int y;
	static unsigned char table[11] = {0, 9, 99, 999, 9999,
		99999, 999999, 9999999, 99999999, 99999999,
		0xFFFFFFFF};

	y = (19*(31 - nlz(x))) >> 6;
	y = y + ((table[y+1] - x) >> 31);
	return y;
}