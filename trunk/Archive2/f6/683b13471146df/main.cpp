#include <iostream>
#include <stdarg.h>
#include <string>

void print(std::string pattern, ...) {
  va_list LIST;
  va_start(LIST, pattern);

  std::string::iterator s = pattern.begin(), e = pattern.end();
  while (true) {
    std::string::iterator f = std::find(s, e, '%');  // find %
    if (f == pattern.end()) break;
    s = f+1;
    if (*(f + 1) == 'd') {
      int val = va_arg(LIST, int);
	  std::cout << val << '\n';

    } else if (*(f + 1) == 'c') {
      char val = va_arg(LIST, int);
	  std::cout << (char)val << '\n';

    } else if (*(f + 1) == 'f') {
      float val = va_arg(LIST, double);
	  std::cout << val << '\n';
    } else if (*(f + 1) == 's') {
      std::string val = va_arg(LIST, std::string);
      std::cout <<val<<'\n';
    }
  }

  va_end(LIST);
}
int main() 
{
	print("%d%c%f%s", 2, 'a', 6.34, std::string("test"));
}