#include <stdint.h>
#include <stdio.h>

union color {
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    
    uint32_t rgba;
};

int main(int argc, char* argv[])
{
    color c = { 255, 0, 0, 255 };
    printf("Color: %08X\n", c.rgba);

    return 0;
}
