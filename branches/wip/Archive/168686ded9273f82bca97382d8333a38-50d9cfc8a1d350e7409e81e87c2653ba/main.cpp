#include <type_traits>

static_assert(std::is_same<std::make_signed<const unsigned int>, signed int>(), "");

int main(){}