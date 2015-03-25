// http://blog.coldflake.com/posts/C++-delegates-on-steroids/
#include <cstdio>

template<typename return_type, typename... params>
class Delegate
{
    typedef return_type (*Type)(void* callee, params...);
public:
    Delegate(void* callee, Type function)
        : fpCallee(callee)
        , fpCallbackFunction(function) {}
    template <class T, return_type (T::*TMethod)(params...)>
    static Delegate from_function(T* callee)
    {
        Delegate d(callee, &methodCaller<T, TMethod>);
        return d;
    }
    return_type operator()(params... xs) const
    {
        return (*fpCallbackFunction)(fpCallee, xs...);
    }
private:
    void* fpCallee;
    Type fpCallbackFunction;
    template <class T, return_type (T::*TMethod)(params...)>
    static return_type methodCaller(void* callee, params... xs)
    {
        T* p = static_cast<T*>(callee);
        return (p->*TMethod)(xs...);
    }
};

template<typename T, typename return_type, typename... params>
struct DelegateMaker
{
    template<return_type (T::*foo)(params...)>
    static return_type methodCaller(void* o, params... xs)
    {
        return (static_cast<T*>(o)->*foo)(xs...);
    }
    template<return_type (T::*foo)(params...)>
    inline static Delegate<return_type, params...> Bind(T* o)
    {
        return Delegate<return_type,
               params...>(o, &DelegateMaker::methodCaller<foo>);
    }
};
template<typename T, typename return_type, typename... params>
DelegateMaker<T, return_type, params... >
makeDelegate(return_type (T::*)(params...))
{
    return DelegateMaker<T, return_type, params...>();
}
#define DELEGATE(foo, thisPrt) (makeDelegate(foo).Bind<foo>(thisPrt))

class A
{
public:
    void deadSimple()
    {
        printf("no params whatsoever\n");
    }
    int foo(int x)
    {
        return x*x;
    }
    int bar(int x, int y, char a)
    {
        return a == 'a' ? x+y : x*y;
    }
    void crazy(int I, char wanna, float go, const char* crazy)
    {
        printf("I=%d, wanna=%c, go=%f, crazy=%s\n",
               I, wanna, go, crazy);
    }
};

int main()
{
    A a;
    auto d = DELEGATE(&A::foo, &a);
    auto d2 = DELEGATE(&A::bar, &a);
    auto d3 = DELEGATE(&A::crazy, &a);
    auto d4 = DELEGATE(&A::deadSimple, &a);
    printf("d(42)=%d\n", d(42));
    printf("d2(42, 2, 'a')=%d\n", d2(42, 2, 'a'));
    const char* s = "sheeeet!";
    d3(5, 'a', 4.5, s);
    d4();
    return 0;
}
