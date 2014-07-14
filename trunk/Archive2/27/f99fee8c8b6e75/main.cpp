#include <type_traits>

struct B
{
    const int value;
    // B() = default;
};

int main()
{
    B();
}