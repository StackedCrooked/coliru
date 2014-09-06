#include <stdio.h>
#include <math.h>
// Extended euclidian alogrithm for finding gcd and modulo multiplicative inverses
void egcd(int a, int b,int buf[4]) {
int s,t,u,v,q,r,uo,vo,so;
// ao = a; bo = b;
q = 0; s = v = r = 0    ; u = t = 1;
do {
q = a / b;
r = a % b;
a = b;
b = r;
uo = u;
u = s;
vo = v;
v = t;
so = s;
s = uo - q*so;
t = vo-q*t;
//printf("q:%d,b:%d, u:%d, s:%d v:%d t:%d while!\n",q,b,u,s,v,t);
} while(b!=0);

// a = gcd; u = modular multiplicativ inverse; v+s : internal use only
buf[0] = a; buf[1] = u; buf[2] = v;buf[3] = s;
}

// Modular Multiplicativ Invers
int modInv(int a, int n)
{
	int erg[4] = {0,0,0,0};
	egcd(a,n,erg);
	if(erg[0] == 1 && erg[1] >= 0) return erg[1];
	else if(erg[0] == 1&& erg[1] < 0) return erg[3] + erg[1];
	return -1;
}
// Modular Exponentation
int modExp(int b,int signed e,int m) {
int c=1,e1 = 0;
if(e == 0 && m>1) { return (int) 1; }
if(e == 0 && m==1) { return 0; }

//for negative exponents c = b^e = d^|e| mod m 
if(e < 0) {b= modInv(b,m); e*=-1; if(b==0) return 0; }
do {
	e1++;
	c = b*c % m;
//printf("c: %d,b: %d\n",c,b); 
} while(e1 != e);
return c;
}

// calculate one sum of the BBP formular.
// int n: position in pi
// int b: see Wikipedia BBP-Formula
// int samples: samples for calculation of infty sum
double calcSingleSum(int n,int b,int samples) {
    int k;
	double erg = 0;
	for(k=0;k<=n;k++) {
		printf("k:%d; n: %d\n",k,n);
		erg += modExp(16,n-k,8*k+b)/(8*k+b);
	}
	printf("First Sum: %4.10f\n",erg);
	for(k=n+1;k<=samples;k++) {
		erg += pow(16,n-k)/(8*k+b);
	}
	printf("Second Sum: %4.10f\n",erg);
	return erg;
}

// BBP Formular calulation
double BBP(int n,int samples) {
double a1=0,a2=0,a3=0,a4=0,erg=0;
// calculate sums
a1 = calcSingleSum(n,1,samples);
a2 = calcSingleSum(n,4,samples);
a3 = calcSingleSum(n,5,samples);
a4 = calcSingleSum(n,6,samples);

// Strip Integer parts (e.g. mod 1)
/*
a1 -= (long) a1;
a2 -= (long) a2;
a3 -= (long) a3;
a4 -= (long) a4;
*/
// Some all four sums together
erg = 4*a1 -2*a2 - a3 -a4;
// Strip integer part
//erg = (erg -(long) erg);
return erg;
}
double PiN(double BBP) {
//return (int) ((BBP - (long) BBP));
return (BBP*16);
}
int main(void) {

// Result: 		0.0082593203
// Calc-Result:	0.00825932025646
printf("%4.10f\n",BBP(0,100));

printf("\n");
return 0;
}