#include <memory>
#include <iostream>

class Interface {
  public:
    virtual void WriteIt() = 0;
    virtual ~Interface() = default;

    struct DeleteTrigger final { 
        void operator()(Interface* o) const {
            o->WriteIt(); 
            delete o;
        }
    };
};

class Foo : public Interface {
    void WriteIt() { printf("Foo\n"); }
};

class Bar : public Interface {
    void WriteIt() { printf("Bar\n"); }
};

using InterfaceWrapper = std::shared_ptr<std::unique_ptr<Interface, Interface::DeleteTrigger> >;

InterfaceWrapper make_thing(Interface* o = new Foo) {
    return std::make_shared<InterfaceWrapper::element_type>(o);
}

void set_bar(InterfaceWrapper& o) {
    o->reset(new Bar);
}

#include <vector>

int main(void) {
    {
        std::vector<InterfaceWrapper> thing_vector;

        auto thing = make_thing();

        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
    } // prints "Foo" once

    {
        std::vector<InterfaceWrapper> thing_vector;

        auto thing = make_thing();

        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);

        set_bar(thing); // prints "Foo" once

        thing_vector.push_back(thing);
    } // prints "Bar" once
}
