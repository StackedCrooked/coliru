#include <algorithm>
#include <iostream>
#include <vector>

struct Data {
    Data(int value) : value_(value) {}
    int value_;
};

struct CompareData {
    bool operator()(const Data& lhs, const Data& rhs) const {
      return lhs.value_ > rhs.value_;
      };
};
 
int main()
{
  std::vector<int> v;
  v.emplace_back(5);
  v.emplace_back(4);
  v.emplace_back(2);
  v.emplace_back(8);
  v.emplace_back(1);
  
  // Sort decending using a lamdda.
  std::sort(v.begin(), v.end(), [](const Data& lhs, const Data& rhs) {
      return lhs.value_ > rhs.value_;
      });
      
  // Using a comparator class.    
  CompareData comparator;
  std::sort(v.begin(), v.end(), comparator);
  
  
  for (const Data& data : v) {
      std::cout << data.value_ << std::endl;
  }
}