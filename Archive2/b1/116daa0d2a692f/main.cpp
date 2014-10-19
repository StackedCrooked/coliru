#include <iostream>





void f(int *aa,int *bb){
        *bb=8;
        aa[1] = bb[2];
        
}
int main(){
 int a[5] = {1,2,3,4,5},*b;
 b = a+2;
 f(a,b);
 printf("%d %d %d %d %d \n", a[0],a[1],a[2],a[3],a[4]);
}