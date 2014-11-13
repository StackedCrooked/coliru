#include <iostream>
#include <set>
#include <vector>

std::vector<int> offline_minima(const std::vector<int>& input)
{
  std::vector<int> result;
  std::multiset<int> numbers; // handles duplicate input like in 4,4,5,E,4,6,E,E
  for(int i : input)
  {
    if(i == 'E') // We need to extract the minimum
    {
      if(numbers.empty())
        throw -42; // shouldn't happen with valid input
      result.push_back(*(std::begin(numbers))); // store the minimum number
      numbers.erase(std::begin(numbers)); // remove the minimum number from our sorted numbers
    }
    else
      numbers.insert(i); // store the new number in the sorted set numbers
  }
  return result;
}

int main()
{
  const std::vector<int> input{ 5, 4, 6, 'E', 1, 7, 'E', 'E', 3, 2 };
  const auto result = offline_minima(input);
  
  for(int i : result)
    std::cout << i << '\n';
}