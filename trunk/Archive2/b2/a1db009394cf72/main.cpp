#include <iostream>
template <typename T>
void f(T t) {
    t.access();
}
namespace N {
    class X {
        class Y {
            friend void f<>(Y);
            void access() {      // private!!!
               std::cout << "access\n";
            }
        };
    public:
        static void call() {
            Y y;
            f(y);
        }
    };
}
int main() {
    N::X::call();
    f(1);
}