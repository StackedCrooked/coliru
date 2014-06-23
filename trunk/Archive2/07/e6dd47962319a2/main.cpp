#include <vector>
#include <iostream>
#include <functional>


namespace my_space {
//template<typename... R> using bind = std::bind<R...>;   // error
template<class... Args>
auto bind(Args&&... args) -> decltype( std::bind(std::forward<Args>(args)...) )
{
    return std::bind(std::forward<Args>(args)...);
}
//Or C++14:
//template<class... T>
//auto bind(T&&... t)
//{
//    return std::bind(std::forward<T>(t)...);
//}
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
