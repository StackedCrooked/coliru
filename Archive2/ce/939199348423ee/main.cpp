template<typename InIt1, typename InIt2, typename OutIt>
OutIt zip(InIt1 begin1, InIt1 end1,
        InIt2 begin2, InIt2 end2,
        OutIt out)
{
    while(begin1!=end1 || begin2!=end2) {
        if (begin1 != end1) *out++ = *begin1++;
        if (begin2 != end2) *out++ = *begin2++;
    }
    
    return out;
}

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main()
{
  const std::string s1 = "John";
  const std::vector<char> s2 { 'S','t','e','v','e','n' };
  std::string result;
  std::string result2;
  
  zip(begin(s1), end(s1),
      begin(s2), end(s2),
      std::back_inserter(result));
      
  zip(begin(s2), end(s2),
      begin(s1), end(s1),
      std::back_inserter(result2));

  std::cout << result << '\n' << result2 << '\n';
}