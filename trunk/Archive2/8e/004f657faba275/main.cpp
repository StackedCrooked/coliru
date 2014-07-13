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


std::ostream& operator<<(std::ostream&, Nanoseconds);
std::ostream& operator<<(std::ostream&, Microseconds);
std::ostream& operator<<(std::ostream&, Milliseconds);
std::ostream& operator<<(std::ostream&, Seconds);
std::ostream& operator<<(std::ostream&, Minutes);
std::ostream& operator<<(std::ostream&, Hours);


} // stuff
