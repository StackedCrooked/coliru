#include <typeinfo>
#include <iostream>
#include <vector>

struct Component { virtual ~Component() = default; };
struct Foo : Component {};
struct Bar : Component {};

struct Entity {
    template<class T> T* getComponent();
    std::vector<Component*> mComponents;
};

template <class T>
T* Entity::getComponent()
{
    for( auto i = mComponents.begin(); i != mComponents.end(); i++ )
    {
        if( typeid(**i) == typeid(T) )
        {
            return static_cast<T*>(*i);
        }
    }

    return nullptr;
}

int main() {
    Entity test { {new Foo(), new Bar() } };
    std::cout << test.getComponent<Foo>() << std::endl;
}