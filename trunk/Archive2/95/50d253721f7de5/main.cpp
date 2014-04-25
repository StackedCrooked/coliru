#include <stdint.h>
#include <limits.h>

int main()
{
    const unsigned length = (uint8_t) ( (8.0/CHAR_BIT) * 18 );
    uint8_t var [ length ];
}
