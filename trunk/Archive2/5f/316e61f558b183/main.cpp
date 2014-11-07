#include <utility>

int main(int argc, char** argv) {
    int x[2][3];
    int y[2][3];

    using std::swap;
    static_assert(noexcept(swap(x, y, 0)), "");

    return 0;
}