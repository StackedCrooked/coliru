#include <iostream>
#include <stdexcept>

void throwing(int x)
{
  if(x) throw std::runtime_error("x non-null");
}

int main()
{
  try {
    throwing(1);
  } catch(std::runtime_error const&ex) {
    std::clog << "error: \"" << ex.what() << '\"' << std::endl;
    std::terminate();
  }
  return 0;
}
