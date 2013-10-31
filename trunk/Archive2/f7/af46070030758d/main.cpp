#include <iostream>
#include <iomanip>
#include <ctime>
 
 #include <ctime>
#include <string>
#include <chrono>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <cassert>
#include <iomanip>
// FYI: 
// namespace g2::internal ONLY in g2time.cpp
//          std::string put_time(const struct tm* tmb, const char* c_time_format)

namespace g2
{
  typedef std::chrono::steady_clock::time_point steady_time_point;
  typedef std::chrono::time_point<std::chrono::system_clock>  system_time_point;
  typedef std::chrono::milliseconds milliseconds;
  typedef std::chrono::microseconds microseconds;

    // This mimics the original "std::put_time(const std::tm* tmb, const charT* fmt)"
    // This is needed since latest version (at time of writing) of gcc4.7 does not implement this library function yet.
    // return value is SIMPLIFIED to only return a std::string

    std::string put_time(const struct tm* tmb, const char* c_time_format) {
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
      std::ostringstream oss;
      oss.fill('0');
      // BOGUS hack done for VS2012: C++11 non-conformant since it SHOULD take a "const struct tm*  "
      oss << std::put_time(const_cast<struct tm*> (tmb), c_time_format);
      return oss.str();
#else    // LINUX
      const size_t size = 1024;
      char buffer[size]; // IMPORTANT: check now and then for when gcc will implement std::put_time. 
      //                    ... also ... This is way more buffer space then we need

      auto success = std::strftime(buffer, size, c_time_format, tmb);
      if (0 == success) 
      {
        assert((0 != success) && "strftime fails with illegal formatting");
        return c_time_format;
      }

      return buffer;
#endif
    }


  std::time_t systemtime_now() {
    system_time_point system_now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(system_now);
  }

  tm localtime(const std::time_t& time) {
    struct tm tm_snapshot;
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) && !defined(__GNUC__))
    localtime_s(&tm_snapshot, &time); // windsows
#else
    localtime_r(&time, &tm_snapshot); // POSIX
#endif
    return tm_snapshot;
  }

  /// returns a std::string with content of time_t as localtime formatted by input format string
  /// * format string must conform to std::put_time
  /// This is similar to std::put_time(std::localtime(std::time_t*), time_format.c_str());

  std::string localtime_formatted(const std::time_t& time_snapshot, const std::string& time_format) {
    std::tm t = localtime(time_snapshot); // could be const, but cannot due to VS2012 is non conformant for C++11's std::put_time (see above)
    std::stringstream buffer;
    buffer << g2::put_time(&t, time_format.c_str()); // format example: //"%Y/%m/%d %H:%M:%S");
    return buffer.str();
  }
} // g2
 
int main()
{
    std::time_t t = std::time(nullptr);
    std::cout << g2::localtime_formatted(t, "%Y/%m/%d %H:%M:%S") << '\n';
}