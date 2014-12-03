#include <memory>
#include <iostream>
#include <vector>

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
}

using dynamic_release = detail::basic_dynamic_release<std::function<void()>>;

void do_foo() { std::cout << "Foo\n"; }
void do_bar() { std::cout << "Bar\n"; }

int main(void) {
    using InterfaceWrapper = std::shared_ptr<detail::basic_dynamic_release<void(*)(void)>>;
    using Thing = InterfaceWrapper::element_type;

    {
        std::vector<InterfaceWrapper> thing_vector;

        auto thing = std::make_shared<Thing>(do_foo);

        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
    } // prints "Foo" once

    {
        std::vector<InterfaceWrapper> thing_vector;

        auto thing = std::make_shared<Thing>(do_foo);

        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);

        *thing = do_bar; // Prints nothing

        thing_vector.push_back(thing);
    } // prints "Bar" once
}
