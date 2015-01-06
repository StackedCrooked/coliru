#include <iostream>
#include <string>
#include <utility>

namespace lib
{
    //Make the syntax nicer for library code.
    template<typename T> using traits_for = typename T::lib_traits;

    template<typename T> void f()
    {
        std::cout << traits_for<T>::str() << '\n';
    }
}

namespace client
{
    struct A {
        struct lib_traits {
            static std::string str() {
                return "trait value";
            }
        };
    };
}

int main()
{
    lib::f<client::A>(); //Prints 'trait value'.
}