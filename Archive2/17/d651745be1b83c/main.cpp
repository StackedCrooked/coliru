// align example
#include <iostream>
#include <memory>

int main() {
  char buffer[] = "------------------------";
  void * pt = buffer;
  std::size_t space = sizeof(buffer)-1;
  while ( std::align(alignof(int),sizeof(char),pt,space) ) {
    char* temp = static_cast<char*>(pt);
    *temp='*'; ++temp; space-=sizeof(char);
    pt=temp;
  }
  std::cout << buffer << '\n';
  return 0;
}