#include <initializer_list>
#include <type_traits>


template<typename T>
void func(T arg) {
}


int main() {
    auto init_list = {1, 2};
    static_assert(std::is_same<decltype(init_list), std::initializer_list<int>>(), "not same");
    func({1, 2});
}
