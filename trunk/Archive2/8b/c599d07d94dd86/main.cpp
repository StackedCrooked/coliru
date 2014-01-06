#include <iostream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>
#include <array>

typedef struct {
    uint16_t index;
    uint8_t subindex;
    uint8_t bit_length;
} ec_pdo_entry_info_t;

class the_class {
private:
    static constexpr std::array<ec_pdo_entry_info_t, 17> slave_0_pdo_entries {{
            { 0x6040, 0x00, 16 },    //    0
            { 0x607a, 0x00, 32 },    //    2
            { 0x60b0, 0x00, 32 },    //    6
            { 0x60b1, 0x00, 32 },    //    10
            { 0x60b2, 0x00, 16 },    //    14
            { 0x6060, 0x00, 8 },    //    16
            { 0x2078, 0x01, 16 },    //    17
            { 0x60b8, 0x00, 16 },    //    19
            { 0x6041, 0x00, 16 },    //    21
            { 0x6064, 0x00, 32 },    //    23
            { 0x606c, 0x00, 32 },    //    27
            { 0x6077, 0x00, 16 },
            { 0x6061, 0x00, 8 },
            { 0x2071, 0x01, 16 },
            { 0x60b9, 0x00, 16 },
            { 0x60ba, 0x00, 32 },
            { 0x60bb, 0x00, 32 }
    }};
    //...
};

int main() {
    return 0;
}