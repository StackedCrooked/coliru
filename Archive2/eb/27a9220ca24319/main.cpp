#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


using namespace std;


int main()
{
  vector<int> v { 1, 2, 3, 4}; 
  cout << "{\n\t"; 
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(cout, "\n\t")); 
  cout << "}\n"; 
}
