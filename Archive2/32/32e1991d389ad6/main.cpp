#include <iostream>
#include <string>

using namespace std;

int main()
{
  string v = "abcdef"; // use string here so output is trivial

  string::size_type insert_index = 1; // at the location of 'b'
  string::size_type move_index = 4; // at the location of 'e'

  while(move_index > insert_index)
  {
    std::swap(v[move_index], v[move_index-1]);
    --move_index;
  }
  std::cout << v;
}