struct Base{
    int x,y,z;
};

struct Derived : Base{
    Derived() = default;
    constexpr Derived(int a, int b, int c) : Base{a, b, c}{}
};

#include <type_traits>

static_assert(std::is_trivial<Base>::value, "Base must be trivial");
static_assert(std::is_trivial<Derived>::value, "Derived must be trivial");

int main(){
  Base b{1, 2, 3};
  Derived d{10, 20, 30};
}