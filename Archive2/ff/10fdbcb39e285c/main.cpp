#include <iostream>
using namespace std;

template<class T> struct C;

struct A{};

template<class T>
struct C{
    void func(C<T>*){cout<<"C<T>::func"<<endl;}
};

template<class T>
struct M: public C<T>
{
    C<T>* pt;
    void f(){ func(pt); } // Ошибка. Имя func не найдется
};

int main() {
    M<A> m;
    m.f();

    return 0;
}