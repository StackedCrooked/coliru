#include <stdio.h>
#include <map>

int *var;

int main(){
    int a = 8;
    var = &a;
    printf("%p",var);
}
