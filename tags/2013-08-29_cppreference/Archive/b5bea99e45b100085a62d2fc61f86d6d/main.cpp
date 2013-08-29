#include <array>
#include <stdint.h>

struct IP
{
    std::array<uint8_t, 4> data;
};

struct IPPair
{
    IP source;
    IP destination;
};


static constexpr IPPair pair = {{{{ 1, 2, 3, 4 }}}, {{{ 1, 2, 3, 5 }}}};