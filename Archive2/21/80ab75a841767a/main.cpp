#include <stdio.h>
char * mystrcpy_1(char * dest, char * src) {
    char * origDest = dest;
    while (*src != '\0') {
        *dest = *src;
        src++;
        dest++;
    }
    *dest = '\0';
    return origDest;
}
char * mystrcpy_2(char * dest, char * src) {
    char * origDest = dest;
    while (*src != '\0') {
        *origDest = *src;
        src++;
        origDest++;
    }
    *origDest = '\0';
    return origDest;
}
int main(int argc,char*argv[]){
    char src_1[]="abcdefg",dst_1[sizeof(src_1)];
    mystrcpy_1(dst_1,src_1);
    printf("%s\n",dst_1);
    
    char src_2[]="abcdefg",dst_2[sizeof(src_2)];
    mystrcpy_2(dst_2,src_2);
    printf("%s\n",dst_2);
    return 0;
}