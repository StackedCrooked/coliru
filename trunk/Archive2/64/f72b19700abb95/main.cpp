#include <stdlib.h>
#include <stdio.h>

struct Foo {
    int *ptr;
};

static void modify_copy(struct Foo f)
{
    *f.ptr = 42;
}

int main()
{
    int n = 1337;
    
    printf("%d\n", n);
    
    struct Foo f = { &n };
    modify_copy(f);
    
    printf("%d\n", n);
        
	return 0;
}