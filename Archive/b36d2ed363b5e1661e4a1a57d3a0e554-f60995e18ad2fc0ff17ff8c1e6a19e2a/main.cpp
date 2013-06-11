#include <type_traits> // is_same
#include <cstddef> // size_t

static_assert(not std::is_same<std::size_t, unsigned int>(), "nope, size_t is not unsigned int here");

int main () {}
