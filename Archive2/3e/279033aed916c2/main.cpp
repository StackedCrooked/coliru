#include <functional>
#include <array>

struct Foo {};
struct Bar : public Foo {};

int main()
{
    Foo f;
    Bar b;
    std::array<std::reference_wrapper<Foo>, 2> arr = { f, b };
    
    return 0;
}