#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
  int arrA[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> vecIntA(arrA, arrA+sizeof(arrA)/sizeof(arrA[0]));

  vector<int> vecIntB(vecIntA.size());

  //copy((vecIntA.rbegin()+3).base(), (vecIntA.rbegin()+1).base(),  vecIntB.begin()); // OK    

  vector<int>::iterator s = (vecIntA.rbegin()+3).base();
  vector<int>::iterator e = (vecIntA.rbegin()+1).base();
  cout << "s: " << *s << ", e: " << *e << endl;
  reverse_copy(s, e,  vecIntB.begin()); // error: function call has aggregate value

  //copy(vecIntB.begin(), vecIntB.end(), ostream_iterator<int>(cout, ","));
  cout << endl;
}