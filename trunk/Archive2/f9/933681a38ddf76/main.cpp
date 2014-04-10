#include <stdio.h>

typedef void (*GCallback) ();
#define G_CALLBACK(f) ((GCallback) (f))

void foo(GCallback c) {};

int main() {
    foo(G_CALLBACK([](){}));
	foo(G_CALLBACK(+[](void*, int, int, void*){}));
    printf("hello!\n");
	return 0;
}