#include <type_traits>

#define ASSERT_NOTHROW_WHATEVER(className) static_assert(std::is_nothrow_move_constructible<className>::value, "bad");

struct A{};

ASSERT_NOTHROW_WHATEVER(A)

template <typename First, typename Second>
struct B{};

ASSERT_NOTHROW_WHATEVER(B<int, int>)

int main()
{
}
