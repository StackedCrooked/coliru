
#include <iostream>
#include <type_traits>

struct FrameworkTag final {};
struct GraphicsTag final {};

struct CoolBroEvent {};
struct BasicEvent {};

template< typename T >
struct System {

  template< typename Event >
  void HandleEvent( Event && e );

  static System& get();
};

template<>
struct System<FrameworkTag> final {

  template< typename Event >
  void HandleEvent( Event && e );

  static System& get() {
    static System s;
    return s;
  }
};

template<>
struct System<GraphicsTag> final {

  template< typename Event >
  void HandleEvent( Event && e );

  static System& get() {
    static System s;
    return s;
  }
};

namespace detail {
  template <typename T, typename E> 
  auto constexpr can_handle_event( int&& ) -> decltype( T::template HandleEvent<E>, bool{}) { return true; }

  template <typename T, typename E> 
  auto constexpr cannot_handle_event( int&& ) -> decltype(T::template HandleEvent<E>, bool{}) { return false; }

  template <typename T, typename E> 
  auto constexpr can_handle_event( ... ) -> bool { return false; }

  template <typename T, typename E> 
  auto constexpr cannot_handle_event( ... ) -> bool { return true; }
}

template< typename T, typename E>
auto constexpr can_handle_event() -> bool { return detail::can_handle_event<T,E>(0); }

template< typename T, typename E>
auto constexpr cannot_handle_event() -> bool { return detail::cannot_handle_event<T,E>(0); }

template< typename ... Systems >
struct EventDispatcher {

public:
  template< typename Event >
  void DispatchDirect( Event && e ) {
    DispatchDirect_Impl<Event, Systems ... >( std::forward<Event>( e ) );
  }
private:
  template< typename Event  >
  void 
  DispatchDirect_Impl( Event && ) {
  }

  template< typename Event, typename S, typename ... Ss >
  typename std::enable_if< can_handle_event<System<S>, Event>(), void >::type
  DispatchDirect_Impl( Event && e ) {
    System<S>::get(). template HandleEvent<Event>( std::forward<Event>( e ) );
    DispatchDirect_Impl< Event, Ss ...  >( std::forward<Event>( e ) );
  }

  template< typename Event, typename S, typename ... Ss >
  typename std::enable_if< cannot_handle_event<System<S>, Event>(), void >::type
  DispatchDirect_Impl( Event && e ) {
    DispatchDirect_Impl< Event, Ss ...  >( std::forward<Event>( e ) );
  }
};

auto dispatcher = EventDispatcher<GraphicsTag, FrameworkTag > {};

template<>
void System<FrameworkTag>::HandleEvent<BasicEvent>( BasicEvent&& e ) {
  std::cout << "Frameworks + BasicEvent" << std::endl;
  dispatcher.DispatchDirect( CoolBroEvent() );
}

template<>
void System<GraphicsTag>::HandleEvent<BasicEvent>( BasicEvent&& e ) {
  std::cout << "Graphics + BasicEvent" << std::endl;
}

template<>
void System<GraphicsTag>::HandleEvent<CoolBroEvent>( CoolBroEvent&& e ) {
  std::cout << "Graphics + CoolBroEvent" << std::endl;
}

int main( void ) {
  dispatcher.DispatchDirect( BasicEvent() );
  return 0;
}