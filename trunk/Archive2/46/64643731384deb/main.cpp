#include <iostream>
#include <algorithm>

int main() {
  char str[] = "abcdefghzi...zkdllsz";
  char key[] = "z";
  auto c = std::find_first_of(std::begin(str), std::end(str), std::begin(key), std::end(key));
  if(c != std::end(str)) {
    std::cout << key << " found at position " << std::distance(std::begin(str), c) << std::endl;    
  } else {
    std::cout << key << " not found" << std::endl;
  }
}