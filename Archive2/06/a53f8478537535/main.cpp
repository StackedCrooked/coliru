#include <utility>
#include <tuple>
#include <iostream>

namespace std
{
    /*template<size_t... Is> struct index_sequence {};
    template<size_t N, size_t... Is> make_index_sequence : make_index_sequence<N-1, N-1, Is...> {};
    template<size_t... Is> make_index_sequence<0, Is...> : index_sequence<Is...> {};*/
}

template <typename... Args>
auto args(Args&&... args) {
    return std::make_tuple(std::forward<Args>(args)...);
}

template <class C, class TupleArgs, std::size_t... Indices>
C construct_class_unpacked_(TupleArgs&& args, std::index_sequence<Indices...>) {
    return C(std::get<Indices>(std::forward<TupleArgs>(args))...);
}

template <class C, typename TupleArgs>
C construct(TupleArgs&& args) {
    return construct_class_unpacked_<C>(std::forward<TupleArgs>(args), std::make_index_sequence<std::tuple_size<typename std::decay<TupleArgs>::type>::value>());
}

template<class Tuple>
auto make_index_sequence_for_tuple_expansion(Tuple&&)
{
    return std::make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>();
}

struct Root {
    Root(int l) : l_(l) {
    }

    protected:
        Root() : l_(-2) {}

    public:
        int l_;
};

struct A : public virtual Root {
    A(int i, float f) : i_(i), f_(f) {}

    int i_;
    float f_;
};

struct B : public virtual Root {
    B(int j, float g) : j_(j), g_(g) {}

    int j_;
    float g_;
};

struct C : public virtual Root {
    C() : x_(1), y_(3.1) {
    }

    int x_;
    float y_;
};

template<class T>
struct Wrap : T
{
    template<class Tuple, std::size_t... Is>
    Wrap(Tuple&& tuple, std::index_sequence<Is...>)
        : T( std::get<Is>(std::forward<Tuple>(tuple))... )
    {}
    
    template<class Tuple>
    Wrap(Tuple&& tuple) : Wrap(std::forward<Tuple>(tuple), make_index_sequence_for_tuple_expansion(tuple))
    {}
};

template <typename Base, typename... Bases>
struct S : public Wrap<Bases>... {
    template <typename Arg, typename... TupleArgs>
    S(Arg&& arg, TupleArgs&&... args) : Base(std::forward<Arg>(arg)), Wrap<Bases>(std::forward<TupleArgs>(args))... {
    }
};

int main (int argc, char const* argv[]) {
    {
        S<Root, A, C, B> s(4, args(2, 3.1f), args(), args(3, 5.3f));
        std::cout << s.i_ << "\n";
        std::cout << s.f_ << "\n";
        std::cout << s.j_ << "\n";
        std::cout << s.g_ << "\n";
        std::cout << s.x_ << "\n";
        std::cout << s.y_ << "\n";
        std::cout << s.l_ << "\n";
    }
}