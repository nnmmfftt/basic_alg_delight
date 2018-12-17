#include <stdlib.h>
#include <math.h>

/**
 *@abs: int type
 *
 **/
#define abs(x) ( (x)>0?(x):-(x) )

float fabs_asm(float fnumber){
  float ret;
  __asm__ (
     "fabs/n/r"
     : "=t" (ret)
     : "0" (fnumber)
  );
  return ret;
}

float fabs_signfloat(float fnumber){
	/**
	 *
	 * Clear the sign of float number.
	 *
	 **/
   *( (int *) &fnumber) &=0x7FFFFFFF;
  return fnumber;
}

double fabs_signdouble(double dnumber){
  *( ( (int *) & dnumber) + 1) &=0x7FFFFFFF;
  return dnumber;
}

int compute_negtive(int a){
	return aplusb(~a,1);
}

int asubb(int a, int b){
	return aplusb(a,compute_negtive(b));
}

int aplusb(int a, int b){ 
	/**
	 *
	 * 1) compute a+b and ignore the carry. @ a^b
	 * 2) compute the carry. 				@ (a&b)<<1 
	 * 3) add the carry and a^b(1).			@ a|b
	 * 4) if the sum has carry, repeat the 1) and 2) before the 3).
	 *
	 **/
    if((a&b) == 0)
        return a|b;
    return aplusb(a^b,(a&b)<<1);
}

int getsign(int i){
    return (i>>31);
}


int multiply(int a, int b){ //循环法实现加法
    bool flag = true;
    if(getsign(a) == getsign(b)) 
        flag = false;

    a = abs(a);
    b = abs(b);
    int ans = 0;
    while(b){
        ans = aplusb(ans, a);
        b = asubb(b, 1);
    }

    if(flag)
        ans = compute_negtive(ans);
    return ans;
}

int division(int a, int b){
    if(b==0) return 0;
	bool flag = true;
    if(getsign(a) == getsign(b)) //积的符号判定
        flag = false;

    a = abs(a);
    b = abs(b);
    int n = 0;
    a = asubb(a, b);
    while(a>=0){
        n = aplusb(n, 1);
        a = asubb(a, b);
    }

    if(flag)
        n = compute_negtive(n);
    return n;
}

