struct A {
    typedef int type;
};

template<class T>
struct B {
    typedef typename T::type d;
};

int main() {
    B<A&>::d c;
}