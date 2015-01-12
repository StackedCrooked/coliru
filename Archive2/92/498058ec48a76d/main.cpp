#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator> //cbegin

using namespace std;

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
    
    //GOOD things in auto:
    //#1 - you won't forget initialization of a variable.
    //auto k;     //compile error - no expression to collect type information
    
    //#2 - save you time/characters with more readable code:
    std::vector<int> vect{1, 5, 2};  
    auto it = begin(vect);         //it is       vector<int>::iterator
    auto const_it = vect.cbegin(); //const_it is vector<int>::const_iterator
    
    //#3 always pick the right type
    auto vsize = vect.size();       //vsize is std::vector::size_type.
    unsigned vsize2 = vect.size(); //looks same. in Win32 both are 32bit, on Win64 unsigned 32bit <=> vector::size_type 64bit
    
    
    //Some usage:   
    auto i = 10;           //i is int
    auto d = i / 3.0 ;     //(10/3) is int, 10/3.0 is double   
    std::cout << i << " " << d << std::endl;
    
    //changing vector with auto iterator
    std::vector<int> v{1, 5, 2};
    auto iterator = begin(v);      //iterator is vector<int>::iterator
    *iterator = 6;                 //we can change the vector
    std::cout << v <<std::endl;
    
    //cbegin still has no "static" function only collection method.
    auto const_iterator = v.cbegin(); //const_iterator is vector<int>::const_iterator
//    *const_iterator = 9;        //compile error - can not change collection with const iterator   
    
    //for(vector<int>::iterator it = begin(v); it != end(v); ++it)
    
    //saving time/space for loops
    for(auto it = begin(v); it != end(v); ++it)
    {
        *it = 9 - *it;
    }
    std::cout << v << std::endl;
    
    //using output for template functions
    auto a = add(11, 13);       //returns int
    auto b = add(11, 13.1);     //returns double
    std::cout << std::fixed << a << " " << b << std::endl;
}
