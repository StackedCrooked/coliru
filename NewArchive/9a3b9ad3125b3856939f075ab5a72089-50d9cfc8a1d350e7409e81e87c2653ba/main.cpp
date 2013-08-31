#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

// Only takes std::functions
template<typename R, typename... P>
void do_something(std::function<R(P...)> &func) {
    std::cout << &func << std::endl;
}

struct not_a_pointer_to_member{};
template<typename T>
struct member_function_traits {
    typedef not_a_pointer_to_member function_type;
};

template<>
template<typename C, typename R, typename... P>
struct member_function_traits<R (C::*)(P...) const> {
    typedef std::function<R(P...)> function_type;
};

template<typename Func>
typename member_function_traits<decltype(&Func::operator())>::function_type
make_function(const Func &func) {
    return func;
}

int main () {
    auto func = make_function([](){});
    do_something(func);
}
