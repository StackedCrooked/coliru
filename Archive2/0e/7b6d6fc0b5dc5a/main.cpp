#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <iterator>
using namespace std;

int main() {

  vector<int> v = {1,3,5,9,9,0,4,6,9}; //v = {};

   copy (v.cbegin(), v.cend(), 
          ostream_iterator<int>(cout," "));
    cout << endl;

auto left = v.begin();
auto right = left;

for(; right != v.end();++left, ++right ) {
  if(*left == 9) {
    for(;*right == 9 && right != v.end(); ++right);
    if(right == v.end()) break;
    swap(*left, *right);
  }
}

   copy (v.cbegin(), v.cend(), 
          ostream_iterator<int>(cout," "));
    cout << endl;

}