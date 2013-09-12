//#include <chrono>
#include <string>
#include <deque>
#include <algorithm>

using Timepoint = unsigned; // std::chrono::system_clock::time_point;
struct Entry {
    Timepoint start, end;
    std::string data;
};

#include <iostream>
int main()
{
    std::deque<Entry> schedule { 
        {  77472, 77504, "A" },
        {  77301, 77371, "B" },
        {  77406, 77439, "C" },
        {  77270, 77303, "D" },
        {  77302, 77570, "E" },
    };
    
    // order by end time_point
    std::sort(begin(schedule), end(schedule), [](Entry const& a, Entry const& b) { return a.end < b.end; });

    // now, iterate the schedule entries, skipping overlapping items
    for(auto it = begin(schedule); it != end(schedule); )
    {
        auto const& entry = *it;
        std::cout << "entry: " << entry.data << " from " << entry.start << " to " << entry.end << "\n";
        while (++it != end(schedule))
                if (it->start > entry.end)
                    break;
    }
}
