#include <stdint.h>
#include <limits.h>

int main() 
{
    enum {array_length = (uint8_t)((8.0 / CHAR_BIT) * 18)};
    uint8_t array[array_length] = {0};
    (void)(array);
    return 0;
}
