#include <functional>

class myClass
{
    std::function<void()> m;
public:
    template<class F, class... Args>
    myClass(F&& f, Args&&... args)
        : m(std::bind(std::forward<F>(f), std::forward<Args>(args)...))
    {}
    
    void evaluate()
    {  m();  }
};

#include <iostream>
int foo(int p) { std::cout << "purr\n"; return p; }

int main()
{
    myClass x(foo, 42);
    x.evaluate();
}