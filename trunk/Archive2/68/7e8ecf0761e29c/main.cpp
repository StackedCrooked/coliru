#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>

struct Noisy
{
    typedef std::string::value_type value_type;
    std::string data;
    
    Noisy()
    {
    }
    
    Noisy(const char* data)
        : data(data)
    {
    }
    
    ~Noisy()
    {
    }
    
    Noisy(const Noisy& other)
        : data(other.data)
    {
        std::cout << "Copy constructor.\n";
    }
    
    Noisy& operator=(const Noisy& other)
    {
        data = other.data;
        std::cout << "Copy assignment operator.\n";
        return *this;
    }
    
    Noisy(Noisy&& other)
        : data(std::move(other.data))
    {
        std::cout << "Move constructor.\n";
    }
    
    decltype(data.begin()) begin()
    {
        return data.begin();
    }
    
    decltype(data.end()) end()
    {
        return data.end();
    }
    
    void push_back( std::string::value_type ch )
    {
        data.push_back(ch);
    }
};
 
int main()
{
    Noisy s1("test");
    Noisy s2("four");
    std::copy(std::make_move_iterator(s1.begin()), std::make_move_iterator(s1.end()), std::make_move_iterator(s2.begin()));
    std::cout << s2.data;
    return 0;
}