#include <iostream>

class Interface {
    public:
      Interface() : impl_(0) {}
      struct impl;
      friend const impl * const& get_impl(const Interface &interface);
    private:
      impl* impl_;
};

struct Interface::impl {
    impl() : x(3) {}
    int x;
};

const Interface::impl * const& get_impl(const Interface &interface) {
    return interface.impl_;
}

int main() {
    Interface iface;
    return 0;
}