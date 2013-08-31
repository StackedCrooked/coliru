#include <vector>

namespace ns {
    template <typename T>
    void f(T) { }

    struct x { };
}

int main() {
    std::vector<ns::x> v;
    f(v);
}