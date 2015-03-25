#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <chrono>

using namespace std;

template<typename C>
auto mean(C&& data)
{
    return std::accumulate(begin(data), end(data), 0) / data.size(); 
}

template<typename T> struct time_type                  { constexpr static char *name = "unknown";      };
template<> struct time_type<std::chrono::nanoseconds > { constexpr static char *name = "nanoseconds";  };
template<> struct time_type<std::chrono::microseconds> { constexpr static char *name = "microseconds"; };
template<> struct time_type<std::chrono::milliseconds> { constexpr static char *name = "milliseconds"; };
template<> struct time_type<std::chrono::seconds     > { constexpr static char *name = "seconds";      };
template<> struct time_type<std::chrono::minutes     > { constexpr static char *name = "minutes";      };
template<> struct time_type<std::chrono::hours       > { constexpr static char *name = "hours";        };


int main()
{
    std::vector<double> v{ 1, 2, 1, 2, 1, 2 }; 
    std::cout << "mean val = " << mean(v) << std::endl; 
    
    std::cout << time_type<std::chrono::nanoseconds>::name << std::endl;
}
