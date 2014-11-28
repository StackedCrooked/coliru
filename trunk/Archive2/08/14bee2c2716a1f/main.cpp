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

template <typename H, typename T>
struct Stack;

template <typename T, int N>
struct Stack<Disk<N>, T> {
    typedef Disk<N> Head;
    typedef T Tail;
};

#define STACK_0() NullType
#define STACK_1(D1) Stack<D1, NullType>
#define STACK_2(D1, D2) Stack<D1, STACK_1(D2)>
#define STACK_3(D1, D2, D3) Stack<D1, STACK_2(D2, D3)>
#define STACK_4(D1, D2, D3, D4) Stack<D1, STACK_3(D2, D3, D4)>

template <typename T>
struct Pop;

template <int N, typename T1>
struct Pop<Stack<Disk<N>, T1>> {
    typedef Stack<Disk<N>, typename Pop<T1>::result> result;
};

template<int N>
struct Pop<Stack<Disk<N>, NullType>> {
    typedef NullType result;
};

template <typename T, int M>
struct Push;

template <int N, typename T1, int M>
struct Push<Stack<Disk<N>, T1>, M> {
    typedef Stack<Disk<N>, typename Push<T1, M>::result> result;
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
};

int main() {
    TD<STACK_4(Disk<4>, Disk<3>, Disk<2>, Disk<1>)> td1;
    TD<Pop<STACK_4(Disk<4>, Disk<3>, Disk<2>, Disk<1>)>::result> td2;
    TD<Push<Pop<STACK_4(Disk<4>, Disk<3>, Disk<2>, Disk<1>)>::result, 5>::result> td3;
    //Hanoi<STACK_4(Disk<4>, Disk<3>, Disk<2>, Disk<1>), STACK_0(), STACK_0()>::solution s;
    //TD<decltype(s)> td;
}