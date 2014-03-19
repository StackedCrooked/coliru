#include <type_traits>

static_assert(not std::is_same<decltype(100), decltype(100000000000)>::value, "oh, well");

int main() {}