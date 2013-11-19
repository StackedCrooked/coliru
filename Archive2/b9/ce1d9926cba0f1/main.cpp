#include <cstdint>                                          

struct X {
    explicit operator uint32_t() { return 0; }
};

int main() {
    static_cast< int >( X() );
    return 0;
}