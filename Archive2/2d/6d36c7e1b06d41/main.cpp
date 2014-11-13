#include <iostream>

using namespace std;

template<int T, typename R> R fun() { return T; }
template<int T> int fun<T, int>() { return T; }
template<> double fun<3, double>() { return 16; }
int main()
{
   cout << std::to_string(fun<2>()) << endl; 
   cout << std::to_string(fun<3>()) << endl; 
   
   return 0;
}
