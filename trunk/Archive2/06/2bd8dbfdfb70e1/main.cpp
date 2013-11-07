#include <stdio.h>


void f1(char *d, char const* c)
{
    while (*d++=*c++);
}

void f2(char *d, char const* c)
{
	while(*c){
		*d = *c;
		d++;
		c++;
	}
}

int main(void)
{
	char text1[20] = "Hello, World!";
	
	char text2[20];
	char text3[20];
	
	f1(text2,text1);
	f2(text3,text1);
	
#define DBG(x) printf(#x":\t%s\n",x);
	
	DBG(text1);
	DBG(text2);
	DBG(text3);
	
#undef DBG

	return 0;
}
