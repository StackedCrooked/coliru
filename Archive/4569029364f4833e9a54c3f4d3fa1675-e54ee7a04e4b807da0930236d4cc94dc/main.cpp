#include <mutex>
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

struct foo : static_ctorable<foo> {
    static void static_ctor() {
        std::cout << "static ctored\n";
    }
};

int main() {
    foo a;
    foo b;
    foo c;
}
