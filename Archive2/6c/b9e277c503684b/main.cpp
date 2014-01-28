#include <initializer_list>

int main() {
    constexpr auto i={1, 2, 3, 4, 5};
    static_assert(i.size()==5, "Size != 5");
}
