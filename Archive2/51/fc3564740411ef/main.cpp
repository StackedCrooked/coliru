#include <iostream>

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

enum TimeUnit { Milliseconds, Seconds, Minutes, Hours, Days };

template<TimeUnit time>
struct TimeUnitImpl
{ using type = decltype(m_milliseconds); };

template<>
struct TimeUnitImpl<Seconds>
{ using type = decltype(m_seconds); };

template<>
struct TimeUnitImpl<Minutes>
{ using type = decltype(m_minutes); };

template<>
struct TimeUnitImpl<Hours>
{ using type = decltype(m_hours); };

template<>
struct TimeUnitImpl<Days>
{ using type = decltype(m_days); };

// used member function
template <TimeUnit unit = Seconds>
typename TimeUnitImpl<unit>::type getTime()
{
    switch (unit)
    {
    case Milliseconds: return m_milliseconds;
    case Seconds: return m_seconds;
    case Minutes: return m_minutes;
    case Hours: return m_hours;
    case Days: return m_days;
    default:
        break;
    }
}
    
int main()
{
    if(std::is_same<decltype(getTime<Milliseconds>()), MILLISECONDS_DTYPE>::value)
        std::cout << "it works!" << std::endl;

   return 0;
}