#include <chrono>
#include <iosfwd>


namespace stuff {


typedef std::chrono::high_resolution_clock Clock;


typedef std::chrono::nanoseconds Nanoseconds;
typedef std::chrono::microseconds Microseconds;
typedef std::chrono::milliseconds Milliseconds;
typedef std::chrono::seconds Seconds;
typedef std::chrono::minutes Minutes;
typedef std::chrono::hours Hours;


std::ostream& operator<<(std::ostream&, nanoseconds);
std::ostream& operator<<(std::ostream&, microseconds);
std::ostream& operator<<(std::ostream&, milliseconds);
std::ostream& operator<<(std::ostream&, seconds);
std::ostream& operator<<(std::ostream&, minutes);
std::ostream& operator<<(std::ostream&, hours);


} // stuff
