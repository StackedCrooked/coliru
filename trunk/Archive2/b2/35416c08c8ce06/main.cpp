#include <type_traits>

class Class {};

static_assert(std::is_member_function_pointer<int Class::*>(), "");

int main()
{}