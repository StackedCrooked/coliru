#include<stdio.h>

int main() {
    int c,y;
    float r,si;
    
    scanf("%d%d%f",&c,&y,&r);
    
    si=c*y*r/100;
    printf("%f\n",si);
}