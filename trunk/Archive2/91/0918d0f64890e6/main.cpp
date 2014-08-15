#include <iostream>
#include <vector>
#include <tuple>


enum class MyEnum {
    VALUE
};

struct MyClass {
    template< typename T, typename... Ts >
    MyClass( std::vector<T>& head, std::tuple<Ts& ...> tail, MyEnum myEnum ) {
        // Note that this assumes two parameter types for tail, for simplicity
        std::get<0>(tail) = 42;
        std::get<1>(tail) = 3.14f;
        head.emplace_back(1);
    }
};

 
int main() {
    std::vector<int> dataA;
    int dataB;
    float dataC;
    
    MyClass myClass( dataA, std::tie( dataB, dataC ), MyEnum::VALUE );
    
    std::cout << dataA[0] << std::endl;
    std::cout << dataB << std::endl;
    std::cout << dataC << std::endl;
} 