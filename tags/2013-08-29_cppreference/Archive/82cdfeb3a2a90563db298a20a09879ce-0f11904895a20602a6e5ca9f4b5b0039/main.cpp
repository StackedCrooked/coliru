#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Foo {
public:
    T val;
    Foo(T _v): val(_v){}
    friend ostream& operator<< (ostream& out, const Foo& A) {
        out << A.val;
        return out;
    }
};

template <class X, class Y>
typename std::conditional<(sizeof(X)>sizeof(Y)),Foo<X>,Foo<Y>>::type
operator+(const Foo<X>& A, const Foo<Y> & B) {
    typedef typename std::conditional<(sizeof(X)>sizeof(Y)),Foo<X>,Foo<Y>>::type result_type;
    return result_type(A.val + B.val);
}

int main() {
    Foo<double> a(1.5);
    Foo<int> b(2);
    cout << a << endl;
    cout << b << endl;
    cout << a+b << endl;
}