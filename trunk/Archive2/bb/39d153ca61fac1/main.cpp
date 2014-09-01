#include <iostream>
#include <cstdlib>
#include <boost/variant.hpp>

template<typename T>
void println(T const& t)
{
    std::cout << t << '\n';    
}

template<typename T, typename U>
auto if2(bool cond, T const& t, U const& u)
{
    typedef boost::variant<T const&, U const&> vari;
    return cond ? vari(t) : vari(u);
}

int main()
{
    println( if2(rand() % 2 == 0, "true", 200) );
}