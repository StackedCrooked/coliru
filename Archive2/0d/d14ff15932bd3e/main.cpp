#include <boost/chrono/chrono.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <iostream>

namespace chrono = boost::chrono;

int main()
{
  typedef chrono::duration<long int, boost::ratio<1, 5> > TimeSliceDuration;
  typedef chrono::system_clock Clock;
  typedef chrono::time_point<Clock, TimeSliceDuration> TimeSlicePoint;

  Clock clock;
  TimeSlicePoint run_start_time = chrono::time_point_cast<TimeSliceDuration>(clock.now());
  std::cout << run_start_time << '\n';
}
