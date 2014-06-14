#include <string>
#include <iostream>
#include <functional>

template<typename Ret, typename... Args>
void f(std::function<Ret(Args...)> function) {
    std::cout << typeid(Ret).name() << std::endl;
}
template<typename Ret, typename... Args>
void f(Ret(*function)(Args...)) {
    f(std::function<Ret(Args...)>(function));
}

int f2() {
    return 1;
}

int main() {
    f(f2);
    return 0;
}