struct iA {
    using type = int;
};
template <class T> struct tA {
    using type = T;
};

struct iB1 : iA {
    void f(type i) {}
};
struct iB2 : tA<int> {
    void f(type i) {}
};
template <class T> struct tB1 : iA {
    void f(type i) {}
};
template <class T> struct tB2 : tA<int> {
    void f(type i) {}
};
template <class T> struct tB3 : tA<T> {
    using typename tA<T>::type;
    void f(type i) {}
};

int main() {}