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

namespace phx = boost::phoenix;
using namespace phx::arg_names;

int main()
{
    auto implicit_conversion = phx::static_cast_<const char*>(arg1);

    std::vector<MyStringClass> v(10);
    std::for_each(v.begin(), v.end(), implicit_conversion);
}
