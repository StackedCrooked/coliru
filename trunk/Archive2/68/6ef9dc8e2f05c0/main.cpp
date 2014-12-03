#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int main ()
{
  map <pair<int, int>, int> my_map;
  pair <int, int> my_pair;

  my_pair = make_pair(1, 2);
  my_map[my_pair] = 3;

  // My attempt on iteration
  for(map<pair<int,int>,int>::iterator it = my_map.begin(); it != my_map.end(); ++it) {
    cout << it->first.first << "\n";
  }

  return 0;
}