#include <type_traits>
#include <utility>

int test(double x, double y);
double test(int x, int y);
char test(char x, int y);

template<typename... Ts>
using TestType = decltype(test(std::declval<Ts>()...))(Ts...);

int main() {
    static_assert(std::is_same<TestType<double, double>, int(double, double)>::value, "");
}