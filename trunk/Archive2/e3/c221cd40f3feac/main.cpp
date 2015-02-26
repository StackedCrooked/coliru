#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Thing;
std::shared_ptr<Thing> make_thing();

class Thing
{
    friend std::shared_ptr<Thing> make_thing();

    Thing()
    {
        std::cout << "Thing constructor" << std::endl;
    }
};

std::shared_ptr<Thing> make_thing()
{
    // err: Thing::Thing() is private within make_shared
    // auto thing = std::make_shared<Thing>();

    // this is okay
    struct AccessThing : public Thing {
        AccessThing() : Thing() { }
    };

    auto thing = std::make_shared<AccessThing>();
    return thing;
}


int main()
{
    auto thing = make_thing();
    return 0;
}
