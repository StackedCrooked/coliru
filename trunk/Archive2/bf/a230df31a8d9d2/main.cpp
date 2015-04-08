//test.cpp
#include <iostream>


struct ReadWrite {
    static constexpr bool value = true;
};

struct ReadOnly {
    static constexpr bool value = false;
};

template<typename T, typename A>
struct Property
{
    void F()
    {
        static_assert(A::value,"Cannot modify ReadOnly");
        std::cout << "ping" << std::endl;
    }
};

int main()
{
    Property<int,ReadWrite> x;
    x.F();

    Property<int,ReadOnly> y;
    // y.F(); // won't compile if uncommented

    return 0;
}
