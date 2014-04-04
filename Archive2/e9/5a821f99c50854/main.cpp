#include <iostream>
#include <string>
#include <functional>

struct FF
{
    template <typename T>
    void operator() (T a)
    {
        std::cout << a << std::endl;
    }
};

int main()
{    
    std::function<void(int)> f_int;
    std::function<void(const std::string&)> f_str;
    //f = [](int b){ std::cout << b << std::endl; };
    
    f_int = FF();
    f_str = FF();
    f_int(100);
    f_str("aaaa");
    
}