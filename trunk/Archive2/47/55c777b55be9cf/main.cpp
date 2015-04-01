#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <cstdint>
#include <memory>
#include <cassert>

struct Component {
};

enum ComponentType
{
    POSITION = 0,
    VELOCITY = 1
};

namespace std
{
    template <>
    struct hash<ComponentType> {
        size_t operator()(ComponentType type) const noexcept
        {
            return static_cast<size_t>(type);
        }
    };
}

struct Position : public Component {
    float x;
    Position(float x):x(x) {}
    static const ComponentType type;
};
const ComponentType Position::type = POSITION;


struct Velocity : public Component {
    float x;
    Velocity(float x):x(x) {}
    static const ComponentType type;
};
const ComponentType Velocity::type = VELOCITY;

struct Entity
{
    private:
    std::unordered_map<ComponentType, std::unique_ptr<Component>> components;
    
    public:
    template <typename T>
    T& get() {
        return *static_cast<T*>(components.at(T::type).get());
    }
    
    template <typename T>
    bool has() {
        return components.find(T::type) != components.end();
    }
    
    template <typename T, typename... Args>
    void add(Args... args) {
        assert(!has<T>());
        components[T::type].reset(new T(args...));
    }
};

int main() {
    Entity e;
    e.add<Position>(1);
    
    auto& p1 = e.get<Position>();
    std::cout << p1.x << std::endl;
    
    std::cout << e.has<Velocity>() << std::endl;
    
    auto& p2 = e.get<Velocity>();
    std::cout << p2.x << std::endl;
}
