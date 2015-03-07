#include <iostream>

int    foo1(int device_number, const char*) { std::cout << __PRETTY_FUNCTION__ << "\n"; return device_number*42; }
double foo2(int device_number)              { std::cout << __PRETTY_FUNCTION__ << "\n"; return device_number*3.14159; }

struct facade {
    facade(int dn) : device_number(dn) {}

    template <typename F, typename... A>
        auto call(F&& f, A&&... args) const {
            return std::forward<F>(f)(device_number, std::forward<A>(args)...);
        }

  private:
    int device_number;
};

int main() {

    facade dev(2);

    std::cout << dev.call(foo1, "yes ma'am") << "\n";
    std::cout << dev.call(foo2) << "\n";

}
