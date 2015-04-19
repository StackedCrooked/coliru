#include <iostream>
#include <typeinfo>

namespace details {
    template<class T>
    struct get_member_type;    
    template<class T, class R>
    struct get_member_type<R T::*> { using type = R; };
}

template<class T>
using get_member_type = typename details::get_member_type<typename std::remove_cv<T>::type>::type;

struct Foo {
    enum TimeUnit { Milliseconds, Seconds, Minutes, Hours, Days };

    template<TimeUnit time>
    struct TimeUnitImpl;

    template <TimeUnit unit = Seconds>
    typename TimeUnitImpl<unit>::type getTime()
    {
        return this->*TimeUnitImpl<unit>::p_mem;
    }

    typedef unsigned char u_char;
    typedef unsigned short u_short;
    typedef unsigned long long u_ll;
    typedef u_ll DAYS_DTYPE;
    typedef u_char HOURS_DTYPE;
    typedef u_char MINUTES_DTYPE;
    typedef u_char SECONDS_DTYPE;
    typedef u_short MILLISECONDS_DTYPE;
    
    // used class members; max. values are handled class-internal
    DAYS_DTYPE          m_days = 1;         // max.: 18.446.744.073.709.551.615
    HOURS_DTYPE         m_hours = 2;        // max.: 23
    MINUTES_DTYPE       m_minutes = 3;      // max.: 59
    SECONDS_DTYPE       m_seconds = 4;      // max.: 59
    MILLISECONDS_DTYPE  m_milliseconds = 5; // max.: 999
};

template<Foo::TimeUnit time>
struct Foo::TimeUnitImpl
{ 
  static constexpr auto p_mem = &Foo::m_milliseconds;
  using type = get_member_type<decltype(p_mem)>;
};

template<>
struct Foo::TimeUnitImpl<Foo::Seconds>
{
  static constexpr auto p_mem = &Foo::m_seconds;
  using type = get_member_type<decltype(p_mem)>;
};

template<>
struct Foo::TimeUnitImpl<Foo::Minutes>
{ 
  static constexpr auto p_mem = &Foo::m_minutes;
  using type = get_member_type<decltype(p_mem)>; 
};

template<>
struct Foo::TimeUnitImpl<Foo::Hours>
{ 
  static constexpr auto p_mem = &Foo::m_hours;
  using type = get_member_type<decltype(p_mem)>;
};

template<>
struct Foo::TimeUnitImpl<Foo::Days>
{ 
  static constexpr auto p_mem = &Foo::m_days;
  using type = get_member_type<decltype(p_mem)>;
};


int main()
{
    Foo f;
    
    return f.getTime<Foo::Days>();
}