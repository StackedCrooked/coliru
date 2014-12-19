#include <algorithm>
#include <iostream>
#include <string>

template<typename InputIterator, typename OutputIterator>
void zip(InputIterator begin1, InputIterator end1,
         InputIterator begin2, InputIterator end2,
         OutputIterator out)
{
  auto it2 = begin2;
  for(auto it1 = begin1; it1 != end1; ++it1)
  {
    out = *it1;
    if(it2 != end2)
    {
      out = *it2;
      ++it2;
    }
  }
  // copy remaining elements from second range
  while(it2 != end2)
  {
    out = *it2;
    ++it2;
  }
}

int main()
{
  const std::string s1 = "John";
  const std::string s2 = "Steven";
  std::string result;
  std::string result2;
  
  zip(std::begin(s1), std::end(s1),
      std::begin(s2), std::end(s2),
      std::back_inserter(result));
      
  zip(std::begin(s2), std::end(s2),
      std::begin(s1), std::end(s1),
      std::back_inserter(result2));

  std::cout << result << '\n' << result2 << '\n';
}