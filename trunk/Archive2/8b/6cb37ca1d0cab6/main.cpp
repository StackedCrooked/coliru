#include <functional>
#include <iostream>

template<class T>
class foo;

template<class R, class ...Args>
class foo<R(Args...)>
{
public:
    foo(std::function<R(Args...)> f)
        :_f(f)
    {        
    }

    R invoke(Args... args)
    {
        return _f(args...);
    }

private:
    std::function<R(Args...)> _f;
};

int main()
{
    foo<void()> f([&](){ std::cout << "hi\n"; });
    f.invoke();
}