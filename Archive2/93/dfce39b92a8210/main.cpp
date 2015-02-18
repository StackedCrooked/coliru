#include <stdio.h>
int foo() {
    static int i=0;
    if(i<4) i++;
    return i;
}

int main(){
    int j =0;
    for(j=0;j<20;j++)
       printf("i din foo %d\n", foo());
}