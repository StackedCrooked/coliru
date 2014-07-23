#include <vector>
#include <algorithm>
#include <iostream>

int main() 
{
  // Our orders
  std::vector<int> o1 = { 0,1,2,4,3 };
  std::vector<int> o2 = { 0,1,2,3,4 };
  std::vector<int> o3 = { 0,2,1,3,4 };
  std::vector<int> o4 = { 0,1,3,2,4 };
  
  // Regroup items by type
  std::vector<int> item1 = { o1[0] , o2[0], o3[0], o4[0] };
  std::vector<int> item2 = { o1[1] , o2[1], o3[1], o4[1] }; 
  std::vector<int> item3 = { o1[2] , o2[2], o3[2], o4[2] }; 
  std::vector<int> item4 = { o1[3] , o2[3], o3[3], o4[3] };
  
  // Lookup median elements
  std::nth_element(item1.begin(), item1.begin() + item1.size()/2, item1.end());
  std::nth_element(item2.begin(), item2.begin() + item2.size()/2, item2.end());
  std::nth_element(item3.begin(), item3.begin() + item3.size()/2, item3.end());
  std::nth_element(item4.begin(), item4.begin() + item4.size()/2, item4.end());
  
  std::cout << "Most wanted item 1 is " << item1[item1.size()/2] << '\n';
  std::cout << "Most wanted item 2 is " << item2[item2.size()/2] << '\n';
  std::cout << "Most wanted item 3 is " << item3[item3.size()/2] << '\n';
  std::cout << "Most wanted item 4 is " << item4[item4.size()/2] << '\n';
}