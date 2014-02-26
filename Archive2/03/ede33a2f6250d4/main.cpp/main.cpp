#include <iostream>
#include <string>
#include <vector>
#include<time.h>



template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
int randint(int low,int high)
{
  int range = high - low;  // add 1 to this to make it inclusive, see below
  return (rand() % range) + low;
  
}
int main()
{
    srand(time(0));
   printf("Reuslt %02d",rand());
}
