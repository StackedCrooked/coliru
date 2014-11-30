#include <iostream>
#include <functional>
#include <chrono>

// typedef for a point in time (see Item 9 for syntax)
using Time = std::chrono::time_point<std::chrono::steady_clock >;
// see Item 10 for "enum class"
enum class Sound { Beep, Siren, Whistle };
// typedef for a length of time
using Duration = std::chrono::steady_clock::duration;
// at time t, make sound s for duration d
void setAlarm(Time t, Sound s, Duration d)
{
  std::cout << "Setting Alarm\n";
}


using namespace std::chrono;           // as above
using namespace std::placeholders;     // needed for use of "_1" 

auto setSoundB3 =
  std::bind(setAlarm,
            std::bind(std::plus<steady_clock::time_point>(),
                      steady_clock::now(),
                      hours(1)),
            _1,
            seconds(30));


int main()
{
}
