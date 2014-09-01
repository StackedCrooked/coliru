enum init : int {
    timer          = 0x00000001,
    audio          = 0x00000010,
    video          = 0x00000020,
    joystick       = 0x00000200,
    haptic         = 0x00001000,
    gamecontroller = 0x00002000,
    events         = 0x00004000,
    noparachute    = 0x00100000,
    image          = 0x01000000,
    mixer          = 0x02000000,
    ttf            = 0x03000000,
    everything     = timer | audio | video | events |
                     joystick | haptic | gamecontroller |
                     mixer    | ttf    | image
};

#include <iostream>

void test_flag(int x, int y) {
    std::cout <<  ((x & y) == y) << '\n';
}

int main() {
    int test = timer | mixer;
    std::cout.flags(std::cout.flags() | std::cout.boolalpha);
    test_flag(test, timer);
    test_flag(test, mixer);
    test_flag(test, everything);
    test_flag(test, noparachute);
    test_flag(test, events | video);
    test_flag(test, ttf);
}