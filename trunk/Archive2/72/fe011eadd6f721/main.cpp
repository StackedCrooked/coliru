#include <typeinfo>

int main() {
    alignas(sizeof(decltype(typeid(const volatile unsigned long long int)))) static thread_local decltype(typeid(const volatile unsigned long long int).name()) foo{};
}