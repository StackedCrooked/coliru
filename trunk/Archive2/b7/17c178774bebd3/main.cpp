#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <functional>
#include <algorithm>

using namespace std;

struct NullType { };
struct EmptyType { };

template <typename H, typename T> struct TypeList {
    using Head = H;
    using Tail = T;
};

template <typename Head, typename... Rest> struct TypeListGenerator {
    using result = TypeList<Head, typename TypeListGenerator<Rest...>::result>;
};
template <> struct TypeListGenerator<NullType> {
    using result = NullType;
};
template <typename Last> struct TypeListGenerator<Last> {
    using result = TypeList<Last, NullType>;
};

#define TYPELIST_0() NullType
#define TYPELIST_1(T1) TypeList<T1, NullType>
#define TYPELIST_2(T1, T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) TypeList<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) TypeList<T1, TYPELIST_3(T2, T3, T4)>
#define TYPELIST_5(T1, T2, T3, T4, T5) TypeList<T1, TYPELIST_4(T2, T3, T4, T5)>

template <typename TL> struct Length;
template <> struct Length<NullType> {
    static const int value = 0;
};
template <typename H, typename T> struct Length<TypeList<H, T>> {
    static const int value = Length<T>::value + 1;
};

template <typename TL, unsigned int index, typename D> struct TypeAtNonStrict;
template <unsigned int index, typename D> struct TypeAtNonStrict<NullType, index, D> {
    using type = D;
};
template <typename H, typename T, typename D> struct TypeAtNonStrict<TypeList<H, T>, 0, D> {
    using type = H;
};
template <typename H, typename T, unsigned int index, typename D> struct TypeAtNonStrict<TypeList<H, T>, index, D> {
    using type = typename TypeAtNonStrict<T, index-1, D>::type;
};

template <typename TL, unsigned int index> struct TypeAt {
    using type = typename TypeAtNonStrict<TL, index, NullType>::type;
};

template <typename TL, typename F> struct IndexOf;
template <typename F> struct IndexOf<NullType, F> {
    static const int value = -1;
};
template <typename F, typename T> struct IndexOf<TypeList<F, T>, F> {
    static const int value = 0;
};
template <typename H, typename T, typename F> struct IndexOf<TypeList<H, T>, F> {
    static const int temp = IndexOf<T, F>::value;
    static const int value = (temp == -1) ? -1 : temp + 1;
};

template <typename TL, typename A> struct Append;
template <> struct Append<NullType, NullType> {
    using result = NullType;
};
template <typename A> struct Append<NullType, A> {
    using result = TYPELIST_1(A);
};
template <typename H, typename T> struct Append<NullType, TypeList<H, T>> {
    using result = TypeList<H, T>;
};
template <typename H, typename T, typename A> struct Append<TypeList<H, T>, A> {
    using result = TypeList<H, typename Append<T, A>::result>;
};

template <typename TL, typename E> struct Erase;
template <typename E> struct Erase<NullType, E> {
    using result = NullType;
};
template <typename T, typename E> struct Erase<TypeList<E, T>, E> {
    using result = T;
};
template <typename H, typename T, typename E> struct Erase<TypeList<H, T>, E> {
    using result = TypeList<H, typename Erase<T, E>::result>;
};

template <typename TL> struct NoDuplicates;
template <> struct NoDuplicates<NullType> {
    using result = NullType;
};
template <typename H, typename T> struct NoDuplicates<TypeList<H, T>> {
    using noDuplicatesInT = typename NoDuplicates<T>::result;
    using head_erased = typename Erase<noDuplicatesInT, H>::result;
    using result = TypeList<H, head_erased>;
};

template <typename TL, typename R1, typename R2> struct Replace;
template <typename R1, typename R2> struct Replace<NullType, R1, R2> {
    using type = NullType;
};
template <typename T, typename R1, typename R2> struct Replace<TypeList<R1, T>, R1, R2> {
    using type = TypeList<R2, T>;
};
template <typename H, typename T, typename R1, typename R2> struct Replace<TypeList<H, T>, R1, R2> {
    using type = TypeList<H, typename Replace<T, R1, R2>::type>;
};

