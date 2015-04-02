#include <vector>
#include <cmath>
#include <iostream>
#include <numeric>
#include <algorithm>
 
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& obj) {
  os << "[";
  for(uint i = 0; i < obj.size(); ++i){
      os << obj.at(i);
      if(i+1 < obj.size()){
          os << ", ";
      }
  }
  os << "]";
  return os;
}

template<typename Ta, typename Tb>
std::vector<Ta> sort_with(const std::vector<Ta>& first, const std::vector<Tb>& second){
    std::vector<std::pair<Ta, Tb>> zip;
    for(uint i = 0; i < first.size() && i < second.size(); ++i){
        zip.emplace_back(first[i], second[i]);
    }
    
    struct {
        bool operator()(std::pair<Ta, Tb> a, std::pair<Ta, Tb> b)
        {   
            return a.second < b.second;
        }   
    } compare_second;
    
    std::sort(zip.begin(), zip.end(), compare_second);
    
    std::vector<Ta> r;
    for(auto pair : zip){
        r.push_back(pair.first);
    }
    return r;
} 
 

int main(){
    std::vector<char> letters = {'t','h','e','c','o','s','h','m','a','n'};
    std::cout << letters << "\n";
    std::sort(letters.begin(), letters.end());
    std::cout << letters << "\n";
    std::vector<int> order = {9,4,3,2,7,8,11,5,6,1};
    std::cout << sort_with(letters, order);
}