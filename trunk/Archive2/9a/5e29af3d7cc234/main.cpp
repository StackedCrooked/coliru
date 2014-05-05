#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include <math.h>

using Clock = std::chrono::high_resolution_clock;
using milliseconds = std::chrono::milliseconds;

template<typename T>
T abs_template(T t)
{
  return t>0 ? t : -t;
}

float abs_ugly(float f)
{
  (*reinterpret_cast<std::uint32_t*>(&f)) &= 0x7fffffff;
  return f;
}

int main()
{
  std::random_device rd;
  std::mt19937 mersenne(rd());
  std::uniform_real_distribution<> dist(-std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());

  std::vector<float> v(100000000);

  Clock::time_point t0 = Clock::now();

  std::generate(std::begin(v), std::end(v), [&dist, &mersenne]() { return dist(mersenne); });

  Clock::time_point trand = Clock::now();

  volatile float temp;
  for (float f : v)
    temp = abs_template(f);

  Clock::time_point ttemplate = Clock::now();

  for (float f : v)
    temp = abs_ugly(f);

  Clock::time_point tugly = Clock::now();

  for (float f : v)
    temp = std::abs(f);

  Clock::time_point tstd = Clock::now();

  for (float f : v)
    temp = ::fabsf(f);

  Clock::time_point tfabsf = Clock::now();

  for (float f : v)
    temp = abs_template(f);

  Clock::time_point ttemplate2 = Clock::now();

  for (float f : v)
    temp = abs_template(f);

  Clock::time_point ttemplate3 = Clock::now();

  milliseconds random_time = std::chrono::duration_cast<milliseconds>(trand - t0);
  milliseconds template_time = std::chrono::duration_cast<milliseconds>(ttemplate - trand);
  milliseconds ugly_time = std::chrono::duration_cast<milliseconds>(tugly - ttemplate);
  milliseconds std_time = std::chrono::duration_cast<milliseconds>(tstd - tugly);
  milliseconds c_time = std::chrono::duration_cast<milliseconds>(tfabsf - tstd);
  milliseconds template_time2 = std::chrono::duration_cast<milliseconds>(ttemplate2 - tstd);
  milliseconds template_time3 = std::chrono::duration_cast<milliseconds>(ttemplate3 - ttemplate2);
  std::cout << "random number generation: " << random_time.count() << " ms\n"
    << "naive template abs: " << template_time.count() << " ms\n"
    << "ugly bitfiddling abs: " << ugly_time.count() << " ms\n"
    << "std::abs: " << std_time.count() << " ms\n"
    << "::fabsf: " << c_time.count() << " ms\n"
    << "naive template abs: " << template_time2.count() << " ms\n"
    << "naive template abs: " << template_time3.count() << " ms\n";
}
