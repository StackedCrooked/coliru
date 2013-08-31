#include "windows.h"
#include <chrono>

class win_highdef_clock {
private:
    static ULONGLONG get_frequency() {
        LARGE_INTEGER f;
        QueryPerformanceCounter(&f);
        return f.QuadPart;
    }
    static ULONGLONG frequency = get_frequency();
public:
    typedef ULONGLONG rep; //one of these is probably wrong
    typedef ULONGLONG period; //one of these is probably wrong
    typedef std::duration<rep, period> duration;
    typedef std::time_point<win_highdef_clock, duration> time_point;
    static const bool is_monotonic = true;
    static const bool is_steady = false;

    win_highdef_clock() : {}
    static time_point from_time_t(time_t t) noexcept(true);
    static time_t to_time_t(time_point t) noexcept(true);
    static time_point now() noexcept(true);
};
