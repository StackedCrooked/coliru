#include <iostream>
#include <functional>

template<class T>
class SPFunction;

template<class... Args>
class SPFunction<void(Args...)>
{
public:
    
    SPFunction()
    {
    }
    
    template <typename F>
    SPFunction(F f)
    : _f(static_cast<std::function<void(Args...)>>(f))
    {
    }
    
    void operator()(Args... args)
    {
        if (_f)
        {
            _f(args...);
        }
    }
    
    operator bool() const
    {
        return _f != nullptr;
    }
    
private:
    std::function<void(Args...)> _f;
};

int main()
{
    std::function<void()> std_func = [](){ printf("this is std::function!\n"); };
    
    SPFunction<void()> f0([](){ printf("this is lambda func!\n"); });
    SPFunction<void()> f1 = std_func;
    SPFunction<void()> f2(std_func);
    SPFunction<void()> f3;
    
    f2 = std_func;
    f1 = f2;
    
    f0();
    f1();
    f2();
    f3();
    
    auto checkIfNull = [](SPFunction<void()> f, const char* fname) { printf("%s is null: %s\n", fname, f ? "NO" : "YES"); };
    checkIfNull(f0, "f0");
    checkIfNull(f1, "f1");
    checkIfNull(f2, "f2");
    checkIfNull(f3, "f3");
    
    
    /// Not supported cases: ========================================================
    /*
    std::function<int()> ifunc = []()->int{ return 0; };
    SPFunction<int()> ispfunc = ifunc;
    //*/
    // ===========================================================================
    
    return 0;
}