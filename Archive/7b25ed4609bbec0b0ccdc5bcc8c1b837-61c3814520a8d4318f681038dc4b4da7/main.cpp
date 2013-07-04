// Original source: https://gist.github.com/rayfix/5930093

#include <iostream>
#include <vector>

namespace rf {

  template <typename T>
  std::vector<T> merge_sort(const std::vector<T>& input)
  {
    size_t n = input.size();
    if (n <= 1)
      return input;
    
    std::vector<T> output(n);
    auto midpoint = begin(input) + (end(input) - begin(input))/2;
    std::vector<T> left = merge_sort<T>({begin(input), midpoint});
    std::vector<T> right = merge_sort<T>({midpoint, end(input)});
    
    auto c1 = begin(left);
    auto c2 = begin(right);
    auto p = begin(output);
    
    while ( p != end(output) )
    {
      if (*c1 <= *c2)
      {
        *p = *c1;
        ++p;
        if (++c1 == end(left))
          break;
      }
      else
      {
        *p = *c2;
        ++p;
        if (++c2 == end(right))
          break;
      }
    }
    
    while (c1 != end(left))
    {
      *p = *c1;
      ++p;
      ++c1;
    }
    
    while (c2 != end(right))
    {
      *p = *c2;
      ++p;
      ++c2;
    }
    
    return output;
  }
  

}

int main()
{
  std::vector<float> input = {1, 3.3, 3.1, 10, 4, 6, -10, 6};
  std::vector<float> sorted = rf::merge_sort(input);
  
  std::cout << "Results" << std::endl;
  for (auto element : sorted) std::cout << element << "\n";
}
