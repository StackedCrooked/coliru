#include <stdio.h>
#include <math.h>

// Extended euclidian alogrithm for finding gcd and modulo multiplicative inverses
// ! Could be simpler but works for now !
void egcd(int a, int b,int buf[4]) {
    int s,t,u,v,q,r,ao,bo,uo,vo,so,to,qo;
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
           to = t;
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
    if(e == 0) return (int) 1;

    //for negative exponents c = b^e = d^|e| mod m 
    if(e < 0) {
        b= modInv(b,m);
        e*=-1;
        if(b==0) return 0;
    }

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
        erg += modExp(16,n-k,8*k+b)/(8*k+b);
    }
    for(k=n+1;k<=samples;k++) {
        erg += pow(16,n-k)/(8*k+b);
    }
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
    a1 -= (long) a1;
    a2 -= (long) a2;
    a3 -= (long) a3;
    a4 -= (long) a4;

    // Sum all four sums together
    erg = 4*a1 -2*a2 - a3 -a4;

    // Strip integer part
    erg = (erg -(long) erg);
    return erg;
}

int PiN(double BBP) {
    //return (int) ((BBP - (long) BBP)));
    return (int)(BBP*16);
}


int main(void) {
    int erg=0;

    printf("BIP %2.2f\n",PiN(BBP(1,1000)));
    printf("\n");
}