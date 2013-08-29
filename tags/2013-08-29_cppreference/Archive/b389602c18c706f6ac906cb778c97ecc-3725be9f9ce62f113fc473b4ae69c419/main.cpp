#include <iostream>
#include <memory>

struct Entity;
std::unique_ptr<Entity> p;

struct Entity {
    Entity() { p.reset(this); }
    ~Entity() { std::cout << "destructing\n"; }
};

int main()
{
    Entity e;
}
