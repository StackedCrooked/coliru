#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using std::vector;
using std::pair;
using std::make_pair;

typedef pair<int, int> interval;



struct interval_container
{
    void add(int start, int len)
    {
        _data.emplace_back( make_pair(start, len) );
    }
    
    void consolidate()
    {
        // sort intervals first by start then by length
        std::sort(_data.begin(), _data.end());
        
        // create temp data
        vector<interval> consolidated;
        
        // iterate over all sorted intervals
        for(const interval& i : _data)
        {
            int start = i.first;
            int len = i.second;
            
            // special case: first interval
            if (consolidated.empty())
            {
                consolidated.emplace_back(i);
            }
            // all other cases
            else
            {
                // get last interval in the consolidated array
                interval& last = consolidated.back();
                int& last_start = last.first;
                int& last_len = last.second;
                
                
                // if the current interval can be merged with the last one
                if ((start >= last_start) and (start < (last_start + last_len)))
                {
                    // merge the interval with the last one
                    last_len = std::max(last_len, (start + len - last_start));
                }
                // if the current interval can't be merged with the last one
                else
                {
                    consolidated.emplace_back(i);
                }
            }
        }
        
        // copy consolidated data
        _data = consolidated;
    }
    
    
    vector<interval>& data() { return _data; }
    
private:
    vector<interval> _data;
};


int main()
{
    interval_container intervals;
    
    intervals.add(0, 2);
    intervals.add(1, 3);
    intervals.add(5, 3);
    
    intervals.consolidate();
    
    int c(0);
    for(interval i : intervals.data())
    {
        std::cout << (c++) << ": from " << i.first << " to " << (i.first + i.second) << std::endl;
    }
}