#include <type_traits>

static_assert(std::is_convertible<const int, int>(), "const to non-const");
static_assert(std::is_convertible<int, const int>(), "non-const to const");

int main(){}