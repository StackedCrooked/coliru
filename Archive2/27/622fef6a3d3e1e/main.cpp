#include <iostream>
#include <algorithm>

void remove(char arr[], int& size, int element, int count) {
  std::rotate(arr + element, arr + element + count, arr + size);
  size = size - count;
}

int main() {
  char array[] = {'A','B','C','D','E'};
  int size = sizeof(array) / sizeof(char);
  remove(array, size, 2, 2);
  for(std::size_t i(0); i < size; ++i) std::cout << array[i] << " ";
  std::cout << std::endl;
}