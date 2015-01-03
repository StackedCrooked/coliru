class ET
{
public:
    template< class Type >
    struct Component {};
};

template<class EntityManager>
class System {
public:
  virtual void Update(EntityManager& entity_manager, double dt) = 0;
protected:
  template<typename T> using Component = typename EntityManager::template Component<T>;
};

template< class EntityManager >
class MovementSystem : public System<EntityManager> {
public:
#ifndef DONTFIXIT
  template< class T > using Component = typename EntityManager::template Component< T >;
#endif

  virtual void Update(EntityManager& entity_manager, double dt) {
    Component<int> position_component; // I'd like to use Component<T> here.
    (void) position_component;
  }
};

auto main() -> int
{
    MovementSystem< ET > ms;
}
