#include <type_traits>

namespace detail { struct secret {}; }

template <typename NoExplicit = detail::secret, typename T>
void f(T) { static_assert(std::is_same<NoExplicit, detail::secret>(), "fuck off"); /* ... */ }

int main()
{
    f(1);
    f<int>(2);
}
