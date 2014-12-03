#include <memory>
#include <iostream>

namespace detail {

    template <typename T> struct default_construction final {
        T operator()() const { return {}; }
    };

    template <typename InterfaceCallable, typename Factory = default_construction<InterfaceCallable> >
    struct basic_dynamic_release {
        basic_dynamic_release() = default;

        template <typename F> basic_dynamic_release(F&& f) : _f(std::forward<F>(f)) { }
        template <typename F> basic_dynamic_release& operator=(F&& f) 
            { _f = std::forward<F>(f); return *this; }

        ~basic_dynamic_release() { _f(); }
      private:
        InterfaceCallable _f = Factory()();
    };

    using dynamic_interface = std::function<void()>;
    template <typename Factory = default_construction<dynamic_interface> >
    using dynamic_release   = basic_dynamic_release<dynamic_interface, Factory>;
}

#include <vector>

void do_foo() { std::cout << "Foo\n"; }
void do_bar() { std::cout << "Bar\n"; }

struct foo_default { detail::dynamic_interface operator()() const { return do_foo; } };

int main(void) {
    using InterfaceWrapper = std::shared_ptr<detail::dynamic_release<foo_default> >;
    using Thing = InterfaceWrapper::element_type;

    {
        std::vector<InterfaceWrapper> thing_vector;

        auto thing = std::make_shared<Thing>();

        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
    } // prints "Foo" once

    {
        std::vector<InterfaceWrapper> thing_vector;

        auto thing = std::make_shared<Thing>();

        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);

        *thing = &do_bar; // Prints nothing

        thing_vector.push_back(thing);
    } // prints "Bar" once
}
