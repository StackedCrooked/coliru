#include <iostream>
#include <cstdint>

// whatever
#define ANS1_OID_BER  sizeof(uint32_t)

struct Local_registry_d
{
    uint8_t length_width; /**< Length */
    uint8_t tag_width;    /**< Tag */
};


static const struct Local_registry_d Local_reg_map[0x7B + 1] = {
    [0x3 ] = { .length_width = ANS1_OID_BER, .tag_width = 1            },
    [0x0B] = { .length_width = ANS1_OID_BER, .tag_width = ANS1_OID_BER },
    [0x13] = { .length_width = ANS1_OID_BER, .tag_width = 2            },
    [0x1B] = { .length_width = ANS1_OID_BER, .tag_width = 4            },
    [0x23] = { .length_width = 1           , .tag_width = 1            },
    [0x2B] = { .length_width = 1           , .tag_width = ANS1_OID_BER },
    [0x33] = { .length_width = 1           , .tag_width = 2            },
    [0x3B] = { .length_width = 1           , .tag_width = 4            },
    [0x43] = { .length_width = 2           , .tag_width = 1            },
    [0x4B] = { .length_width = 2           , .tag_width = ANS1_OID_BER },
    [0x53] = { .length_width = 2           , .tag_width = 2            },
    [0x5B] = { .length_width = 2           , .tag_width = 4            },
    [0x63] = { .length_width = 4           , .tag_width = 1            },
    [0x6B] = { .length_width = 4           , .tag_width = ANS1_OID_BER },
    [0x73] = { .length_width = 4           , .tag_width = 2            },
    [0x7B] = { .length_width = 4           , .tag_width = 4            },
};




int main(void)
{}