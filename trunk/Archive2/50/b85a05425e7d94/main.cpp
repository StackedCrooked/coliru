#include <iostream>
#include <type_traits>
 
int main() {
    typedef std::remove_cv<const int>::type type1;
    typedef std::remove_cv<volatile int>::type type2;
    typedef std::remove_cv<const volatile int>::type type3;
    typedef std::remove_cv<const volatile int*>::type type4;
    typedef std::remove_cv<int * const volatile>::type type5;
 
    std::cout << "test1 " << (std::is_same<int, type1>::value
        ? "passed" : "failed") << '\n';
    std::cout << "test2 " << (std::is_same<int, type2>::value
        ? "passed" : "failed") << '\n';
    std::cout << "test3 " << (std::is_same<int, type3>::value
        ? "passed" : "failed") << '\n';
    std::cout << "test4 " << (std::is_same<const volatile int*, type4>::value
        ? "passed" : "failed") << '\n';
    std::cout << "test5 " << (std::is_same<int*, type5>::value
        ? "passed" : "failed") << '\n';
}