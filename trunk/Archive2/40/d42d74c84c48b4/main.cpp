#include <string>
#include <iostream>
int main()
{
    std::string s1 { u8"åäö" };
    std::string s2 { u8"\u00E5\u00E4\u00f6" };
  std::cout << s1.size() << "\n" << s2.size() << "\n";
}