#include <vector>
#include <algorithm>
#include <iostream>

int main()
{


const int i=9;

const_cast<int&>(i) =6 ;



std::cout << i ;
}