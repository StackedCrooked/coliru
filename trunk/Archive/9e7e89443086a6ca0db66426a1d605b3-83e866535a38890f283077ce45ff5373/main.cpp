#include <iostream>
#include <list>
#include <cstdarg>

using namespace std;

template<class TYPE>
list <TYPE> MakeList ( int num, ... ){
  va_list arguments;                     
  va_start ( arguments, num ); 
  list <TYPE> PoliticianList;
  for ( int x = 0; x < num; x++ ) {
      PoliticianList.push_back(va_arg (arguments, TYPE));
  }
  va_end ( arguments );                 

  return PoliticianList;       
}

int main()
{
    MakeList<int>(3, 1, 1, 1);
    cout << "OK" << endl;
}