#include <iostream>

using std::cout;
using std::endl;

int main()
{
  cout << "i\t++i + i++\n";
  for(size_t i = 0; i<10; )
  {
    cout << i << "\t" << ++i + i++ << endl;
  }
  cout << "i\t++i\n";
  for(size_t i = 0; i<10; )
  {
    cout << i << "\t" << ++i << endl;
  }
  cout << "i\ti++\n";
  for(size_t i = 0; i<10; )
  {
    cout << i << "\t" << i++ << endl;
  }
{
  int x = 5;
  cout << x << "\t" << ++x + x++ << endl;
 }
{ int x = 5;
  cout << x;
  cout << "\t" << ++x + x++ << endl;
 } 
  return 0;
}