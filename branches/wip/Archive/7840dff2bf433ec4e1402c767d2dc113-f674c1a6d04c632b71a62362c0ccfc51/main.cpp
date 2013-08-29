#include <iostream>
#include <memory>
#include <functional>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Test {
};
void apply(Test&& t) {
}


int main() {
    auto myt = make_unique<Test>();
    auto f = std::bind(&apply, std::move(myt));
    f();
    return 0;
}