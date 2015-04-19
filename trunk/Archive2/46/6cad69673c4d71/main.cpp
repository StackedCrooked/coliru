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

// used member function

    
int main()
{
    if(getTime<Milliseconds>() == 5)
        std::cout << "it works!" << std::endl;

   return 0;
}