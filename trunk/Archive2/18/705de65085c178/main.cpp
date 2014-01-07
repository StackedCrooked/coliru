#include <type_traits>

static_assert(std::is_assignable<int, int>(), "...");

int main(){}