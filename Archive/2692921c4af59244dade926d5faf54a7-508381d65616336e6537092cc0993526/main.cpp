#include <type_traits>

int main(){
    auto l = [](int i){ return i * 42; };
    static_assert(std::is_empty<decltype(l)>(), "non-empty empty lambda");
}