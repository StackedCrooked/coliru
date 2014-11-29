#include <iostream>
#include <vector>
#include <iterator>

int main(){

  std::vector<int> ivec = { 1, 2, 3, 4, 5 }; //initializes vector ivec.
  int arr[5]; //initializes array "arr" with 5 null elements.

  std::copy(std::begin(ivec), std::end(ivec), arr);
  std::copy(arr, arr + 5, std::ostream_iterator<int>(std::cout, " "));
}