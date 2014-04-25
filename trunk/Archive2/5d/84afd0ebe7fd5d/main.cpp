#include <tuple>
#include <iostream>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>

struct A {};
struct B {}; 
struct C {}; 
struct D {}; 
struct E {};

int main() {
    using namespace std;
    using namespace boost::fusion;

    A a;
    B b;
    C c;
    D d;
    E e;

    for_each(tie(a, b, c, d, e), [](auto &x) {
        cout << typeid(x).name() << endl;
    });
}