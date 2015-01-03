#include <vector> // vector
#include <algorithm> // remove
#include <iostream> // cout, endl

class Entity;

class Component {
    Entity* owner;
public:
    Entity* getOwner() { return owner; }
    void setOwner(Entity* o) { owner = o; }
};

template<typename T>
class Interface {
public:
    static std::vector<T*> all;
    Interface() { all.push_back((T*)this); }
    virtual ~Interface() { std::remove(all.begin(), all.end(), (T*)this); }
};
template<typename T> std::vector<T*> Interface<T>::all(0);

class PosInterface : public Interface<PosInterface> {
public:
    virtual float getX() = 0;
};

class TransformComponent : public Component, public PosInterface {
    float x;
public:
    float getX() { return x; }
    TransformComponent(float _x) : x(_x) {}
};

class Entity {
public:
    std::vector<Component*> mComponents;
    Entity& addComponent(Component* c) { mComponents.push_back(c); c->setOwner(this); return *this; }
};

int main()
{
    Entity e;
    TransformComponent t(5);
    e.addComponent(&t);
    for (auto p : PosInterface::all) {
        std::cout << p->getX() << std::endl;
    }
    std::cout << e.mComponents.size() << std::endl;
    return 0;
}
