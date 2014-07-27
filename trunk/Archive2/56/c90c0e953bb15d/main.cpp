#include <iostream>
#include <istream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

template<class Iterator, class IteratorId>
Iterator remove_at_indexes(Iterator first, Iterator last, IteratorId indexes_begin, IteratorId indexes_end)
{
    sort(indexes_begin, indexes_end, less<size_t>());
    
    size_t count { 0 };
    
    if (first != last)
        for(auto i = first; i != last; i++)
            if(indexes_begin == indexes_end)
               first++;
            else
            {
                if (count != *indexes_begin)
                    *first++ = std::move(*i);
                else
                    indexes_begin++;
                count++;
            }

    return first;
}

int main() 
{
  vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
  vector<size_t> indexes { 4, 1, 9 };
  
  v.erase(remove_at_indexes(v.begin(), v.end(), indexes.begin(), indexes.end()), v.end());
  
  for(auto val : v)
    cout << val << " ";
  
  return 0;
}