#include <iostream>
#include <utility>
#include <vector>

template<class T>
std::vector<std::pair<T, T> > adjacent_pairs(std::vector<T>& elements)
{
  std::vector<std::pair<T, T> > pair_elements(elements.size() - 1);
  for(size_t i = 0; i < elements.size() - 1; i++) {
    pair_elements[i] = std::make_pair(elements[i], elements[i + 1]);
  }
  return pair_elements;
}

int main()
{
    int a_elements[10] = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
    std::vector<int> elements(a_elements, a_elements + 10);
    std::vector<std::pair<int, int> > pair_elements = adjacent_pairs(elements);
    for(size_t i = 0; i < pair_elements.size(); i++) {
      std::cout << pair_elements[i].first << ", " << pair_elements[i].second << std::endl;
    }
}
