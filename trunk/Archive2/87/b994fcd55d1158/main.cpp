#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <chrono>
#include <iomanip>

template<typename C, typename D>
std::ostream& operator<< (std::ostream& s, std::chrono::time_point<C, D> const& tp)
{
    auto tt = std::chrono::system_clock::to_time_t(tp);
    s << std::ctime(&tt);
    return s;
}

int main()
{
    typedef std::chrono::duration<unsigned, std::ratio<86400>> duration_days;
    
    auto today = std::chrono::system_clock::now();
    auto nintyDaysAgo = today - duration_days{90};
    std::cout << "Today: " << today << ", Ninty days ago: " << nintyDaysAgo << std::endl;
}
