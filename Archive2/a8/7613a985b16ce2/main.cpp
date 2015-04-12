#include <stdio.h>
#include <string.h>


int main(void)
{
    const char a[] = "abc";
    const char b[] = "abc11111";
    const char c[] = "abc11111";
	const char * arr[3] = {a,b,c};
    printf("%s\n", arr[2]);
    printf("%c\n", arr[1][2]);
	return (0);
}
