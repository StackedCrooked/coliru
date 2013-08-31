//#include "windows.h"
typedef int DWORD;
typedef long LONG;
typedef long long LONGLONG;
typedef union _LARGE_INTEGER {
//  struct {
//    DWORD LowPart;
//    LONG  HighPart;
//  };
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
bool QueryPerformanceCounter(LARGE_INTEGER *){return true;}
bool QueryPerformanceFrequency(LARGE_INTEGER *){return true;}





#include <chrono>

class win_highdef_clock {
private:
    static LONGLONG initial_frequency() {
        LARGE_INTEGER f={};
        QueryPerformanceFrequency(&f);
        return f.QuadPart;
    }
    static const LONGLONG nano = 1000000000;
public:
    static const LONGLONG& get_freq() {        
        static const LONGLONG frequency = initial_frequency();
        return frequency;
    }
    
    typedef LONGLONG rep;
    typedef std::ratio<1, nano> period;
    typedef std::chrono::duration<rep, period> duration;
    typedef std::chrono::time_point<win_highdef_clock, duration> time_point;
    static const bool is_monotonic = true;
    static const bool is_steady = false;

    static time_point from_time_t(time_t t) noexcept(true);
    static time_t to_time_t(time_point t) noexcept(true);
    static time_point now() noexcept(true) {
        LARGE_INTEGER n={};
        QueryPerformanceCounter(&n);
        if (get_freq()!=nano)
            n.QuadPart = n.QuadPart*(get_freq()/nano);
        return time_point(duration(n.QuadPart));
    }
};

#include <iostream>
int main() {
    auto t = win_highdef_clock::now();
    std::cout << win_highdef_clock::get_freq();
}
