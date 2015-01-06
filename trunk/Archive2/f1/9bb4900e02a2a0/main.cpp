#include <iostream>
#include <string>
#include <utility>

namespace lib
{
    //Make the syntax nicer for library code.
    template<typename T> using traits_for = decltype(traits_helper(std::declval<T>()));

    template<typename T> void f()
    {
        std::cout << traits_for<T>::str() << '\n';
    }
}

namespace client
{
    struct A { };
    //The following two lines are needed only once in every client namespace.
    struct traits { static std::string str(); };
    traits traits_helper(A&&); //No definition needed.
    std::string traits::str() { return "trait value"; }
}

int main()
{
    lib::f<client::A>(); //Prints 'trait value'.
}