#include <iostream>
#include <string>
#include <vector>

    #include <iostream>
    #include <type_traits>
     
    using namespace std;
     
    struct DataContainer
    {
    public:
    DataContainer() {}
     
    template<typename T>
    DataContainer(T&& value, typename std::enable_if<std::is_pointer<typename std::remove_reference<T>::type>::value>::type* = 0)
    {
    std::cout << "pointer\n";
    }
     
    template<typename T>
    DataContainer(T&& value, typename std::enable_if<!std::is_pointer<typename std::remove_reference<T>::type>::value>::type* = 0)
    {
    std::cout << "no pointer\n";
    }
    };
     
    struct FooBar
    {};
     
    int main() {
    // your code goes here
    int value = 42;
    DataContainer data(&value);
     
    FooBar* foo = new FooBar;
    DataContainer data2(foo); // output "no pointer" wrong! why?
     
    return 0;
    }