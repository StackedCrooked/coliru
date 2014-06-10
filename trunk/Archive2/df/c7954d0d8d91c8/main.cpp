#include <functional>

template<typename Handler>void func1(int a, Handler&& handler) {}
template<typename Handler>void func2(Handler&& handler)
{
    // this line got compile error
    std::function<void (int, Handler)> funcB = std::bind(func1<Handler>, 1, std::forward<Handler>(handler));
}

int main()
{
    func2([]{});
}