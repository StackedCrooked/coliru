#include <iostream>
#include <string>

using namespace std;

int main()
{
  string v = "abcdef"; // use string here so output is trivial

  string::size_type insert_index = 1; // at the location of 'b'
  string::size_type move_index = 4; // at the location of 'e'

  string::iterator insert = v.begin()+insert_index;
  string::iterator move = v.begin() + move_index;

  while(move != insert)
  {
    std::iter_swap(move, move-1);
    --move;
  }
  std::cout << v;
}
