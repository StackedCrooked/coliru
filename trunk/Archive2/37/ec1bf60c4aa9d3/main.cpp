#include <cassert>
#include <iostream>

template <class T>
struct Print;

int main() {
    using std::cout;
    using std::endl;

    // Print<decltype(~static_cast<unsigned char>(0x55u))> dummy;

    cout << "--> 0x55: " << 0x55u << ", 0xAA: " << 0xAAu << ", ~0x55: "
         << static_cast<unsigned>(~static_cast<unsigned char>(0x55u)) << endl;

    assert(static_cast<unsigned char>(0xAAu) ==
           ~static_cast<unsigned char>(0x55u));
}