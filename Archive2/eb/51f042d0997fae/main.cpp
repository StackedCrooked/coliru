#include <stdint.h>
#include <cassert>

struct alignas(32) foo { int i; };

int main() {
    auto p0 = new foo{0};
    auto p1 = new foo{1};
    auto p2 = new foo{2};
    auto p3 = new foo{3};
    
    assert((uintptr_t)p0 % 32 == 0);
    assert((uintptr_t)p1 % 32 == 0);
    assert((uintptr_t)p2 % 32 == 0);
    assert((uintptr_t)p3 % 32 == 0);
}