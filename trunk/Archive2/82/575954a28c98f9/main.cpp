template <int...> struct PossibleActions {};

template <typename, typename, int...> struct merge;
template <int... Ks> struct merge<PossibleActions<>, PossibleActions<>, Ks...> { using type = PossibleActions<Ks...>; };
template <int... Is, int... Ks> struct merge<PossibleActions<Is...>, PossibleActions<>, Ks...> { using type = PossibleActions<Ks..., Is...>; };
template <int... Js, int... Ks> struct merge<PossibleActions<>, PossibleActions<Js...>, Ks...> { using type = PossibleActions<Ks..., Js...>; };

template <bool, typename, typename, int...>
struct strip;

template <int I, int... Is, int J, int... Js, int... Ks>
struct strip<true, PossibleActions<I, Is...>, PossibleActions<J, Js...>, Ks...>
{
    using type = merge<PossibleActions<I, Is...>, PossibleActions<Js...>, Ks..., J>;
};

template <int I, int... Is, int J, int... Js, int... Ks>
struct strip<false, PossibleActions<I, Is...>, PossibleActions<J, Js...>, Ks...>
{
    using type = merge<PossibleActions<Is...>, PossibleActions<J, Js...>, Ks..., I>;
};

template <int I, int... Is, int J, int... Js, int... Ks>
struct merge<PossibleActions<I, Is...>, PossibleActions<J, Js...>, Ks...>
    : strip<(I>J), PossibleActions<I, Is...>, PossibleActions<J, Js...>, Ks...>::type {};

template <typename A, typename B>
using sort = typename merge<A, B>::type;

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

template <> struct PossibleActions<> { void operator()(int) const {} };

template <int First, int... Rest>
struct PossibleActions<First, Rest...> : ActionType<First>, PossibleActions<Rest...> {
    void operator()(int a) const {
        ActionType<First>::foo(a);
        PossibleActions<Rest...>::operator()(a);
    }
};

// Anything that can call ActionType<2>::foo(int) can also call ActionType<3>::foo(int).
struct Object : sort<PossibleActions<1,  2>, PossibleActions<3,  4>> {
    void foo(int a) {sort<PossibleActions<1,  2>, PossibleActions<3,  4>>()(a);}
};

using TwoAndThree = PossibleActions<2, 3>;

struct Blob : sort<PossibleActions<1, 4>, TwoAndThree> {
    void foo(int a) {sort<PossibleActions<1, 4>, TwoAndThree>()(a);}
};

int main() {
    Object object;
    object.foo(12);  // ActionType<1>::foo(int) called  ActionType<2>::foo(int) called   ActionType<3>::foo(int) called  ActionType<4>::foo(int) called
    std::cout << std::endl;

    Blob blob;
    blob.foo(12);  // ActionType<0>::foo(int) called  ActionType<2>::foo(int) called   ActionType<3>::foo(int) called  ActionType<4>::foo(int) called
    std::cout << std::endl;
}
