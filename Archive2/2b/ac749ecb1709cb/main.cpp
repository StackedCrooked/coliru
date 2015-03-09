
#include <limits>
#include <cstdint>

enum class Foo : int64_t { a = std::numeric_limits<int64_t>::max(), b };

