#include <utility>
#include <iostream>
#include <boost/variant.hpp>

namespace my {
    using std::cout; using std::endl;

    class X
    {
    private:
        X& operator=( X const& ) = delete;

    public:
        X() {}

        X( X const& )
        { cout << "Copy" << endl; }

        X( X&& )
        { cout << "Move" << endl; }
    };
}  // my

auto foo_true()
    -> my::X
{ return my::X(); }

auto foo_false()
    -> my::X const&
{ static my::X const static_x; return static_x; }

boost::variant<my::X, my::X const&> foo_impl(bool b) {
  if (b) {
    return foo_true();
  } else {
    return foo_false();
  }
}

#define do_foo_true boost::get<my::X>(foo_impl(true))
#define do_foo_false boost::get<my::X const&>(foo_impl(false))


#define foo(b)\
 do_foo_##b

auto main() -> int
{
    using namespace my;

    cout << "A" << endl; const X& x1 = foo(true);   // No copies
    cout << "B" << endl; const X& x2 = foo(false);  // No copies
    cout << "C" << endl; X x3 = foo(true);          // No copies, one move (or zero via RVO)
    cout << "D" << endl; X x4 = foo(false);         // One copy
    
    (void)x1; (void)x2; (void)x3; (void)x4;
}