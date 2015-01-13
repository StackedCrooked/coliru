#include <stdio.h>

namespace chrome {
  char kDo = 'l';
  
  char Do(char x) { return x; }
}

#define kDo Do('r')

int main() {
  //chrome::kDo = 'a';
  printf("%c\n", chrome::kDo);
}