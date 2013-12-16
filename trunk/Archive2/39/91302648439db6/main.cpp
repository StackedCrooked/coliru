//PUNTEROS

#include <stdio.h>

/*void mul(int a, int b, int s)
{
    s=a*b;
}

void mult(int a, int b, int* s)
{
    *s=a*b;
}*/


/*
void p()
{
    int s;
    printf("%d\n",s);
}

void q()
{
    int n = 248;
    printf("%d\n",n);
}
*/

int* m()
{
    int a=29;
    return &a;
}



int main()
{
    /*int a=8;
    int* s;
    s= &a;
    printf("%p\n",s);
    printf("%d\n",*s);
    *s = 25;
    printf("%d\n",*s);*/
    
    /*int* p = (int*) 0xF9;
    printf("%p\n",p);
    printf("%d\n",*p);*/
    
    /*int a=9;
    int b=5;
    int r;
    mult(a,b,&r);
    printf("%d\n",r);*/
    
    /*p();
    q();*/
    int* f=m();
    printf("%d\n",*f);
}