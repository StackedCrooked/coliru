#include <iostream>
#include <functional>
using namespace std;

template< class R, class... Args >
class MyFunction;

template< class R, class... Args >
class MyFunction<R(Args...)> : public std::function<R(Args...)> {
public:
    using std::function<R(Args...)>::function;
};

int main() {
    std::function<void()> f_display_42 = []() { std::cout << 42; }; //works

    MyFunction<void()> mine = []() { std::cout << 42; }; //errors
}
