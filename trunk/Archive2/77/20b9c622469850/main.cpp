#include <iostream>
#include <vector>
#include <algorithm>

void print (int i) 
{
    std::cerr << i << ",";
}

int main()
{
    std::vector <int> v {1, 2, 3, 4};
    std::for_each (v.begin (), v.end (), print);
}
