#include <type_traits>
#include <utility>

static_assert(std::is_pod<std::pair<unsigned, unsigned>>::value, "");

int main() { }
