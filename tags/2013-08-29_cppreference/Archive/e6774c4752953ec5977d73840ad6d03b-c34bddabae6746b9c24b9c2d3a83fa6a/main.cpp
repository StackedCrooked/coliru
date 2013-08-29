#include <iostream>
#include <string>

using std::string;

bool space (char c)
{
      return static_cast<bool>(isspace (c));
}

int main() {
    char char1 = ' ';
    char char2 = 'a';
    
    std::cout << space(char1) << " ";
    std::cout << space(char2);
}