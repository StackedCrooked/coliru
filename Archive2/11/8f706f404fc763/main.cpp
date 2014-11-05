//#include <Eigen/Dense>
#include <vector>
#include <iostream>

struct Bar {};
struct Foo
{
    Foo() = default;
    Foo(Bar const&, Bar const&) {}
};

//void f(Eigen::MatrixXd const &) {}
//void f(std::vector<Eigen::MatrixXd> const &) {}

void g(Foo const &) {}
void g(std::vector<Bar> const &) {}

int main()
{
    Bar a, b, c;
//    Eigen::MatrixXd x, y, z;

    // f({x, y}); ambiguity, why?!
//    f({x, y, z}); // ok

    g({a,b}); // ok
    g({a,b,c}); // ok
}
