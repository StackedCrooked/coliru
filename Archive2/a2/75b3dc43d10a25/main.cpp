#include <utility>

template <typename...Components>
class Entity : private Components... {
public:
    Entity() = default;
    
    Entity(Components...components) :
        Components(std::move(components))... {}

    template <typename T>
    T& get() {
        return *this;
    }
    template <typename T>
    const T& get() const {
        return *this;
    }
};


#include <iostream>

struct ComponentA { void f() const { std::cout << "I'm a ComponentA\n"; } };
struct ComponentB { void f() const { std::cout << "I'm a ComponentB\n"; } };
struct ComponentC { void f() const { std::cout << "I'm a ComponentC\n"; } };

int main() {
    {
        Entity<ComponentA, ComponentB, ComponentC> e;
        e.get<ComponentC>().f();
        e.get<ComponentB>().f();
        e.get<ComponentA>().f();
    }
    
    {
        ComponentA a;
        Entity<ComponentA, ComponentB> e{a, {}};
    }
    
    {
        // error: duplicate base type
        // Entity<ComponentA, ComponentA> invalid_entity;
    }
}
