#include <iostream>

struct foo_t {
    foo_t() {std::cout << "default construct\n";}
    foo_t(const foo_t&) {std::cout << "copy construct\n";}
    foo_t(foo_t&&) {std::cout << "move construct\n";}
    explicit foo_t(int converter) {std::cout << "convert construct\n";}
    foo_t& operator=(const foo_t&) {std::cout << "copy assign\n"; return *this;}
    foo_t& operator=(foo_t&&) {std::cout << "move assign\n"; return *this;}
};

void function(foo_t* ptr) {std::cout << "function\n";}

template<class... Ts>
void foo_function_helper(Ts...Vs) {
    //assume all Ts are foo_t    
    using swallow = int[];
    swallow{(function(&Vs),0)...,0};
}

template<class T> T& maybe_convert(T& p) {return p;}
template<class T> T&& maybe_convert(T&& p) {return std::move(p);}
template<class T, class U> T maybe_convert(U&& p, typename std::enable_if<!std::is_same<U,T>::value,char*>::type=0)
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


