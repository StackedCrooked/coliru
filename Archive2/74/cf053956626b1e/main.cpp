#include <iostream>

class Interface {
    public:
      Interface() : impl_(0) {}
      struct impl;
      friend const impl * const& get_impl(const Interface& interface);
      friend void print_x(const Interface& interface);
    private:
      impl* impl_;
};

struct Interface::impl {
    impl() : x(3) {}
    int x;
};

const Interface::impl * const& get_impl(const Interface& interface) {
    return const_cast<const Interface::impl * const&>(
        static_cast<Interface::impl * const &>(interface.impl_));
}

Interface::impl *& get_impl(Interface& interface) {
    return const_cast<Interface::impl *&>(get_impl(const_cast<const Interface&>(interface)));
}

void print_x(const Interface& interface) {
    if (interface.impl_)
    {
        std::cout << interface.impl_->x << "\n";
    }
    else
    {
        std::cout << "Null pointer!\n";
    }
}

int main() {
    Interface iface;
    print_x(iface);
    Interface::impl*& impl_ptr = get_impl(iface);
    impl_ptr = new Interface::impl();
    print_x(iface);
    return 0;
}
