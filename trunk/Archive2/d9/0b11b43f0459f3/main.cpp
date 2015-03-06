#include <fstream>
#include <iostream>
#include <string>

namespace {
void one_pass(std::istream& is) {
  std::string lin;
  for (int num = 0; std::getline(is, lin); ++num) {
    std::cout << '#' << num << ':' << lin << '\n';
  }
}
} // unnamed namespace

int main(int argc, char**argv)
{
  std::ifstream inp{argc > 1 ? argv[1] : __FILE__};

  std::cout << "first pass\n";
  one_pass(inp);

  inp.clear();
  inp.seekg(0);

  std::cout << "\nsecond pass\n";
  one_pass(inp);
}
