     #include <stdio.h>
     #include <stdlib.h>

    int fibr (int n ) {    // using recursive method
        if (n==0) return 0 ;
        else if (n==1) return 1;
        else return (fibr(n-1)+2*fibr(n-2));
    }
    
    int fibnr (int n ) {
        int a=0;
        int b=1;
        if (n==0) return a;
        else if (n==1) return b;
        else {
            int sum=0 ;
            int i ;
            for (i=2;i<=n;i++) {
                sum=a+(2*b);
                a=b;
                b=sum;
            }
            return sum;
        }
    }
    int main() {
        for(int i=0; i<15; ++i) {
            int rresult = fibr(i);
            int nrresult = fibnr(i);
            printf("%d produced %d and %d\n", i, rresult, nrresult);
        }
    }