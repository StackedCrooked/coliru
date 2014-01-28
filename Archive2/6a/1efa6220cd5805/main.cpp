#include <iostream>
#include <functional>
#include <utility>
 
struct Foo {
    template <typename Function, typename... Args>
    Foo(Function&& func, Args&&... args) :
      func_(std::bind(std::forward<Function>(func), std::forward<Args>(args)...)) {}
    void operator()() const { func_(); }
    std::function<void()> func_;
};
 
void printValues(int x, double y, const char* charArr) {
    std::cout << x << " " << y << " " << charArr << std::endl;
}
 
int main() {
    Foo{printValues, 5, 2, "Test"}();
}
