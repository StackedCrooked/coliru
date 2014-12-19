#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator zip(InputIterator1 first1, InputIterator1 end1,
                   InputIterator2 first2, InputIterator2 end2,
                   OutputIterator out)
{
  while(first1 != end1 && first2 != end2)
  {
    out = *first1;
    out = *first2;
    ++first1;
    ++first2;
  }
  // copy remaining elements from both ranges
  while(first1 != end1)
  {
    out = *first1;
    ++first1;
  }
  while(first2 != end2)
  {
    out = *first2;
    ++first2;
  }
  return out;
}

int main()
{
  const std::string s1 = "John";
  const std::string s2 = "Steven";
  const std::vector<char> v1 = {'M', 'a', 'r', 'k'};
  std::string result1;
  std::string result2;
  std::string result3;
  
  zip(begin(s1), end(s1),
      begin(s2), end(s2),
      std::back_inserter(result1));
      
  zip(begin(s2), end(s2),
      begin(s1), end(s1),
      std::back_inserter(result2));

  zip(begin(s2), end(s2),
      begin(v1), end(v1),
      std::back_inserter(result3));
      
  std::cout << result1 << '\n' << result2 << '\n' << result3 << '\n';
}