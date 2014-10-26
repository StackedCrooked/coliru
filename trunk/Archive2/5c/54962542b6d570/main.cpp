template<typename T> struct tuple_holder { T value; };

template<typename... Args>
struct unique_tuple : tuple_holder<Args>...
{    
    unique_tuple(Args... args) : tuple_holder<Args>{args}... { } 
    
    template<typename T>
    T& get() { return tuple_holder<T>::value; }

    template<typename T>
    T const& get() const { return tuple_holder<T>::value; }
};

#include <iostream>
#include <iomanip>
#include <string>

int main()
{
    unique_tuple<int, std::string, double> t{1, "Hello", 3.14};

    std::cout << t.get<int>() << std::endl;
    std::cout << t.get<std::string>() << std::endl;
    std::cout << t.get<double>() << std::endl;
}