#include <utility>
#include <iostream>

auto tuple = [](auto... args)
{
    return [=](auto f){ return f(args...); };  
};

auto map = [](auto... args)
{
    return [=](auto f){ return tuple(f(args)...); };  
};

auto cat_raw = []( auto... largs )
{
    return [=](auto... rargs){ return tuple(largs...,rargs...); }; 
};

auto rcat = []( auto... largs )
{
    return [=]( auto rhs ){ return rhs(cat_raw)(largs...); };
};



auto print_tuple = [](auto t){ return t(map)( [](auto e){ std::cout << e << " "; return e; } ); };


int main()
{
    auto t = tuple(1,2,3,4)(rcat)(tuple(5,6,7,8));
    
    print_tuple(t);
}