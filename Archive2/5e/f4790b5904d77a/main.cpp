#include <iostream>
#include <functional>

template<class T>
class SPFunction;

template<class R, class ...Args>
class SPFunction<R(Args...)>
{
public:
    
    SPFunction()
    {
    }
    
    template <typename F>
    SPFunction(F f)
    : _f(static_cast<std::function<R(Args...)>>(f))
    {
    }
    
    R operator()(Args... args)
    {
        if (_f)
        {
            return _f(args...);
        }
        else
        {
            return R();
        }
    }
    
    operator bool()const
    {
        return _f != nullptr;
    }
    
private:
    std::function<R(Args...)> _f;
};

int main()
{
    auto checkIfNull = [](SPFunction<void()> f, const char* fname) { printf("%s is null: %s\n", fname, f ? "NO" : "YES"); };
    
    std::function<void()> std_func = [](){ printf("this is std::function!\n"); };
    
    SPFunction<void()> f0([](){ printf("this is lambda func!\n"); });
    SPFunction<void(void)> f01 = [](){};
    
    SPFunction<void()> f1 = std_func;
    SPFunction<void()> f2(std_func);
    SPFunction<void()> f3;
    
    f2 = std_func;
    f1 = f2;
    
    f0();
    f1();
    f2();
    
    checkIfNull(f0, "f0");
    checkIfNull(f1, "f1");
    checkIfNull(f2, "f2");
    checkIfNull(f3, "f3");
    
    SPFunction<int(int)> i_func = [](int i)->int{ printf("fx %d\n", i); return 0; };
    i_func(1);
    
    SPFunction<int(int,int)> sum_func = [](int a, int b){ return a+b; };
    int a = 5;
    int b = 6;
    printf("a + b = %d\n", sum_func(a, b));

    SPFunction<int(int,int)> nullfunc = nullptr;
    printf("nullfunc: %d\n", nullfunc(1,2));
    
    
    /// Not compiling case: ========================================================
    /*
    class Foo
    {
    public:
        Foo(int v) : _v(v) {}
    private:
        int _v;
        Foo(){}
    };
    
    SPFunction<Foo(int)> foo = [](int i)->Foo{ return Foo(i); };
    foo(10); // Error: "calling a private constructor of class Foo"
    //*/
    // ===========================================================================
    
    return 0;
}