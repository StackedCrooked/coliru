#include <iostream>
#include <string>

// In the header...

class Interface {
 public:
   Interface(const int x);
   ~Interface();
   void foo(); 
 protected:
  struct impl;
  impl *impl_;
};

// In the source file...

struct Interface::impl {
    impl(const int y) : y_(y) {}
    int y_;
};

Interface::Interface(const int x)
 : impl_(new impl(x)) {}
 
Interface::~Interface() { delete impl_; }


class InterfaceAccessor : public Interface {
 public:
  //using Interface::impl;
  friend impl& get_impl(Interface& iface);
};

InterfaceAccessor::impl& get_impl(Interface &iface) { return *static_cast<InterfaceAccessor&>(iface).impl_; }

int main() {
    Interface a(1);
    std::cout << get_impl(a).y_ << "\n";
    return 0;
}