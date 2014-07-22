#include <type_traits>
struct none {};

template<typename T>
struct test {
    bool b = std::is_same<T, none>::value;
};

int main() {
    test<int> x;
    return x.b;
}