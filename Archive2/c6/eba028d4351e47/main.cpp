#include <iostream>
#include <string>
#include <regex>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>

template<class T>
using maybe = boost::optional<T>;
static const boost::none_t nothing = boost::none;
using namespace boost;



template<class T, class FuncT> inline
maybe<T> operator>>=(const maybe<T>& maybe, FuncT func)
{
    return maybe? func(maybe.get()) : nothing;
}

maybe<int> half(int x)
{
    if(x % 2 == 0) return (x / 2);
    return nothing;
}

int main()
{
    std::cout << ((half(8) >>= half) >>= half) << std::endl;
}
