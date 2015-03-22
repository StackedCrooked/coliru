#include <stdio.h>
#include <string.h>


int foo(int *a,int * b){
    return (*a+*b);
}

int main(void){
    const char a[11]= "asdsda";
    strcat(a,'c');
    printf("%s", a);
	return 0;
}