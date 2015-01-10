#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

//return with auto type deduction by (a+b) type
template<typename A, typename B>
auto add(A a, B b) -> decltype(a+b)
{
    return (a+b);
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    //auto type variables
    auto i = 10;  //i is int
//    auto k;       //compile error - no expression to collect type information
    auto d = 10 / 3.0 ; // (10/3) is int, 10/3.0 is double   
    std::cout << i << " " << d << std::endl;
    
    std::vector<int> v{1, 5, 2};
    
    auto iterator = begin(v); //iterator is vector<int>::iterator
    *iterator = 6;
    std::cout << v <<std::endl;
    
    //cbegin still has no "static" function only collection method.
    auto const_iterator = v.cbegin(); //const_iterator is vector<int>::const_iterator
//    *const_iterator = 9;        //compile error - can not change collection with const iterator   
    
//    for(vector<int>::iterator it = begin(v); it != end(v); ++it)
    for(auto it = begin(v); it != end(v); ++it)
    {
        *it = 9 - *it;
    }
    std::cout << v << std::endl;
    
    auto a = add(11, 13);
    auto b = add(11, 13.1);
    std::cout << std::fixed << a << " " << b << std::endl;
}
