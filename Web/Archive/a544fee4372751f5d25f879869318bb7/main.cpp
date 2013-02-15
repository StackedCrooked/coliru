#include <stdint.h>
 
typedef struct IP_t
{
    uint8_t data[4];
} IP;
 
typedef struct IPPair_t
{
    IP source;
    IP destination;
} IPPair;
 
 
static const IPPair pair = {{{{ 1, 2, 3, 4 }}}, {{{ 1, 2, 3, 5 }}}};
 
int main() { return 0; }