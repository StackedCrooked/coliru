#include <iostream>
#include <stdexcept>
#include <typeinfo>


template<class Fun, class ExceptionHandler, class ... Exceptions>
struct excpected_exception;

template<class Fun, class ExceptionHandler, class Ex1, class ... Exceptions>
struct excpected_exception<Fun, ExceptionHandler, Ex1, Exceptions...>
{
    void operator()(Fun f, ExceptionHandler eh) {
        try {
            excpected_exception<Fun, ExceptionHandler, Exceptions...>{}(f, eh);
        } catch (Ex1 const& ex) {
            eh(ex);
        }
    }
};

template<class Fun, class ExceptionHandler>
struct excpected_exception<Fun, ExceptionHandler>
{
    void operator()(Fun f, ExceptionHandler) {
        f();
    }
};

template<class... Ex, class F, class Eh>
void expect_exception(F f, Eh eh) {
    excpected_exception<F, Eh, Ex...>{}(f, eh);
}

struct MyEh {
    template<class Ex>
    void operator()(Ex&& ex) const {
        std::cerr << ex.what() << "(" << typeid(ex).name() << ")" << std::endl; 
    }
};


int main() {
    
    expect_exception<std::runtime_error, std::logic_error>([&]{throw std::runtime_error("Hello");}, MyEh{});
    expect_exception<std::runtime_error, std::logic_error>([&]{throw std::logic_error("World");;}, MyEh{});
    
    return 0;
}


    
