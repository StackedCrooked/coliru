#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char**argv)
{
  std::string path = argc>1?std::string{argv[1]}:std::string(__FILE__);
  std::ifstream inp{path};
  int num=0;
  std::cout << "first pass" << std::endl;
  do {
    std::string lin;
    std::getline(inp,lin);
    if (inp.eof())
      break;
    num++;
    std::cout << "#" << num << ":" << lin << std::endl;
  } while (!inp.eof());
  inp.seekg(0, inp.beg);
  inp.sync();
  inp.clear();
  std::cout << "second pass" << std::endl;
  num=0;
  do {
    std::string lin;
    std::getline(inp,lin);
    if (inp.eof())
      break;
    num++;
    std::cout << "##" << num << ":" << lin << std::endl;
  } while (!inp.eof());
  inp.close();
  return 0;
}