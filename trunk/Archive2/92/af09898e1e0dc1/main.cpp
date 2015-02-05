#include <iostream>

struct Checker {
    static const bool L0 = true;
    static const bool L1 = true;
};

#define JOIN(a, b) a ## b

#define CHECK_MACRO_EXISTS(M) \
template <typename T2 = Checker> \
static constexpr bool exists(bool x = T2::JOIN(L, M)) { \
    return true; \
}

/*
static constexpr bool exists(...) {
    return false;
}
*/

#define FOO 1

CHECK_MACRO_EXISTS(FOO)

#define WTF(M) Checker::JOIN(L, M)


int main() {
    
 bool does_exist = exists();
 std::cout << does_exist << std::endl;
 
 std::cout << WTF(FOO) << std::endl;
    
 return 0;
}