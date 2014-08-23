#include <cstdlib>
#include <type_traits>

int main() {
    static_assert(!std::is_null_pointer<decltype(NULL)>::value, "");   
}