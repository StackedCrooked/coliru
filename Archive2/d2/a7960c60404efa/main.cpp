#include <cstdint>

#define LEDS

class BaseAddr {
public:
    BaseAddr():
        LEDS      (0x41200000),
        SW1       (0x41210000), // switch 1
        SW2       (0x41220000), // switch 2
        AXI_BRAM  (0x40000000), // 128 registers
        AXI_DUMMY (0x43c00000)  // 16 registers, 4 lsb are connected with leds
    { /* nop */ }

    virtual ~BaseAddr() {}

    const uint32_t LEDS;
    const uint32_t SW1;
    const uint32_t SW2;

private:
    const uint32_t AXI_BRAM;
    const uint32_t AXI_DUMMY;
};