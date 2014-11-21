#include <type_traits>

int main() {
    static_assert(std::is_const<std::remove_reference_t<const int &>>{});   
}