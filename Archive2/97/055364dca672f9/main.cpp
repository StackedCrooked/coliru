#include <vector>
#include <iostream>
#include <functional>


namespace my_space {
template<typename... R> using bind = std::bind<R...>;   // error
}


void foo() {
    std::cout << "bar\n";
}


int main() {
    std::function<void()> fn;
    fn = std::bind(foo);
    fn();
    
    // i want to do
    fn = my_space::bind(foo);
    fn();
}
