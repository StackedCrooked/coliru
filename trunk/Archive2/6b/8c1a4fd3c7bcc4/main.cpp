#include <iostream>
#include <type_traits>

template <typename From, typename To>
using WithConstOf = typename std::conditional<std::is_const<From>::value, typename std::add_const<To>::type, To>::type;
template <typename T>
using RemoveReference = typename std::remove_reference<T>::type;

struct foo {
    template <typename Foo>
    static WithConstOf<RemoveReference<Foo>, int>& get_(Foo&& self) {
        return self.x;
    }
    
    int& get() { return get_(*this); }
    int const& get() const { return get_(*this); }

    int x;
};

int main() {}
