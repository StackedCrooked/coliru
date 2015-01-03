#include <vector> // vector
#include <algorithm> // remove
#include <iostream> // cout, endl

class Entity;

// Base class for all components. Stores the owner.
class Component {
    Entity* owner;
public:
    Entity* getOwner() { return owner; }
    void setOwner(Entity* o) { owner = o; }
};

// Entity is a collection of components.
class Entity {
public:
    std::vector<Component*> mComponents;
    Entity& addComponent(Component* c) { mComponents.push_back(c); c->setOwner(this); return *this; }
};

// Base class for all Interfaces, which expose functionality of components.
template<typename T>
class Interface {
public:
    static std::vector<T*> all;
    Interface() { all.push_back((T*)this); }
    virtual ~Interface() { std::remove(all.begin(), all.end(), (T*)this); }
};
template<typename T> std::vector<T*> Interface<T>::all(0);

// This type of interface exposes a position.
class PosInterface : public Interface<PosInterface> {
public:
    virtual float getX() = 0;
};

// A transform component is a component, and can be accessed through the position interface.
class TransformComponent : public Component, public PosInterface {
    float x;
public:
    float getX() {
        std::cout << getOwner()->mComponents.size() << std::endl;
        return x;
    }
    TransformComponent(float _x) : x(_x) {}
};

int main()
{
    Entity e;
    TransformComponent t(5);
    e.addComponent(&t);
    for (auto p : PosInterface::all) {
        std::cout << p->getX() << std::endl;
    }
    return 0;
}
