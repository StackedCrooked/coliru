#include <memory>
#include <iostream>
#include <vector>

struct dynamic_release {
    template <typename F> dynamic_release(F&& f) : _f(std::forward<F>(f)) { }
    template <typename F> dynamic_release& operator=(F&& f) 
        { _f = std::forward<F>(f); return *this; }

    ~dynamic_release() { _f(); }
  private:
    std::function<void()> _f;
};

void do_foo() { std::cout << "Foo\n"; }
void do_bar() { std::cout << "Bar\n"; }

int main(void) {
    using InterfaceWrapper = std::shared_ptr<dynamic_release>;
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
