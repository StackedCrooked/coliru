struct A {
    A(int f) : f_(f) {}

    int foo(int i) {
        return f_*i;
    }
  private: 
    int f_;
};

#include <boost/phoenix.hpp>
#include <boost/phoenix/function.hpp>
#include <cassert>

int main() {
    using namespace boost::phoenix;
    using namespace boost::phoenix::arg_names;

    A instance(9);

    int direct    = (arg1->*&A::foo)(arg2)
                        (&instance, 7);

    int with_bind = bind(&A::foo, arg1, arg2)
                        (&instance, 7);

    assert(direct == with_bind);

    BOOST_AUTO(afoo, (arg1->*&A::foo)(arg2));

    return afoo(&instance, 2);
}
