#include <iostream>

const char * s(bool a)
{
  return (a ? "true" : "false");
}

void test(bool a, bool b)
{
  std::cout << s(a) << " < " << s(b) << " = " << s(a < b) << std::endl;                                                                                          
}

int main()
{
  test(false, false);
  test(false, true);
  test(true, false);
  test(true, true);
}