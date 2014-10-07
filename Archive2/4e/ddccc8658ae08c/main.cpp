#include <functional>
#include <array>

struct Foo {};
struct Bar : public Foo {};

int main()
{
    std::array<std::reference_wrapper<Foo>, 2> arr = { Foo(), Bar() };
    
    return 0;
}