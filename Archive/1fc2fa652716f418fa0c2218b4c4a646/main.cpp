#include <type_traits>

static_assert(not std::is_same<decltype(600851475143), int>::value,
              "stop saying nonsense");

int main() {}