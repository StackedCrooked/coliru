#include <functional>
#include <iostream>
template<typename Handler>void func1(int a, Handler&& handler) { handler(a); }
template<typename Handler>void func2(Handler&& handler)
{
    // this line compile fine
    std::function<void ()> funcA = [handler = std::move(handler)]() { func1(1, std::move(handler)); };
    funcA();
}

int f(int a) { std::cout << "Hi! " << a << std::endl; return 0; }

int main()
{
    func2(&f); // this just a sample, I am using functor as argument in real code
}