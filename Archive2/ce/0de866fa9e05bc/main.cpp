//Author Manu Sánchez (Manu343726). Aug 2014

//Everything started from this: http://stackoverflow.com/questions/25338795/is-there-a-name-for-this-tuple-creation-idiom
//Now, play with C++14!

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
    auto t = tuple(5u,6,7l,8.0)(rcat)(tuple(1u,2,3l,4.0));
    
    print_tuple(t);
}