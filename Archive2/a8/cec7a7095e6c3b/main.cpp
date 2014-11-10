#include <stdio.h>

int main(void) {
    int x = 'ABCD';
	printf("%d\n",x);
    printf("%c\n",x);

    printf("Val:`%c`_addr:`%p`\n", ((char*)(&x))[0] , &(((char*)(&x))[0]) );
    printf("Val:`%c`_addr:`%p`\n", ((char*)(&x))[1] , &(((char*)(&x))[1]) );
    printf("Val:`%c`_addr:`%p`\n", ((char*)(&x))[2] , &(((char*)(&x))[2]) );
    printf("Val:`%c`_addr:`%p`\n", ((char*)(&x))[3] , &(((char*)(&x))[3]) );
	return 0;
}
