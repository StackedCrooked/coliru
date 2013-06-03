#include <iostream>

struct foo_t {
    foo_t() {}
    explicit foo_t(int converter) {}
};

void function(foo_t* ptr) {}

template<class... Ts>
void foo_function_helper(Ts...Vs) {
    //assume all Ts are foo_t
    char data[] = {(function(&Vs),0)...,0};
}

template<class T> T& maybe_convert(T& p) {return p;}
template<class T> T&& maybe_convert(T&& p) {return std::move(p);}
template<class T, class U> T maybe_convert(U&& p, std::enable_if<std::is_convertible<U,T>::value,char*>::type=0)
{return T(std::forward<U>(p));}

template<class ...Ts>
void foo_function(Ts...Vs) {
    //MAKE all Ts into foo_t
    foo_function_helper(maybe_convert<foo_t>(std::forward<Ts>(Vs))...);
}

int main() {
    foo_t reference;
    foo_function(reference, foo_t(), 3);
}


