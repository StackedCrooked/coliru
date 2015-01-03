namespace detail
{
    template <typename T, typename, typename, T...> struct merge;
    template <typename T, template <T...> class S, T... Ks> struct merge<T, S<>, S<>, Ks...> { using type = S<Ks...>; };
    template <typename T, template <T...> class S, T... Is, T... Ks> struct merge<T, S<Is...>, S<>, Ks...> { using type = S<Ks..., Is...>; };
    template <typename T, template <T...> class S, T... Js, T... Ks> struct merge<T, S<>, S<Js...>, Ks...> { using type = S<Ks..., Js...>; };
    template <typename T, bool, typename, typename, T...> struct strip;
    template <typename T, template <T...> class S, T I, T... Is, T J, T... Js, T... Ks>
    struct strip<T, true, S<I, Is...>, S<J, Js...>, Ks...> { using type = merge<T, S<I, Is...>, S<Js...>, Ks..., J>; };
    template <typename T, template <T...> class S, T I, T... Is, T J, T... Js, T... Ks>
    struct strip<T, false, S<I, Is...>, S<J, Js...>, Ks...> { using type = merge<T, S<Is...>, S<J, Js...>, Ks..., I>; };
    template <typename T, template <T...> class S, T I, T... Is, T J, T... Js, T... Ks>
    struct merge<T, S<I, Is...>, S<J, Js...>, Ks...> : strip<T, (I>J), S<I, Is...>, S<J, Js...>, Ks...>::type {};
}
template <typename A, typename B> using merge = typename detail::merge<int, A, B>::type;

#include <iostream>

struct ActionOption {
    virtual void foo(int) const = 0;
};

template <int> struct ActionType;

template <> struct ActionType<0> : ActionOption {
    virtual void foo(int) const override {std::cout << "ActionType<0>::foo(int) called.\n";}
};

template <> struct ActionType<1> : ActionOption {
    virtual void foo(int) const override {std::cout << "ActionType<1>::foo(int) called.\n";} 
};

template <> struct ActionType<2> : ActionOption {
    virtual void foo(int) const override {std::cout << "ActionType<2>::foo(int) called.\n";}
};

template <> struct ActionType<3> : ActionOption {
    virtual void foo(int) const override {std::cout << "ActionType<3>::foo(int) called.\n";}
};

template <> struct ActionType<4> : ActionOption {
    virtual void foo(int) const override {std::cout << "ActionType<4>::foo(int) called.\n";}
};

template <int...> struct PossibleActions;
template <> struct PossibleActions<> { void operator()(int) const {} };

template <int First, int... Rest>
struct PossibleActions<First, Rest...> : ActionType<First>, PossibleActions<Rest...> {
    void operator()(int a) const {
        ActionType<First>::foo(a);
        PossibleActions<Rest...>::operator()(a);
    }
};

struct Object : PossibleActions<1, 2>, PossibleActions<3, 4>
{
    void foo(int a)
    {
        merge<PossibleActions<1, 2>, PossibleActions<3, 4>>()(a);
    }
};

using OneAndFour = PossibleActions<1, 4>;
using TwoAndThree = PossibleActions<2, 3>;

struct Blob : PossibleActions<0>, OneAndFour, TwoAndThree
{
    void foo(int a)
    {
        merge<PossibleActions<0>, merge<OneAndFour, TwoAndThree>>()(a);
    }
};

int main()
{
    Object object;
    object.foo(12);
    std::cout << std::endl;

    Blob blob;
    blob.foo(12);
    std::cout << std::endl;
}
