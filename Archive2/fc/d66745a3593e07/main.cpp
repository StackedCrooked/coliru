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
struct Disc {
    const static int value{N};
};

template <typename H, typename S>
struct Stack;

template <typename S, int N>
struct Stack<Disc<N>, S> {
    typedef Disc<N> Head;
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
struct Pop<Stack<Disc<N>, R>> {
    typedef Stack<Disc<N>, typename Pop<R>::result> result;
};

template<int N>
struct Pop<Stack<Disc<N>, NullType>> {
    typedef NullType result;
};

template <typename S>
struct Top;

template <int N, typename R>
struct Top<Stack<Disc<N>, R>> {
    typedef typename Top<R>::result result;
};

template <int N>
struct Top<Stack<Disc<N>, NullType>> {
    typedef Disc<N> result;
};

template <typename S, typename D>
struct Push;

template <int N, typename S, typename D>
struct Push<Stack<Disc<N>, S>, D> {
    typedef Stack<Disc<N>, typename Push<S, D>::result> result;
};

template <int M>
struct Push<NullType, Disc<M>> {
    typedef Stack<Disc<M>, NullType> result;
};

template <typename S1, typename S2, typename S3>
struct Hanoi {
    typedef S1 Stack1;
    typedef S2 Stack2;
    typedef S3 Stack3;
    
    template <int I, int J, int unused=0>
    struct MoveDisc;
    
    template <int unused>
    struct MoveDisc<1, 2, unused> {
        typedef Hanoi<
            typename Pop<Stack1>::result,
            typename Push<Stack2, typename Top<Stack1>::result>::result,
            Stack3
        > result;
    };

//    template <int unused>
//    struct MoveDisc<2, 1> {
//        typedef Hanoi<
//            typename Push<Stack1, typename Top<Stack2>::result>::result,
//            typename Pop<Stack2>::result,
//            Stack3
//        >::result;
//    };
//
//    template <int unused>
//    struct MoveDisc<1, 3> {
//        typedef Hanoi<
//            typename Pop<Stack1>::result,
//            Stack2,
//            typename Push<Stack3, typename Top<Stack1>::result>::result,
//        >::result;
//    };
//
//    template <int unused>
//    struct MoveDisc<3, 1> {
//        typedef Hanoi<
//            typename Push<Stack1, typename Top<Stack3>::result>::result,
//            Stack2,
//            typename Pop<Stack3>::result,
//        >::result;
//    };
//
//    template <int unused>
//    struct MoveDisc<2, 3> {
//        typedef Hanoi<
//            Stack1,
//            typename Pop<Stack2>::result,
//            typename Push<Stack3, typename Top<Stack2>::result>::result,
//        >::result;
//    };
//
//    template <int unused>
//    struct MoveDisc<3, 2> {
//        typedef Hanoi<
//            Stack1,
//            typename Push<Stack2, typename Top<Stack3>::result>::result,
//            typename Pop<Stack3>::result,
//        >::result;
//    };
};

static_assert(
    is_same<
        Pop<STACK_1(Disc<1>)>::result,
        NullType
    >::value, "test1"
);

static_assert(
    is_same<
        Top<STACK_2(Disc<2>, Disc<1>)>::result,
        Disc<1>
    >::value, "test2"
);

static_assert(
    is_same<
        Push<STACK_1(Disc<2>), Disc<1>>::result,
        STACK_2(Disc<2>, Disc<1>)
    >::value, "test2"
);

static_assert(
    is_same<
        typename Hanoi<
            STACK_4(Disc<4>, Disc<3>, Disc<2>, Disc<1>),
            STACK_0(),
            STACK_0()>::MoveDisc<1,2>::result,
        Hanoi<
            STACK_3(Disc<4>, Disc<3>, Disc<2>),
            STACK_1(Disc<1>),
            STACK_0()>
    >::value, "test3"
);


int main() {
        
}