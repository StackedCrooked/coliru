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

auto print_tuple = [](auto t){ return t(map)( [](auto e){ std::cout << e << " "; return e; } ); };

auto double_tuple = tuple(1,2,3)(map)([](auto i){ return i*2; });


int main()
{
    print_tuple(tuple(1,2,3,4));
}