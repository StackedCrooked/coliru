#include <iostream>
#include <string>


template <typename Ta>
struct MyStruct {
    
    Ta actual;
    
    MyStruct(Ta actual) : actual(actual) {}; 
    
    template <typename Te>
    bool equal(Te expected) {
        return actual == expected;
    };
};


int main()
{
    std::cout << "asdf" << MyStruct(3).equal(5) << std::endl;
}