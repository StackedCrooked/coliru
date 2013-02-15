#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <iomanip>
#include <future>

using namespace std;
  
int retInt(int a) { return a; }
void randomFunction() 
{
    int a = 3;
    auto future = async([&] ()->int{ return retInt(a); });
    const auto ret = future.get();
}

int main()
{

    randomFunction();
	
    return 0;
}