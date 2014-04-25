#include <stdint.h>
#include <limits.h>

int main()
{
    uint8_t var [ (uint8_t) ( (8.0/CHAR_BIT) * 18 ) ];
}
