#include <cstdlib>
#include <type_traits>

void foo(void *) {}

int main() {
    static_assert(!std::is_null_pointer<decltype(NULL)>::value, "");   
    foo(NULL);
}