#include <iostream>
#include <typeinfo>


template<typename T, typename R, typename ...Args>
void check(R(T::*)(Args...) const)
{
    std::cout << "return type: " << typeid(R).name() << " arity: " << sizeof...(Args) << std::endl;
}

template <typename...> struct functor;

template <> struct functor<> { };

template <typename L, typename... More> struct functor<L,More...> : L, functor<More...> {
    functor(L l, More... more) : L(l), functor<More...>(more...) { }
    using L::operator();
};

template <typename... lambdae> functor<lambdae...>  make_functor(lambdae... ll) {
    return { ll... };
}

int main()
{
    {
        auto lambda = make_functor([](int, int) { return 2; }, [](int, int, int) { return 3; });
        
        lambda(1,2);
        lambda(1,2,3);
        
        check(&decltype(lambda)::operator());
    }
    {
        auto lambda = make_functor([](int, int, int) { return 3; }, [](int, int) { return 2; });
        
        lambda(1,2);
        lambda(1,2,3);
        
        check(&decltype(lambda)::operator());
    }
}

