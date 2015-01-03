#include <cstring>
#include <cstdio>

int main(){

    //passing strings directly
    printf("%d\n", strcmp("ahmad", "fatema"));

    //passing strings as pointers 
    char *a= "ahmad";
    char *b= "fatema";
    printf("%d\n",strcmp(a,b));

    return 0;
}