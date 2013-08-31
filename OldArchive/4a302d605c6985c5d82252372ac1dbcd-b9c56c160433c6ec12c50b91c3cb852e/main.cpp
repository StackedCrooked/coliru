#include <type_traits>

template <typename T, typename std::enable_if<sizeof(int) < sizeof(T), int>::type...>
void f(T) = delete;

void f(int) {}

int main() {
    char c = 0;
    unsigned long long x = 0;
    f(c);
    f(x);
}