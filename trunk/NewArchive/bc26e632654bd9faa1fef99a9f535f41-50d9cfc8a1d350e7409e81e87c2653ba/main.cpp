#include <iostream>
#include <functional>

// Only takes std::functions
template<typename R, typename... P>
void do_something(std::function<R(P...)> &func) {
    std::cout << &func << std::endl;
}

struct not_pointer_to_member_function{};

template<typename T>
struct pointer_to_member_function_traits {
    typedef not_pointer_to_member_function type;
};

template<>
template<typename C, typename R, typename... P>
struct pointer_to_member_function_traits<R (C::*)(P...) const> {
    typedef std::function<R(P...)> type;
};

struct not_callable{};

template<typename C>
struct callable_traits {
    typedef typename pointer_to_member_function_traits<decltype(&C::operator())>::type type;
};

template<>
template<typename R, typename... P>
struct callable_traits<R(P...)> {
    typedef std::function<R(P...)> type;
};

template<typename Func>
typename callable_traits<Func>::type
make_function(const Func &func) {
    return func;
}

void abc(){}

struct fo_abc {
    void operator()() const {}
};

struct look_i_said_it_is_impossible_and_you_need_to_change_your_requirements {
    int operator()(int x) const { return x; }
    double operator()(double x) const { return x; }
};
struct here_is_another_good_luck_finding_the_types {
    template <typename T>
    T operator()(T x) const { return x; }
};

int main () {
    auto func = make_function([](){}); // lambda
    auto func2 = make_function(abc); // free function
    auto func3 = make_function(fo_abc()); // function object
    do_something(func);
    do_something(func2);
    do_something(func3);

    auto func4 = make_function(look_i_said_it_is_impossible_and_you_need_to_change_your_requirements()); // function object
    auto func5 = make_function(here_is_another_good_luck_finding_the_types()); // function object
}
