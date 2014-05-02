#include <map>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <memory>
#include <stdexcept>

struct component {
    virtual ~component() = default;
};

template<typename T>
constexpr bool is_component() noexcept {
    static_assert(std::is_base_of<component, T>::value, "Type must be a component");
    return true;
}

template<typename... Args>
constexpr bool are_components() {
    using swallow = bool[];
    return (void(swallow{ (is_component<Args>(), true)... }), true);
}

struct entity {
private:
    std::map<std::type_index, std::unique_ptr<component>> components;

    template<typename T>
    bool has_impl() const {
        is_component<T>();
        return components.count(std::type_index(typeid(T)));
    }

    template<typename T, typename... Args>
    typename std::enable_if<(sizeof...(Args) >= 1), bool>::type has_impl() const {
        return has_impl<T>() && has_impl<Args...>();
    }

    template<typename T>
    void remove_impl() {
        is_component<T>();
        components.erase(std::type_index(typeid(T)));
    }

    template<typename T, typename... Args>
    typename std::enable_if<(sizeof...(Args) >= 1)>::type remove_impl() {
        remove_impl<T>();
        remove_impl<Args...>();
    }

public:
    entity() = default;

    template<typename T>
    T* get() const {
        is_component<T>();
        auto it = components.find(std::type_index(typeid(T)));

        if(it == components.end()) {
            return nullptr;
        }

        return dynamic_cast<T*>(it->second.get());
    }

    template<typename T, typename... Args>
    void emplace(Args&&... args) {
        is_component<T>();
        std::unique_ptr<component> c{ new T(std::forward<Args>(args)...) };
        components.emplace(std::type_index(typeid(T)), std::move(c));
    }

    template<typename... Args>
    bool has() const {
        return has_impl<Args...>();
    }

    template<typename... Args>
    void remove() {
        return remove_impl<Args...>();
    }
};

template<typename... Args>
struct component_system {
private:
    static const bool assertion = are_components<Args...>();
public:
    constexpr component_system() = default;
    virtual void update(entity& e) = 0;

    void process(entity& e) {
        if(e.has<Args...>()) {
            update(e);
        }
    }
};

#include <iostream>

struct position_component : public component {
    int x;
    int y;
    position_component(int x, int y): x(x), y(y) {}
};

struct health_component : public component {
    int hp;
    health_component(int hp): hp(hp) {}
};

struct dummy_system : public component_system<health_component, position_component> {
    void update(entity& e) {
        auto position = e.get<position_component>();
        auto health = e.get<health_component>();
        position->x *= 2;
        position->y *= 4;
        health->hp -= 1;
    }
};

void print(entity& e) {
    auto position = e.get<position_component>();
    auto health = e.get<health_component>();
    std::cout << "position: (" << position->x << ", " << position->y << ")\nhealth: " << health->hp << '\n'; 
}

int main() {
    entity e;
    e.emplace<position_component>(10, 20);
    e.emplace<health_component>(5);

    dummy_system sys;
    print(e);
    sys.process(e);
    print(e);
}