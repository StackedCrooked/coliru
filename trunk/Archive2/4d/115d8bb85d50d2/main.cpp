#include <iostream>

struct call_operator {
    //template<typename T>
    operator int() {
        std::cout << __FUNCTION__ << std::endl;
        return {};
    }

    //template<typename T>
    operator const int&() const {
        std::cout << __FUNCTION__ << std::endl;
        static int t;
        return t;
    }

    //template<typename T>
    operator int&() const {
        std::cout << __FUNCTION__ << std::endl;
        static int t;
        return t;
    }
};

int main() {
    (void)static_cast<int>(call_operator());
    (void)static_cast<const int&>(call_operator());
    (void)static_cast<int&>(call_operator());
}