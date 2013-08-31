#include <type_traits>
static_assert(std::is_same<int[1], int * const>::value, "Not a const pointer.");
static_assert(std::is_same<int[1], const int *>::value, "Not a pointer to const.");
static_assert(std::is_same<int[1], const int * const>::value, "Not a const pointer to const.");