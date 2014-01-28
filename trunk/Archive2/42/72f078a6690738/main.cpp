#include <stdio.h>  // for test output, not actually needed when you do the I/O
#include <stdarg.h>

void sendToAddressV(int bit, va_list ap)
{
    int value;
    volatile (int*) address1;
    volatile (int*) address2;
    for (; ; )
    {
        // do your write here...
        
        value = va_arg(ap, int);
        if (value == -1)
            break;
        
        // Can't really write it in this test, but this is what you would do:
        // I want to decrment address by 0x4 for each argement.
        //(*address2 - j) = value;
        
        printf("Pretending to write %d to %p on bit %d\n", value, *address,bit);
    }
    //*address1 = 1 << bit;
}

void sendToAddress(int bit, ...)
{
    va_list ap;
    va_start(ap,bit);
    sendToAddressV(bit, ap);
    va_end(ap);
}

#define SEND_TO(bit, ...) sendToAddress(bit, __VA_ARGS__, -1)

//#define SEND_TO_1234(...) SEND_TO(0x1234, __VA_ARGS__)

int main()
{
    SEND_TO(1, 16, 17, 18, 19);
    SEND_TO(2, 30, 31);
}
