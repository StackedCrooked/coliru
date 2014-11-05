//#include <Eigen/Dense>
#include <vector>
#include <type_traits>
#include <iostream>

struct Bar 
{
    Bar() = default;
    Bar(int) {}
};

struct Foo
{
    Foo() = default;
    template<typename T, typename U>
    Foo(T const&, U const&) 
    {
        static_assert(std::is_same<T, Bar>::value &&
                      std::is_same<U, Bar>::value, "blah");
    }
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

//    Foo foo1{1,2};  // fails static assertion
    g({1,2}); // ok
    g({a,b,c}); // ok
}
