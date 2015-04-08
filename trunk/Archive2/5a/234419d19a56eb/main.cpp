#include <iostream>

template<typename T>
struct why_the_fuck {};

namespace ns {
    template<class T>
    void bar(T* testVar) {
        std::cout << "testFunction1" << std::endl;
    }
    
    template<class T>
    void foo() {
        bar((why_the_fuck<int>*)0);
        bar((T*)0);
    }
}

template<typename... Ts>
void bar(why_the_fuck<Ts...>* testVar) {
    std::cout << "testFunction2" << std::endl;
}

int main() {
    ns::foo<why_the_fuck<int>>();
    return 0;
}