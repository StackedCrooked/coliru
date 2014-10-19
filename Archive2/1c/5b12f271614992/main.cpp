#include <tuple>

template<typename... Args>
void f(const Args&... args) {
    std::tuple<Args...> tup(args...);
}

int main() {
    f("hello", 10);
}