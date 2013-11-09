#include <iostream>


struct O
{
    ~O()
    {
        std::cout << "~O()\n";
    }
};

struct wrapper
{
    O const& val;
    
    ~wrapper()
    {
        std::cout << "~wrapper()\n";
    }
};

struct wrapperEx // with explicit ctor
{
    O const& val;
    
    explicit wrapperEx(O const& val)
      : val(val)
    {}
    
    ~wrapperEx()
    {
        std::cout << "~wrapperEx()\n";
    }
};

template<class T>
T&& f(T&& t)
{
    return std::forward<T>(t);
}


int main()
{
    std::cout << "case 1-----------\n";
    {
        auto&& a = wrapper{O()};
        std::cout << "end-scope\n";
    }
    std::cout << "case 2-----------\n";
    {
        auto a = wrapper{O()};
        std::cout << "end-scope\n";
    }
    std::cout << "case 3-----------\n";
    {
        auto&& a = wrapper{f(O())};
        std::cout << "end-scope\n";
    }
    std::cout << "case Ex-----------\n";
    {
        auto&& a = wrapperEx{O()};
        std::cout << "end-scope\n";
    }
    return 0;
}