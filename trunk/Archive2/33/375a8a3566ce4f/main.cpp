#include <iostream>

using namespace std;



template <int... Entries>
struct StaticArray
{

  int size  = sizeof... (Entries);// line A
  //int array[size] = {Entries...};// line B

};


int main()
{
   StaticArray<1,2,3,4> sa;
   cout << sa.size << endl; 

   return 0;
}