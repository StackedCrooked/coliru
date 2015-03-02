#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using myPairType = std::pair<double, int>;
using myVectorType = std::vector<myPairType>;


myVectorType getSorted(const myVectorType& new_vector, const myVectorType& old_vector) {
  myVectorType sorted(new_vector.size());
  auto matching_value = [&new_vector](const myPairType& old_value){ return new_vector[old_value.second - 1]; };
  std::transform(old_vector.begin(), old_vector.end(), sorted.begin(), matching_value);
  return sorted;
}

void peturbValues(myVectorType& values) {
  static std::mt19937 eng(0);
  static std::uniform_real_distribution<double> dist(-0.1, 0.1);
  for (auto& value : values)
    value.first += dist(eng);
}

int main() {  
  auto v = myVectorType{
    {0.6594, 1},
    {0.5434, 2},
    {0.5245, 3},
    {0.8431, 4}
  };
  std::sort(v.begin(), v.end()); 
  auto old_v = v;
  
  for (auto i = 0; i != 10; ++i) {
    peturbValues(v);
    auto new_v = getSorted(v, old_v);
    std::sort(new_v.begin(), new_v.end());
    
    old_v = std::move(v);
    v = std::move(new_v);
    
    for (const auto& value : v)
      std::cout << "{" << value.first << "," << value.second << "}" << " ";
    std::cout << "\n";
  }
}
