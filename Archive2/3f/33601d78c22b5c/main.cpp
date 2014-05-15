#include <iostream>

class A {};

namespace lib {
    template<class T>
    void operation(const T& arg) {
        std::cout << "fallback operation\n";
    }

    template<class T>
    void operation_caller(const T& arg) {
        ::lib::operation(arg);
    }
}

namespace lib {
    void operation(const A& arg) {
        std::cout << "user defined operation for type A";
    }
}


int main(int argc, char** argv) {
    lib::operation_caller(A());
    return 0;
}
