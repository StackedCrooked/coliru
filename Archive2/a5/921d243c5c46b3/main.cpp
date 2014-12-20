/**
 * StackOverflow question: 5 years later, is there something better than the “Fastest Possible C++ Delegates”?
 * Answer by In silico: http://stackoverflow.com/questions/4298408/5-years-later-is-there-something-better-than-the-fastest-possible-c-delegate/4300544#4300544
 * 
 * This code shows how you can implement method callbacks without requiring pointer-to-member-function calls.
 */

#include <iostream>


template<typename R, typename A1>
class Callback
{
public:
    typedef R (*FuncType)(void*, A1);

    Callback(void* obj, FuncType f) : obj(obj), f(f) {}
    
    R operator()(A1 a1) const
    {
        return (*f)(obj, a1);
    }

private:
    void* obj;
    FuncType f;
};


template<typename R, class T, typename A1>
struct DeduceMemCallbackTag
{
    template<R (T::*Func)(A1)>
    static R Wrapper(void* obj, A1 a1)
    {
        return (static_cast<T*>(obj)->*Func)(a1);
    }

    template<R (T::*Func)(A1)>
    inline static Callback<R, A1> Bind(T* o)
    {
        return Callback<R, A1>(o, &DeduceMemCallbackTag::Wrapper<Func>);
    }
};

template<typename R, class T, typename A1>
DeduceMemCallbackTag<R, T, A1> DeduceMemCallback(R (T::*)(A1))
{
    return DeduceMemCallbackTag<R, T, A1>();
}

#define BIND_MEM_CB(memFuncPtr, instancePtr) \
    (DeduceMemCallback(memFuncPtr).Bind<(memFuncPtr)>(instancePtr))



struct  Foo
{
    int increment(int n) { return n + 1; }
};


int main()
{
    Foo foo;
    std::cout << BIND_MEM_CB(&Foo::increment, &foo)(12);
}