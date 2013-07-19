#include <type_traits>

class C;
static_assert(not std::is_pointer<void(C::*)(int)>::value, "pointers to member functions are not pointers");

int main() {}