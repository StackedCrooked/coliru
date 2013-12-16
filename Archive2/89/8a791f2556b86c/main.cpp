#include <type_traits>
struct wat {};
int main() {
    using x = int (wat::*)(int);
    using y = x (wat, int);
    using is_it_int = std::result_of<y>::type;
    is_it_int foo = 5;
}
