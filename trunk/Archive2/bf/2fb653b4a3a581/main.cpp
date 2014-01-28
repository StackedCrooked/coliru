
#include <stdio.h>  // for test output, not actually needed when you do the I/O
#include <stdarg.h>

void sendToAddressV(volatile char *address, va_list ap)
{
    int value;
    for (; ; )
    {
        // do your write here...
        
        value = va_arg(ap, int);
        if (value == -1)
            break;
        
        // Can't really write it in this test, but this is what you would do:
        //*address = value;
        
        printf("Pretending to write %d to %p\n", value, address);
    }
}

void sendToAddress(volatile char *address, ...)
{
    va_list ap;
    va_start(ap, address);
    sendToAddressV(address, ap);
    va_end(ap);
}

int main()
{
    sendToAddress((volatile char*)0x1234, 16, 17, 18, 19, -1);
    sendToAddress((volatile char*)0x1234, 30, 31, -1);
}
