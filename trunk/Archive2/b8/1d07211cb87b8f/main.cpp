
#include <stdio.h>  // for test output, not actually needed when you do the I/O
#include <stdarg.h>

void sendToAddressV(volatile char *address, int count, va_list ap)
{
    int i, value;
    for (i = 0; i < count; ++i)
    {
        // do your write here...
        
        value = va_arg(ap, int);
        printf("Pretending to write %d to %p\n", value, address);
    }
}

void sendToAddress(volatile char *address, int count, ...)
{
    va_list ap;
    va_start(ap, count);
    sendToAddressV(address, count, ap);
    va_end(ap);
}

int main()
{
    sendToAddress((volatile char*)0x1234, 4, 16, 17, 18, 19);
    sendToAddress((volatile char*)0x1234, 2, 30, 31);
}
