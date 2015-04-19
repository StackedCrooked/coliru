#include <iostream>
#include <typeinfo>

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

// used member function
template <TimeUnit unit = Seconds, typename T = decltype(m_seconds)>
T getTime()
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
    if(typeid(getTime<Milliseconds>()) == typeid(MILLISECONDS_DTYPE))
        std::cout << "ms data type matches" << std::endl;
    if(typeid(getTime<Seconds>()) == typeid(SECONDS_DTYPE))
        std::cout << "seconds data type matches" << std::endl;
    if(typeid(getTime<Minutes>()) == typeid(MINUTES_DTYPE))
        std::cout << "minutes data type matches" << std::endl;    
    if(typeid(getTime<Hours>()) == typeid(HOURS_DTYPE))
        std::cout << "hour data type matches" << std::endl;
    if(typeid(getTime<Days>()) == typeid(DAYS_DTYPE))
        std::cout << "days data type matches" << std::endl;

   return 0;
}