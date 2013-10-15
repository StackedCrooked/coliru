#include <string>
#include <iostream>

int main() {
  std::wstring s0(L"foo");
  std::wstring s1(L"bar");
  std::cout << "The two strings are " << (s0 == s1 ? "equal" : "not equal") << std::endl;
  s0.compare(s1);
}