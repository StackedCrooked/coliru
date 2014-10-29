#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std::placeholders;

class Class {
public:
    void method1(int param1) {
        std::cout << __PRETTY_FUNCTION__ << ' ' << param1 << std::endl;
    }
};

auto functor(int param) -> decltype(std::bind(&Class::method1, _1, param)) {
    return std::bind(&Class::method1, _1, param);
}

// C++14
//auto functor(int param)  {
//    return std::bind(&Class::method1, _1, param);
//}

int main()
{
    std::vector<Class> container(5);
    int param = 42;
    std::for_each( container.begin(), container.end(), functor(param));
    
    return 0;
}