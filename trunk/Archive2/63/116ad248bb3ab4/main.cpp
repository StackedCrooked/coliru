#include <iostream>

class A {
    public:
    static inline bool compute(int a, int b) {return a < b;}
};

template <class Functor>
class B {
    public:
    static inline bool compute(int a, int b) {return Functor::compute(a,b);}
};

template <class Functor>
class C {
    public:
    static inline bool compute(int a, int b) {return Functor::compute(a,b);}
};

typedef B<A> D;
typedef C<D> E;

int main() {
    std::cout << B<B<C<B<B<B<C<B<E> > > > > > > >::compute(7,8) << std::endl;
}
