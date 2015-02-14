#include <stdio.h>
#include <limits.h>
int main(int argc,char*argv[]){
    char x=0;
    while(x>=0)++x;
    --x;
    printf("%d\n",x);
    printf("%d\n",CHAR_MAX);
    return 0;
}