#include <type_traits>

using int_ref = int&;

static_assert(std::is_same<int const&,int_ref const&&>(), "Jabberwocky is killing user.");