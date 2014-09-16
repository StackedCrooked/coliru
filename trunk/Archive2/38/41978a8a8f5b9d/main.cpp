#include <type_traits>

struct B {};

static_assert(std::is_base_of< B, B >::value, "!");