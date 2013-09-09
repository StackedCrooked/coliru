#include <stdio.h>

int main()
{
    char *str1 = "Mesg 1";
    char *str2 = "Mesg 2";
    char str3[] = "Mesg 3";
    char str4[] = "Mesg 4";

    printf("str1 = %p\n", (void *) str1);
    printf("str2 = %p\n", (void *) str2);
    printf("&str3 = %p\n", (void *) str3);
    printf("&str4 = %p\n", (void *) str4);

    return 0;
}