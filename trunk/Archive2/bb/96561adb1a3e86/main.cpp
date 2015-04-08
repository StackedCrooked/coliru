#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
  generate_n( ostream_iterator<char>(cout), 10, []{ return '*'; } );  
}
