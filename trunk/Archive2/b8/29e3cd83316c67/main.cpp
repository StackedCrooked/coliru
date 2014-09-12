#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <chrono>
#include <ostream>
#include <iomanip>

namespace std { namespace chrono {
    template<typename C, typename D>
    std::ostream& operator<< (std::ostream& stream, std::chrono::time_point<C, D> const& tp)
    {
        auto timet = std::chrono::system_clock::to_time_t(tp);
        stream << std::put_time(timet);
        return ostream;
    }
}}

int main()
{
    typedef std::chrono::duration<unsigned, std::ratio<86400>> duration_days;
    
    auto today = std::chrono::system_clock::now();
    auto nintyDaysAgo = today - duration_days{90};
    std::cout << nintyDaysAgo << std::endl;
}
