#include <algorithm>
#include <iterator>
#include <iostream>

int main()
{
   char s[] = "12345\n6789";
   char newline = *std::find(std::reverse_iterator<char *>(s + 10),
   std::reverse_iterator<char *>(s),
   '\n');
   
   std::cout << (int)newline << std::endl;
}
