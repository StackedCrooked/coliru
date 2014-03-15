#include <functional>
#include <type_traits>
#include <iostream>

#define set(expression) set_([&]{ return (expression); })
#define LazyContainer2(expression) LazyContainer<std::decay<decltype((expression))>::type>{[&]{ return (expression); }}

template<typename T>
struct LazyContainer {
    std::function<T()> value;
    
    LazyContainer() {
    };
    
    LazyContainer(std::function<T()> value) : value{value} {
    }
    
    void set_(std::function<T()> value) {
        this->value = value;
    }
    
    T get() {
        return value();
    }
};

int main() {
    int n = 0;
    LazyContainer<int> container;
    
    std::cout << "n: " << n << std::endl; // 0
    container.set(++n);
    std::cout << "(++n) n: " << n << std::endl; // 0
    std::cout << "get(): " << container.get() << std::endl; // 1
    std::cout << "get(): " << container.get() << std::endl; // 2
    std::cout << "n: " << n << std::endl; // 2
    
    auto container2 = LazyContainer2(------n);
    std::cout << "(------n) n: " << n << std::endl; // 2
    std::cout << "get(): " << container2.get() << std::endl; // -1
    
    return 0;
}