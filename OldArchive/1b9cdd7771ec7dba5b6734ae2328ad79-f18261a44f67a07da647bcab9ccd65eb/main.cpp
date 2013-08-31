#include <chrono>

struct Stopwatch : std::chrono::high_resolution_clock
{
    Stopwatch() : s_(now()) {}

    //! Returns elapsed number of seconds in decimal form.
    double elapsed()
    {
        return 1.0 * (now() - s_).count() / period::den;
    }

private:
     time_point s_;
};
