#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> v{1,2,3,4,5,6};
    
  unsigned index = 0;   // this is the index variable used to remove elements
  auto end = v.end();   // point to the current end of the vector

  // keep looping until there is only 1 element in the vector
  while(std::distance(v.begin(), end) > 1) {
    // remove_if will call the predicate for each element
    // the predicate simply increments the index each time, and when it reaches 
    // 3 indicates that element should be removed
    // remove_if will move items to the end of the vector and return an 
    // iterator to the end of the new range, so we'll update the end variable 
    // with the result
    end = std::remove_if(v.begin(), end, [&index](int) {
      if(++index == 3) {
        // reset the index and indicate this element should be removed
        return (index = 0), true;
      }
      return false;
    });
    
    for(auto iter = v.begin(); iter != end; ++iter) {
      std::cout << *iter << ' ';
    }
    std::cout << '\n';
  }

  // erase all the elements we've removed so far
  v.erase(end, v.end());
}