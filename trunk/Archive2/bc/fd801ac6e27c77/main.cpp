#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> items { 1,2,3,4,5,6,7,8 };

template<typename Runnable>
void for_all_active_things(Runnable && func)
{
    std::for_each(items.begin(), items.end(),
                  [&func](decltype(items)::value_type & item)
                  {
                      if ( item % 2 == 0) // some condition that determines "active"
                          func(item);
                  });
    
}

int main(void)
{
    //                 vvvv can I avoid this decltype?
    for_all_things([](decltype(items)::value_type & t) 
                      { 
                          std::cout << t << std::endl; 
                      });
}