#include <stdio.h>
#include <memory>
#include <vector>

class Interface {
  public:
    virtual void WriteIt() = 0;
    virtual ~Interface() {}
};

class Foo : public Interface {
    void WriteIt() { printf("Foo\n"); }
};

class Bar : public Interface {
    void WriteIt() { printf("Bar\n"); }
};

class InterfaceWrapper {
    using UI = std::unique_ptr<Interface>;

    std::shared_ptr<UI> _sui {new UI{new Foo}, [](UI*p){ (*p)->WriteIt(); delete p; }};

  public:
    void MakeBar() { _sui->reset(new Bar); }
};

int main(void) {
    {
        std::vector<InterfaceWrapper> thing_vector;

        InterfaceWrapper thing;

        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
    }

    {
        std::vector<InterfaceWrapper> thing_vector;

        InterfaceWrapper thing;

        thing_vector.push_back(thing);

        thing.MakeBar();

        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
    }
}
