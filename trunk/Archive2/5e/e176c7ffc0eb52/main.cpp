
#include <iostream>
#include <type_traits>
 
template< typename ... Ts >
void sink( Ts&& ... ) {}
 
struct FrameworkTag final {};
struct GraphicsTag final {};
struct CoolBroEvent {
  std::string bro;
  static std::string name() { return "CoolBroEvent"; }
};
 
struct BasicEvent {  
  static std::string name() {   return "BasicEvent"; }
};
 
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
  static std::string name() {
    return "Framework";
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
  static std::string name() {
    return "Graphics";
  }
};
 
using FrameworkSystem = System<FrameworkTag>;
 
template <typename T, typename E> 
auto constexpr has_handle_event() -> decltype(std::declval<T>().template HandleEvent<E>, bool{}) { return true; }
 
template <typename T, typename E> 
auto constexpr does_not_has_handle_event() -> decltype(std::declval<T>().template HandleEvent<E>, bool{}) { return false; }
 
//template <typename T, typename E> 
//auto constexpr has_handle_event() -> bool { return false; }
// 
//template <typename T, typename E> 
//auto constexpr does_not_has_handle_event() -> bool { return true; }
 
 
template< typename ... Systems >
struct EventDispatcher {
 
public:
  template< typename Event >
  void DispatchDirect( Event && e ) {
    std::cout << "Starting event dispatch: " << Event::name() << std::endl;
    DispatchDirect_Impl<Event, Systems ... >( std::forward<Event>( e ) );
  }
private:
  template< typename Event  >
  void 
  DispatchDirect_Impl( Event && ) {
    std::cout << "Finished handling: " << Event::name() << std::endl;
  }
 
  template< typename Event, typename S, typename ... Syss >
  typename std::enable_if< has_handle_event<System<S>, Event>(), void >::type
  DispatchDirect_Impl( Event && e ) {
    System<S>::get(). template HandleEvent<Event>( std::forward<Event>( e ) );
    DispatchDirect_Impl< Event, Syss ...  >( std::forward<Event>( e ) );
  }
 
  template< typename Event, typename S, typename ... Syss >
  typename std::enable_if< does_not_has_handle_event<System<S>, Event>(), void >::type
  DispatchDirect_Impl( Event && e ) {
    //System<S>::get(). template HandleEvent<Event>( std::forward<Event>( e ) );
    std::cout << System<S>::name() << " Can't handle it, forwarding " << Event::name() << " to others" << std::endl;
    DispatchDirect_Impl< Event, Syss ...  >( std::forward<Event>( e ) );
 
  }
};
 
auto dispatcher = EventDispatcher<GraphicsTag, FrameworkTag > {};
 
 
template<>
void System<FrameworkTag>::HandleEvent<BasicEvent>( BasicEvent&& e ) {
  std::cout << "Framwerkz" << std::endl;
  dispatcher.DispatchDirect<CoolBroEvent>( {} );
 
}
template<>
void System<GraphicsTag>::HandleEvent<BasicEvent>( BasicEvent&& e ) {
  std::cout << "Grapics" << std::endl;
}
 
template<>
void System<GraphicsTag>::HandleEvent<CoolBroEvent>( CoolBroEvent&& e ) {
  std::cout << "Grapics: " << e.bro << std::endl;
}
 
int main( void ) {
  dispatcher.DispatchDirect( BasicEvent() );
  std::cout << "Graphcis handles BroEvent " << has_handle_event<System<GraphicsTag>, CoolBroEvent>() << std::endl;
  std::cout << "Framwerkz handles BroEvent " << has_handle_event<System<FrameworkTag>, CoolBroEvent>() << std::endl;
  std::cout << "Framwerkz handles BasicEvent " << has_handle_event<System<GraphicsTag>, BasicEvent>() << std::endl;
  return 0;
}