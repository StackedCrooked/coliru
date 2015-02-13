#include <iostream>
#include <type_traits>
#include <tuple>

struct FrameworkTag final {};
struct GraphicsTag final {};
struct FactoryTag final {};

struct CoolBroEvent {};
struct BasicEvent {};
struct FactoryEvent {};

namespace detail {
  template< typename T >
  struct event_traits {
    //static constexpr char const * const name {"undefined"};
  };
  template <>
  struct event_traits<CoolBroEvent> {
    static constexpr char const * const name {"CoolBroEvent"};
  };
  template<>
  struct event_traits<BasicEvent> {
    static constexpr char const * const name {"BasicEvent"};
  };
  template<>
  struct event_traits<FactoryEvent> {
    static constexpr char const * const name {"FactoryEvent"};
  };
}

// Borrowed from cdacamara on stackoverflow.com
// http://stackoverflow.com/a/26288164

namespace detail {
    struct null { };
}

template <typename T, typename Tuple>
struct tuple_contains;

template <typename T, typename... Ts>
struct tuple_contains<T, std::tuple<Ts...>> :
  std::conditional<
    std::is_same<
      std::tuple<typename std::conditional<std::is_same<T, Ts>::value, detail::null, Ts>::type...>,
      std::tuple<Ts...>
    >::value,
    std::false_type,
    std::true_type
  >::type
{ };

template< typename Tag, typename ... Handled >
struct System {
  typedef std::tuple< Handled ... > MyEvents;

  template< typename Event >
  void HandleEvent( Event && e ) {
    static_assert(!tuple_contains< Event, MyEvents >::value, "Should only be called for events you explicitly handle");
  }

  static System& get() {
    static System s;
    return s;
  }
};

namespace detail {
  template< typename T >
  struct system_traits {
    //static constexpr char const * const name {"undefined"};
  };
}

template< typename ... Systems >
struct EventDispatcher {

public:
  template< typename Event >
  void DispatchDirect( Event && e ) {
    //std::cout << "started handling " << detail::event_traits<Event>::name << std::endl;
    DispatchDirect_Impl<Event, Systems ... >( std::forward<Event>( e ) );
  }
private:
  template< typename Event  >
  void 
  DispatchDirect_Impl( Event && ) {
    //std::cout << "finished handling " << detail::event_traits<Event>::name << std::endl;
  }

  template< typename Event, typename S, typename ... Ss >
  typename std::enable_if< tuple_contains< Event, typename S::MyEvents >::value, void >::type
  DispatchDirect_Impl( Event && e ) {
    //std::cout << detail::system_traits<S>::name << " started handling " << detail::event_traits<Event>::name << std::endl;
    S::get(). template HandleEvent<Event>( std::forward<Event>( e ) );
    DispatchDirect_Impl< Event, Ss ...  >( std::forward<Event>( e ) );
  }

  template< typename Event, typename S, typename ... Ss >
  typename std::enable_if< !tuple_contains< Event, typename S::MyEvents >::value, void >::type
  DispatchDirect_Impl( Event && e ) {
    //std::cout << detail::system_traits<S>::name << " couldn't handle " << detail::event_traits<Event>::name << std::endl;
    DispatchDirect_Impl< Event, Ss ...  >( std::forward<Event>( e ) );
  }
};


using GraphicsSystem = 
  System
  < 
    GraphicsTag, 
      BasicEvent, 
      CoolBroEvent
  >;

using FrameworkSystem = 
  System
  <
    FrameworkTag, 
      BasicEvent
  >;


using FactorySystem = 
  System
  <
    FrameworkTag, 
      BasicEvent,
      FactoryEvent,
      CoolBroEvent
  >;


namespace detail {
  template <>
  struct system_traits<GraphicsSystem> {
    static constexpr char const * const name {"GraphicsSystem"};
  };
  template<>
  struct system_traits<FrameworkSystem> {
    static constexpr char const * const name {"FrameworkSystem"};
  };
}

auto dispatcher = EventDispatcher< GraphicsSystem, FrameworkSystem, FactorySystem > {};

template <> template <>
void FrameworkSystem::HandleEvent<BasicEvent>( BasicEvent&& e ) {
  std::cout << "Frameworks + BasicEvent" << std::endl;
  dispatcher.DispatchDirect( CoolBroEvent() );
}

template <> template <>
void GraphicsSystem::HandleEvent<BasicEvent>( BasicEvent&& e ) {
  std::cout << "Graphics + BasicEvent" << std::endl;
}

template <> template <>
void GraphicsSystem::HandleEvent<CoolBroEvent>( CoolBroEvent&& e ) {
  std::cout << "Graphics + CoolBroEvent" << std::endl;
}

template <> template <> 
void FactorySystem::HandleEvent<BasicEvent>( BasicEvent&& e ) {
  std::cout << "Factory + BasicEvent" << std::endl;
  dispatcher.DispatchDirect( FactoryEvent() );
}

template <> template <>
void FactorySystem::HandleEvent<CoolBroEvent>( CoolBroEvent&& e ) {
  std::cout << "Factory + CoolBroEvent" << std::endl;
}

template <> template <>
void FactorySystem::HandleEvent<FactoryEvent>( FactoryEvent&& e ) {
  std::cout << "Factory + FactoryEvent" << std::endl;
  dispatcher.DispatchDirect( CoolBroEvent() );
}



int main( void ) {
  dispatcher.DispatchDirect( BasicEvent() );
  return 0;
}