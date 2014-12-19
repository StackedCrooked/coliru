#include <algorithm>
#include <iostream>
#include <string>

template<typename InputIterator, typename OutputIterator>
void zip(InputIterator begin1, InputIterator end1,
         InputIterator begin2, InputIterator end2,
         OutputIterator out)
{
  auto it1 = begin1;
  auto it2 = begin2;
  for(; it1 != end1 && it2 != end2; ++it1, ++it2)
  {
    out = *it1;
    out = *it2;
  }
  // copy remaining elements from both ranges
  while(it1 != end1)
  {
    out = *it1;
    ++it1;
  }
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
  std::string result1;
  std::string result2;
  
  zip(std::begin(s1), std::end(s1),
      std::begin(s2), std::end(s2),
      std::back_inserter(result1));

  zip(std::begin(s2), std::end(s2),
      std::begin(s1), std::end(s1),
      std::back_inserter(result2));

  std::cout << result1 << '\n' << result2 << '\n';
}