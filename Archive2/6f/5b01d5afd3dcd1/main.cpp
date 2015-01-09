#include <iostream>
#include <chrono>
#include <functional>

// typedef for a point in time (see Item 9 for syntax)
using Time = std::chrono::steady_clock::time_point;
// see Item 10 for "enum class"
enum class Sound { Beep, Siren, Whistle };
// typedef for a length of time
using Duration = std::chrono::steady_clock::duration;
// at time t, make sound s for duration d

struct MockClock
{
    static Time now()
    {
        return _t;
    }

    static void ellapse(Duration d)
    {
        _t += d;
    }

    static Time _t;
};

Time MockClock::_t;

Time startTime;

void setAlarm(Time t, Sound /*s*/, Duration /*d*/)
{
    std::cout << "fired after " << std::chrono::duration_cast<std::chrono::hours>(t - startTime).count() << " hours\n";
}

int main()
{
    using namespace std::chrono; // as above
    using namespace std::literals;
    using namespace std::placeholders; // needed for use of "_1"

    auto setSoundL =
      [](Sound s)
      {
          using namespace std::chrono;
          using namespace std::literals; // for C++14 suffixes
          setAlarm(MockClock::now() + 1h, // C++14, but
            s, // same meaning
            30s); // as above
      };

    auto setSoundB =
      std::bind(setAlarm,
        std::bind(std::plus<>(), MockClock::now(), 1h),
        _1,
        30s);

    auto setSoundB_Corrected =
      std::bind(setAlarm,
        std::bind(std::plus<>(), std::bind(MockClock::now), 1h),
        _1,
        30s);


    // 1 hour past...
    MockClock::ellapse(1h);

    startTime = MockClock::now();

    std::cout << "setSoundL:\n";
    setSoundL(Sound::Beep);
    std::cout << "setSoundB:\n";
    setSoundB(Sound::Beep);
    std::cout << "setSoundB_Corrected:\n";
    setSoundB_Corrected(Sound::Beep);

    return EXIT_SUCCESS;
}
