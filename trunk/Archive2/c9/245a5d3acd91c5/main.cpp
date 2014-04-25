#include <iostream>

namespace detail {
    [[deprecated("FOO() macro is deprecated, use foo() function instead.")]]
    inline void deprecated_foo_macro() {
    }
}

#define FOO(x) do{ std::cout << x << "\n"; detail::deprecated_foo_macro(); }while(false)

int main()
{
    FOO(42);
}
