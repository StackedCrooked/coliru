#include <stdio.h>
#include <stdarg.h>
 
void foo()
{
    printf("foo\n");
}

typedef void(*foo_ptr)();

void bar(unsigned count, ...) 
{
    va_list args;
    va_start(args, count);
    unsigned i = 0;
    
    for (; i < count; ++i) {
        foo_ptr p = va_arg(args, foo_ptr);
        (*p)();
    }
    va_end(args);
}
 
int main() 
{
    bar(2, &foo, &foo);
}
