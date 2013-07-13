#include <iostream>
#include <vector>

int main()
{
std::vector <int> vec;
vec.resize(5);
vec.erase(vec.begin() + 2);
std::cout << vec.size() << std::endl;
std::vector<int>::iterator it;
vec.erase(it + 2);
std::cout << vec.size() << std::endl;
}
