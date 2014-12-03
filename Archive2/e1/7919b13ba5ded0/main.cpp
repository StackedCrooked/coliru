#include <memory>
#include <iostream>

namespace detail {

    template <typename InterfaceCallable>
    struct basic_dynamic_release {
        basic_dynamic_release() = default;

        template <typename F> basic_dynamic_release(F&& f) : _f(std::forward<F>(f)) { }
        template <typename F> basic_dynamic_release& operator=(F&& f) 
            { _f = std::forward<F>(f); return *this; }

        ~basic_dynamic_release() { _f(); }
      private:
        InterfaceCallable _f;
    };

    using dynamic_interface = std::function<void()>;
    using dynamic_release   = basic_dynamic_release<dynamic_interface>;
}

#include <vector>

void do_foo() { std::cout << "Foo\n"; }
void do_bar() { std::cout << "Bar\n"; }

int main(void) {
    using InterfaceWrapper = std::shared_ptr<detail::dynamic_release>;
    using Thing = InterfaceWrapper::element_type;

    {
        std::vector<InterfaceWrapper> thing_vector;

        auto thing = std::make_shared<Thing>(&do_foo);

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
