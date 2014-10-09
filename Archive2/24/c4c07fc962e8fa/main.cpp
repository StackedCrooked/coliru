#include <iostream> 
#include <algorithm>
#include <iterator>
#include <vector> 

using namespace std; 


bool isOdd(int x) 
{ 
   return x%2==1; 
} 

int main(void)
{ 
   int tab[]={1,2,3,4,5,6,7,8,9,10}; 
   vector<int> myVec(tab, tab + sizeof(tab)/sizeof(tab[0])); 
   vector<int>::iterator it; 

   //printing out all numbers 

  cout << "Vector contains the following numbers: " << endl; 

  std::copy(myVec.begin(), myVec.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

   std::copy_if(myVec.begin(), myVec.end(), std::ostream_iterator<int>(std::cout, " "), isOdd);
std::cout << std::endl;
 }