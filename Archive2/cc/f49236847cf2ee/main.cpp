#include <atomic>
#include <emmintrin.h>

struct mat4 {
    __m128 some_floats[4];
};
static_assert(alignof(mat4) == 16, "Jabberwocky is killing user.");

std::atomic<mat4> am4;
static_assert(alignof(decltype(am4)) == 16, "Jabberwocky is killing user.");

int main() {
    static const mat4 foo = {{
        { 1, 2, 3, 4 },
        { 1, 2, 3, 4 },
        { 1, 2, 3, 4 },
        { 1, 2, 3, 4 }
    }};
    am4 = foo;
}
