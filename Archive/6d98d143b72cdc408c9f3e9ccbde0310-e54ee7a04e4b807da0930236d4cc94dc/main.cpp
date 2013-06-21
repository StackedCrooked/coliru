#include <mutex>
#include <cassert>
#include <iostream>

template <typename T>
struct static_ctorable {
public:
    static_ctorable() {
        std::call_once(flag, &T::static_ctor);
    }

private:
    static std::once_flag flag;
};
template <typename T>
std::once_flag static_ctorable<T>::flag;

bool ran = false;

struct foo : static_ctorable<foo> {
    static void static_ctor() {
        ran = true;
    }
    
    static int x;
};

int foo::x = []() -> int { assert(ran); return 42; }();

int main() {
    std::cout << foo::x;
}
