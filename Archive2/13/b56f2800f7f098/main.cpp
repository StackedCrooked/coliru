#include <stdint.h>
#include <cassert>

struct alignas(32) foo { int i; };

int main() {
    auto p0 = new foo{0};
    auto p1 = new foo{1};
    auto p2 = new foo{2};
    auto p3 = new foo{3};
    
    assert((int)p0 % 32 == 0);
    assert((int)p1 % 32 == 0);
    assert((int)p2 % 32 == 0);
    assert((int)p3 % 32 == 0);
}