#include <iostream>

template<typename T>
struct just_cast_it
{
    just_cast_it(T&& t) : _t{std::forward<T>(t)} { }
    
    template<typename U>
    operator U ()
    {
        return static_cast<U>(std::forward<T>(_t));
    }
    
    T&& _t;
};

template<typename T>
just_cast_it<T&&> just_cast_bitch(T&& t)
{
    return {std::forward<T>(t)};
}

int main() 
{
    int x = 65;
    char y = just_cast_bitch(x);
    std::cout << y;
}
