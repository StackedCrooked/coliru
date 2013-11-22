#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <utility>
#include <type_traits>
#include <boost/fusion/container/vector.hpp>

int main() {
    boost::fusion::vector<int> x(1);
	return 0;
}

template<typename... Ts>
class Variadic {
};

template<typename T, typename, typename = typename T::value_type, typename = int, int = 5>
class C {
};

template class C<std::string, int>;
C<std::string, void> c;

void foo(std::future<int> future1) {
    //std::cout << "foo" << std::endl;
}

struct A {
    void foo() {
        std::cout << std::boolalpha << std::is_same<A*, decltype(this)>::value << std::endl;
    }
    
    void bar() const {
        std::cout << std::boolalpha << std::is_same<A*, decltype(this)>::value << std::endl;
    }
};

typedef struct Q {
    int foo;
} Q;

/*
int main() {
    int a = 0;
    ++0<:&(!~0U???(:>(...)<%??>,1:0x0)??(&a:>??);
    std::cout << a << std::endl;
    
    A().foo();
    A().bar();
    
    #if 0
    std::promise<int> promise;
    std::future<int> future1 = promise.get_future();
    auto future2 = std::async(std::launch::async, [] {
            std::cout << "start" << std::endl;
            std::chrono::milliseconds duration { 2000 };
            std::this_thread::sleep_for(duration);
            std::cout << "end" << std::endl;
            return 0;
        });
    foo(std::move(future2));
    std::cout << "end of program" << std::endl;
    #endif
    
    return 0;
}
*/