#include <list>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(void)
{
  list<int> myList;
  srand (time (NULL));
  for (int i = 0; i < 10; i++)
    myList.push_back (rand () % 100);

  list<int>::iterator it = myList.begin (), lastElement = myList.end ();
  lastElement--;
  for (int i = 0; i < (int) myList.size (); i++)
      {
        list<int>::iterator jt = myList.begin (), jtPlus1 = jt;
        ++jtPlus1;
        for (;jt != lastElement; ++jt, ++jtPlus1)
            {
               if (*jt > *jtPlus1)
                   {
                       int temp = *jt;
                       *jt = *jtPlus1;
                       *jtPlus1 = temp;
                   }
            }
        --lastElement;
      }
     
    it = myList.begin ();
    for (;it != myList.end (); ++it)
        cout << *it << ' ';
    cout << endl;
}