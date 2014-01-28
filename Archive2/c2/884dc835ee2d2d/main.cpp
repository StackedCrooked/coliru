template<class C, class F>
struct FunctionSequence;

template<class C, class R, class... Args>
struct FunctionSequence<C, R(Args...)>
{
    typedef R(C::*PointerToMember)(Args...);

    template<R(C::*...F)(Args...)>
    struct Type
    {
        static const PointerToMember f[sizeof...(F)];
    };
};

template<class C, class R, class... Args>
template<R(C::*F)(Args...)...>
const typename FunctionSequence<C, R(Args...)>::PointerToMember
    FunctionSequence<C, R(Args...)>::Type<R(C::*...F)(Args...)>::f[sizeof...(F)]
        = { F... };
