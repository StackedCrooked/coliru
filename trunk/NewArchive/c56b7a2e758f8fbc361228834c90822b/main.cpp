#include <iostream>
#include <algorithm>
#include <functional>

template<typename R, typename... TArgs>
class Delegate;

template<typename... TArgs>
class Delegate<void, TArgs...>
{
    private:
        using Func = std::function<void(TArgs...)>;
        std::vector<Func> funcs;

    public:
        template<typename T> Delegate& operator+=(T mFunc) { funcs.push_back(Func(mFunc)); return *this; }
        void operator()(TArgs... mParams) { for (auto& f : funcs) f(mParams...); }
};

void test(int x, int y) {  }
    
int main()
{
    Delegate<void, int, int> d2;
    d2 += test; // does not compile
}
