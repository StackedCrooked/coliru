#include <stdint.h>
 
struct IP
{
    uint8_t data[4];
};
 
struct IPPair
{
    IP source;
    IP destination;
};
 
 
static const IPPair pair = {{ 1, 2, 3, 4 }}, {{ 1, 2, 3, 5 }};
 
int main() { return 0; }