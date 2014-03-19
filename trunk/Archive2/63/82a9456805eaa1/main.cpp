#include <boost/phoenix.hpp>
#include <iostream>

class MyStringClass
{
public:
    operator const char*() const
    {
        static int i = 0;
        std::cout << "I was here " << ++i << "\n";
        return nullptr;
    }
};

namespace detail
{
    template <typename T>
    struct my_cast 
    {
        template <typename U> struct result { typedef T type; };
        template <typename U>
        T operator()(const U& v) const { return static_cast<T>(v); }
    };
}

namespace phx = boost::phoenix;

int main()
{
    phx::function<detail::my_cast<const char*>> to_csz;

    std::vector<MyStringClass> v(10);

    std::for_each(v.begin(), v.end(), to_csz);
}
