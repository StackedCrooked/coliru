#include <iostream>
#include <string>
#include <functional>
#include <type_traits>

typedef std::function<std::string(void)> acceptedFunc;
template<typename Func>
void asdf(Func doThing) {
    decltype(doThing()) val = doThing();
    std::cout << typeid(val).name() << " -- " << typeid(acceptedFunc).name() << " " << std::is_same<acceptedFunc, decltype(val)>::value << std::endl;
    if(std::is_same<acceptedFunc, decltype(val)>::value) {
        std::cout << "yay" << std::endl;
    }
}


int main()
{
    asdf([&]() {
        return (std::string)"qwer";
    });
    
    
    
    
    std::cout << "done" << std::endl;
    
    return 0;
}


