#include <iostream>
#include <type_traits>
#include <iostream>

template <typename T, int N, typename... Mixins> 
struct get_index
{
    static constexpr int value = -1;
};

template <typename T, int N, typename... Mixins>
struct get_index<T, N, T, Mixins...>
{
    static constexpr int value = N;
};

template <typename T, int N, typename U, typename... Mixins>
struct get_index<T, N, U, Mixins...>
{
    static constexpr int value = get_index<T, N + 1, Mixins...>::value;
};

class ComponentBase {
public:
    virtual void update () = 0;
};

template <class T>
class Component : public ComponentBase {
public:
    virtual void update () {
        static_cast<T*>(this)->update();
    }
};

class TransformComponent : public Component<TransformComponent> {
public:
    void update () {
        std::cout << "TransformComponent" << std::endl;
    }
protected:
    int _x, _y;
};

class ColliderComponent : public Component<ColliderComponent> {
public:
    void update () {
        std::cout << "ColliderComponent" << std::endl;
    }    
protected:
    bool _collided;
};

template <typename... Mixins>
class GameObject
{
public:
    GameObject(Mixins&... mixins) : _components{&mixins...} {}
    GameObject(Mixins&&... mixins) : _components{&mixins...} {}

    constexpr size_t getNumComponents () const { return _numComponents; };
    
    template <typename T>
    constexpr int getIndex() const {
        return get_index<T, 0, Mixins...>::value;
    }
    
    template <typename T>
    constexpr T* getComponent() const {
        if (getIndex<T>() != -1)
            return static_cast<T*>(_components[getIndex<T>()]);
        else
            return nullptr;
    }

    void update () {
        for (size_t i = 0; i < getNumComponents(); ++i) {
            _components[i]->update();
        }
    }

protected:
    static const size_t _numComponents = sizeof...(Mixins);
    ComponentBase* _components[sizeof...(Mixins)];
};

int main()
{
    ColliderComponent c{};
    TransformComponent t{};
    
    GameObject<ColliderComponent, TransformComponent> b{ c, t };
    
    b.getComponent<ColliderComponent>()->update();
    b.getComponent<TransformComponent>()->update();
}
