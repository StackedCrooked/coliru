#include <type_traits>

struct S {
    S() {
        void (std::remove_reference<decltype(*this)>::type::*callback)(int, int);
    }
};

int main(){}