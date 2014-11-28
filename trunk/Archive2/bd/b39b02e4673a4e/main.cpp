#include <map>
#include <iostream>
#include <functional>
#include <tuple>
#include <iomanip>
#include <utility>
#include <unordered_map>
#include <vector>
using namespace std;

template <typename T> class TD;

struct NullType {};

template <int N>
struct Disk {
    const int value{N};
};

template <typename H, typename S>
struct Stack;

template <typename S, int N>
struct Stack<Disk<N>, S> {
    typedef Disk<N> Head;
    typedef S Tail;
};

#define STACK_0() NullType
#define STACK_1(D1) Stack<D1, NullType>
#define STACK_2(D1, D2) Stack<D1, STACK_1(D2)>
#define STACK_3(D1, D2, D3) Stack<D1, STACK_2(D2, D3)>
#define STACK_4(D1, D2, D3, D4) Stack<D1, STACK_3(D2, D3, D4)>

template <typename S>
struct Pop;

template <int N, typename R>
struct Pop<Stack<Disk<N>, R>> {
    typedef Stack<Disk<N>, typename Pop<R>::result> result;
};

template<int N>
struct Pop<Stack<Disk<N>, NullType>> {
    typedef NullType result;
};

template <typename S>
struct Top;

template <int N, typename R>
struct Top<Stack<Disk<N>, R>> {
    typedef typename Top<R>::result result;
};

template <int N>
struct Top<Stack<Disk<N>, NullType>> {
    typedef Disk<N> result;
};

template <typename S, int M>
struct Push;

template <int N, typename S, int M>
struct Push<Stack<Disk<N>, S>, M> {
    typedef Stack<Disk<N>, typename Push<S, M>::result> result;
};

template <int N, int M>
struct Push<Stack<Disk<N>, NullType>, M> {
    typedef Stack<Disk<N>, Stack<Disk<M>, NullType>> result;
};

template <typename S1, typename S2, typename S3>
struct Hanoi {
    typedef S1 Stack1;
    typedef S2 Stack2;
    typedef S3 Stack3;
    
    template <int I, int J>
    struct MoveDisc;
    
    template <>
    struct MoveDisc<1, 2> {
        typedef Hanoi<
            typename Pop<S1>::result,
            typename Push<S2, typename Top<S1>::result>::result,
            S3
        >::result;
    };
};

template <typename S1, typename S2, typename S3>

static_assert(
    is_same<
        Pop<STACK_1(Disk<1>)>::result,
        NullType
    >::value, "test1"
);

static_assert(
    is_same<
        Top<STACK_2(Disk<2>, Disk<1>)>::result,
        Disk<1>
    >::value, "test2"
);

static_assert(
    is_same<
        Push<STACK_1(Disk<2>), Disk<1>>::result,
        STACK_2(Disk<2>, Disk<1>)
    >::value, "test2"
);

static_assert(
    is_same<
        typename Hanoi<
            STACK_4(Disk<4>, Disk<3>, Disk<2>, Disk<1>),
            STACK_0(),
            STACK_0()>::MoveDisk<1,2>::result,
        Hanoi<
            STACK_3(Disk<4>, Disk<3>, Disk<2>),
            STACK_1(Disk<1>),
            STACK_0()>
    >::value, "test3"
);


int main() {
        
}