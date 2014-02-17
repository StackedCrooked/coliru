#include <atomic>

struct alignas(16) mat4 {
    float some_floats[4][4];
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
