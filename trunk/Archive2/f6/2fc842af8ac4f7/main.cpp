#include <iostream>

#define DETAIL_DEPRECATED_MSG(name, fn) deprecated(#name "() macro is deprecated, use " #fn "() function instead.")
#define DETAIL_DEPRECATED_FN(name, fn) deprecated_##fn##_macro()
#if defined(_MSC_VER)
#   define DETAIL_DEPRECATED_MACRO(name, fn) \
    inline void __declspec(DETAIL_DEPRECATED_MSG(name, fn)) DETAIL_DEPRECATED_FN(name, fn) {}
#else
#   define DETAIL_DEPRECATED_MACRO(name, fn) \
    inline void __attribute__((DETAIL_DEPRECATED_MSG(name, fn))) DETAIL_DEPRECATED_FN(name, fn) {}
#endif

namespace detail {
    DETAIL_DEPRECATED_MACRO(FOO, foo)
}

#define FOO(x) do{ std::cout << x << "\n"; detail::deprecated_foo_macro(); }while(false)

int main()
{
    FOO(42);
}
