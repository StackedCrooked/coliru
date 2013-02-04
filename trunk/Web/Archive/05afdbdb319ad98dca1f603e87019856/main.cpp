struct A {
    typedef int type;
};

template<class T>
struct B {
    typedef typename T::type d;
};

template<class T>
void f(T& x) {
    g(x);
}

template<class T>
void g(T x) {
    typename B<T>::type y;
}

int main() {
    A a;
    f(a);
}