#include <stdexcept>

template<bool B>
struct error { 
    static_assert(B, "..");
};

constexpr int f(int x) {
    return x > 0 ? (error<false>{}, 0) : x * 10;
}

int main(int argc, char **argv) {
    f(-5);
    return 0;
}