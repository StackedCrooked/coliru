#include <stdio.h>  // for test output, not actually needed when you do the I/O
#include <stdarg.h>

#define LOGGER  ((volatile int *)0x1234)
#define LOGGER_DATA ((volatile int *)0x5678)

void sendToAddressV(int bit, va_list ap)
{
    int i, value;
    
    for (i = 0; ; ++i)
    {
        // do your write here...
        
        value = va_arg(ap, int);
        if (value == -1)
            break;
            
        // Can't really write it in this test, but this is what you would do:
        //LOGGER_DATA[-i] = value;

        printf("Pretending to write %d to %p\n", value, (void*)&LOGGER_DATA[-i]);
    }
    //*LOGGER |= 1 << bit;
    printf("Pretending to OR %d to %p\n", 1<<bit, (void*)LOGGER);
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
