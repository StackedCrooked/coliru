template<class C, class F>
struct FunctionSequence;

template<class C, class R, class... Args>
struct FunctionSequence<C, R(Args...)>
{
    typedef R(C::*PointerToMember)(Args...);

    template<class T>
    struct Test
    {
        static const PointerToMember f[1];
    };
    
    template<PointerToMember... F>
    struct Type
    {
        static const PointerToMember f[sizeof...(F)];
    };
};

template<class C, class R, class... Args>
template<class T>
const typename FunctionSequence<C, R(Args...)>::PointerToMember
    FunctionSequence<C, R(Args...)>::Test<T>::f[]
        = { nullptr };

template<class C, class R, class... Args>
template<typename FunctionSequence<C, R(Args...)>::PointerToMember... F>
const typename FunctionSequence<C, R(Args...)>::PointerToMember
    FunctionSequence<C, R(Args...)>::Type<F...>::f[]
        = { nullptr };

struct Test
{
    void m1(int) {}
    void m2(int) {}

    FunctionSequence<Test, void(int)>::Type<&Test::m1> s;//, &Test::m2> fs;
};