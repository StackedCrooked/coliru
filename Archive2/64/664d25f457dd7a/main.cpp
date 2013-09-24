#include <iostream>
#include <type_traits>
 
struct Ex1 {
    std::string str; // member has a non-trivial but non-throwing move ctor
};
struct Ex2 {
    int n;
    Ex2(Ex2&&) = default; // trivial and non-throwing
};
 
int main() {
    std::cout << std::boolalpha << "Ex1 is move-constructible? "
              << std::is_move_constructible<Ex1>::value << '\n'
              << "Ex1 is trivially move-constructible? "
              << std::is_trivially_move_constructible<Ex1>::value << '\n'
              << "Ex1 is nothrow move-constructible? "
              << std::is_nothrow_move_constructible<Ex1>::value << '\n'
              << "Ex2 is trivially move-constructible? "
              << std::is_trivially_move_constructible<Ex2>::value << '\n'
              << "Ex2 is nothrow move-constructible? "
              << std::is_nothrow_move_constructible<Ex2>::value << '\n';
}