#include <iostream>

namespace foo {
    namespace bar { 
        struct A {};
        void foo(A) {
            std::cout << "foo::bar\n";
        }
    }
}
namespace bar {
    template <typename T> void foo(T) {
        std::cout << "bar\n";
    }
    template <typename T> void run(T x) {
        bar::foo(x);
    }
}

int main() {
  bar::run(foo::bar::A());
}