#include <iostream>


struct A {};
struct B {};


template<typename ...T>
void match(T&&...)
{
    std::cout << "Match: T&&..." << std::endl;
}


void match(A, A, A)
{
    std::cout << "Match: AAA" << std::endl;

}


enum { Limit = 4 };


// stop condition
template<typename ...Args>
auto dispatch(std::string, Args&& ...args) -> typename std::enable_if<(sizeof...(args) >= Limit)>::type
{
    match(std::forward<Args>(args)...);
}


// runtime to compile-time bridge
template<typename ...Args>
auto dispatch(std::string s, Args&& ...args) -> typename std::enable_if<(sizeof...(Args) < Limit)>::type
{
    if (s.empty())
    {
        match(std::forward<Args>(args)...);
        return;
    }

    char c = s[0];
    s.erase(s.begin());

    switch (c)
    {
        case 'A': dispatch(std::move(s), A{}, std::forward<Args>(args)...); break;
        case 'B': dispatch(std::move(s), B{}, std::forward<Args>(args)...); break;
        default:
        {
            std::cout << "Ignoring " << c << std::endl;
            dispatch(std::move(s), std::forward<Args>(args)...); break;
        }
    }
}


int main()
{
    dispatch("ABC");
    dispatch("AAA");
}