template <typename TL, typename D> struct MostDerived;
template <typename D> struct MostDerived<NullType, D> {
    using type = D;
};
template <typename H, typename T, typename D> struct MostDerived<TypeList<H, T>, D> {
    using candidate = typename MostDerived<T, D>::type;
    using type = typename conditional<is_base_of<H, candidate>::value, candidate, H>::type;
};
template <typename TL> struct DerivedToFront;
template <> struct DerivedToFront<NullType> {
    using result = NullType;
};
template <typename H, typename T> struct DerivedToFront<TypeList<H, T>> {
    using most_derived = typename MostDerived<T, H>::type;
    using replaced = typename Replace<T, most_derived, H>::type;
    using result = TypeList<most_derived, typename DerivedToFront<replaced>::result>;
};

template <typename R, typename TL>
class FunctorImpl;

template <typename R>
class FunctorImpl<R, NullType> {
public:
    virtual R operator()() = 0;
    virtual FunctorImpl* clone() const = 0;
    virtual ~FunctorImpl() { }
};

template <typename R, typename P1>
class FunctorImpl<R, TYPELIST_1(P1)> {
public:
    virtual R operator()(P1) = 0;
    virtual FunctorImpl* clone() const = 0;
    virtual ~FunctorImpl() { }
};

template <typename R, typename P1, typename P2>
class FunctorImpl<R, TYPELIST_2(P1, P2)> {
public:
    virtual R operator()(P1, P2) = 0;
    virtual FunctorImpl* clone() const = 0;
    virtual ~FunctorImpl() { }
};

template <typename R, typename P1, typename P2, typename P3>
class FunctorImpl<R, TYPELIST_3(P1, P2, P3)> {
public:
    virtual R operator()(P1, P2, P3) = 0;
    virtual FunctorImpl* clone() const = 0;
    virtual ~FunctorImpl() = 0;
};

template <typename R, typename TL>
class Functor {
public:
    using ResultType = R;
    using ParamList = TL;
    using P1 = typename TypeAtNonStrict<TL, 0, EmptyType>::type;
    using P2 = typename TypeAtNonStrict<TL, 1, EmptyType>::type;
    using P3 = typename TypeAtNonStrict<TL, 2, EmptyType>::type;
    using P4 = typename TypeAtNonStrict<TL, 3, EmptyType>::type;
public:
    template <class Fun> Functor(const Fun& fun);
    R operator()() { return (*impl_)(); }
    R operator()(P1 p1) { return (*impl_)(p1); }
    R operator()(P1 p1, P2 p2) { return (*impl_)(p1, p2); }
    R operator()(P1 p1, P2 p2, P3 p3) { return (*impl_)(p1, p2, p3); }
private:
    FunctorImpl<R, TL>* impl_;
};

template <typename PF, typename F>
class FunctorHandler : public FunctorImpl<typename PF::ResultType, typename PF::ParamList> {
public:
    using ResultType = typename PF::ResultType;
public:
    FunctorHandler(const F& f) : fun_(f) { }
    FunctorHandler* clone() const { return new FunctorHandler(*this); }
    ResultType operator()() { return fun_(); }
    ResultType operator()(typename PF::P1 p1) { return fun_(p1); }
    ResultType operator()(typename PF::P1 p1, typename PF::P2 p2) { return fun_(p1, p2); }
private:
    F fun_;
};

template <typename R, typename TL>
template <typename Fun>
Functor<R, TL>::Functor(const Fun& fun)
: impl_(new FunctorHandler<Functor, Fun>(fun)) {
}

struct TestFunctor {
    void operator()(int i, double d) { cout << i << ", " << d << endl; }
};

int main() {
    TestFunctor f;
    Functor<void, TYPELIST_2(int, float)> cmd(f);
    cmd(4, 4.0);
}
