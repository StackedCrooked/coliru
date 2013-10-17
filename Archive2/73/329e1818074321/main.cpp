//  Convert this program to C++
//   change to C++ io
//   change to one line comments
//   change defines of constants to const
//   change array to vector<>
//  inline any short function

#include <iostream>      // for std::cout
#include <vector>          // for std::vector
#include <numeric>       // for std::accumulate
#include <algorithm>     // for std::generate

const int N=40;

using namespace std;

// returns the sum of the contents of a vector<int>
inline int sum(vector<int> d) { return accumulate(d.begin(), d.end(), 0); }

int main()
{
   // initialize array data (as an array we define STL vector<int>)
   vector<int> data(N);
   
   // STL generic function generate and lambda expression initilizes
   // vector data with initial values 1, 2, 3, 4, 5...
   int i(0);
   generate(data.begin(), data.end(), [&](){ return i++; });

   int accum = sum(data);
   cout << "sum is " << accum << endl;

return 0;
}

// WARNING:  compile it with g++ 4.8.1 using the command:
// > g++-4.8 -std=c++11  homework1.cpp -o homework1