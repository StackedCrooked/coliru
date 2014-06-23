#include <boost/variant.hpp>
#include <cassert>
#include <iostream>
struct X{};
X by_value() { return X{}; }
static X x;
const X& by_reference() { return x; }

boost::variant<X,X const&> foo(bool b) {
  if (b) {
    return by_value();
  } else {
    return by_reference();
  }
}

int main() {
    auto by_val = foo(true);
    auto by_ref = foo(false);
    
    
    assert(by_val.which() == 0);
    assert(by_ref.which() == 1);
    
    std::cout << "Working\n";
}
