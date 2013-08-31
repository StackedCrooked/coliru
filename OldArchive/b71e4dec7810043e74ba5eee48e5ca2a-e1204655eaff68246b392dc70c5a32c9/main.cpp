#include <type_traits>

template <typename T>
class ClassName
{
    // instance variables, etc..

public:
    template <typename U=T, typename V=typename std::enable_if<std::is_floating_point<U>::value>::type>
    void some_method()
    {
        // do stuff, but only for floating point types
    }
};

int main() {
    ClassName<int> i;
    ClassName<double> d;
    d.some_method(); // compiles
    i.some_method(); // error!
}
