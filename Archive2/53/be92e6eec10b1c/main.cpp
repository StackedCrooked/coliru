#include <boost/variant.hpp>

#include <typeinfo>

template <typename T>
auto foo(const boost::variant<int, double>& variant, double bar) -> decltype(typeid(T) == typeid(int) ? boost::get<T>(variant) : bar)
{
    return typeid(T) == typeid(int) ? boost::get<T>(variant) : bar;
}

int main()
{
    const boost::variant<int, double> variant;
    foo<int>(variant, 0.5);
}
