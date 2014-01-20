#include <iostream>
#include <typeinfo>

using namespace std;

template <class A>
void process_one_type() {
    cerr << typeid(A).name() << ' ';
}

template <class ...B> void func()
{
    int _[] = {0, (process_one_type<B>(), 0)...};
    (void)_;
    cerr << '\n';
}

int main() {
   func<int,int,char,double>();
}
