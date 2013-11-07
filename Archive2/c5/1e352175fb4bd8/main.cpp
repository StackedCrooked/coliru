#include <iostream>
#include <future>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
   vector<int> vec(10);
   iota(begin(vec), end(vec), 0);
   
   auto f = async([&]{ return accumulate(begin(vec), end(vec), 0); });
   
   cout << f.get() << endl;
   
 
}