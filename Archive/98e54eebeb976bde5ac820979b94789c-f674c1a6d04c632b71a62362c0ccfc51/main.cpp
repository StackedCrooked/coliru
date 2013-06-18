#include <iostream>
#include <map>

int main ()
{
std::map<int,int> mymap;

int test = mymap.max_size();

std::cout << test; //178,956,970

return 0;
}