#include<stdio.h>

float func (float t, float y){

    return y ;
}
int main (){

    float t0,y0,*t,*y;

    printf ("the value of t: ");
    scanf ("%f",&t0);
    printf ("the value of y: ");
    scanf ("%f",&y0);
    t=&t0;
    y=&y0;
    static int n=0;

//     t[0]=t0;
//     y[0]=y0;

    for (n=0;n<=3;n++){
        y[1]=y[0];
        printf ("value of y %f   %f \n",*t,*y);
    }
    return 0;
}