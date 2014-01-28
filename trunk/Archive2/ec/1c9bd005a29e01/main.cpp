
#include <stdio.h>  // for test output, not actually needed when you do the I/O
#include <stdarg.h>

void sendToAddressV(void *address, int count, va_list ap)
{
    int i, value;
    for (i = 0; i < count; ++i)
    {
        // do your write here...
        
        value = va_arg(ap, int);
        printf("Pretending to write %d to %p\n", value, address);
    }
}

void sendToAddress(void *address, int count, ...)
{
    va_list ap;
    va_start(ap, count);
    sendToAddressV(address, count, ap);
    va_end(ap);
}

int main()
{
    sendToAddress((void*)0x1234, 4, 16, 17, 18, 19);
}
