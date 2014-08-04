#include <iostream>
#include <vector>

template<typename T, typename F>
void push_if(std::vector<T>& v, T element, F& f)
{
    if(f(element))
       v.push_back(element);
}

int main()
{
  std::vector<int> v;
  auto is_range = [](int i) {return i >= 8 && i <= 23; };
  
  push_if(v, 8, is_range);
  push_if(v, 24, is_range);

  for(auto& e : v)
    std::cout << e << " ";

  return 0;
}