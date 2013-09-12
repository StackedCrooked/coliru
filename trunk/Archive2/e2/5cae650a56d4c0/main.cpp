//#include <chrono>
#include <string>
#include <deque>
#include <algorithm>

using Timepoint = unsigned; // std::chrono::system_clock::time_point;
struct Interval { Timepoint start, end; };
using Data      = std::string;
using Entry     = std::pair<Interval, Data>;
using Schedule  = std::deque<Entry>;

#include <iostream>
int main()
{
    Schedule schedule { 
        { { 77472, 77504 }, "A" },
        { { 77301, 77371 }, "B" },
        { { 77406, 77439 }, "C" },
        { { 77270, 77303 }, "D" },
        { { 77302, 77570 }, "E" },
    };
    
    std::sort(begin(schedule), end(schedule), [](Entry const& a, Entry const& b) { return a.first.end < b.first.end; });

    // now, iterate the schedule entries, skipping overlapping items
    for(auto it = begin(schedule); it != end(schedule); )
    {
        auto const& entry = *it;
        std::cout << "entry: " << entry.second << " from " << entry.first.start << " to " << entry.first.end << "\n";
        while (++it != end(schedule))
                if (it->first.start > entry.first.end)
                    break;
    }
}
