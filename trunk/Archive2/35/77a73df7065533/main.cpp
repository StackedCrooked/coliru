#include <cassert>
#include <array>
#include <iostream>

inline constexpr int BAND_FIELD1(int B) {
    return 10 * B + 1;
}

int main(int, char*[]) {

    constexpr int myField = 0;
    constexpr int B = myField % 10;
    int variable1 = 0;
    switch (myField) {
        case BAND_FIELD1(B):
            variable1 = 123;
            break;
        default: break;
    }
    std::cout << variable1;
}