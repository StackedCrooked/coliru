#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>

void Swap(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end)
{
  std::string temp;
  temp = *begin;
  *begin = *end;
  *end = temp;
}

void QuickSort(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end, std::vector<std::string>& v)
{
  // Initially find a random pivot
  if (begin == end || *begin == *(end - 1))
    return;
  int pivotIndex = std::rand() % (end - begin);
  std::string pivot = *std::next(begin, pivotIndex);
  
  // Pointer to begining of array and one to the end
  
  std::vector<std::string>::iterator posBegin = begin, posEnd = end;
  
  // While begin != end 
  while(begin != end)
  {
    // Find the lowest bound number to swap
    while(*begin < pivot && begin < end)
      begin++;
    while(*end >= pivot && begin < end)
      end--;
    
    // Do the swap

      Swap(begin, end);
  }
  
  // Here begin and end are equal and equal to point from where left side is lower and right side is greater or equal to pivot
  
  // Partition left
  QuickSort(posBegin, begin, v);
  // Partition right
  QuickSort(end, posEnd, v);
}

int main()
{
   std::vector<std::string> paths = {"a", "c", "d", "b", "a", "c"};
   QuickSort(paths.begin(), --paths.end(), paths);
   for (unsigned int i = 0; i < paths.size(); i++)
      std::cout << i << ". " << paths.at(i) << std::endl;
}