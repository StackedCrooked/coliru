#include <fstream>
#include <iostream>


int main(int argc, const char *argv[])
{
  using namespace std;
  fstream infile("main.cpp");
  basic_streambuf<char>* buf = infile.rdbuf();
  cout << static_cast<void *> (buf) << endl;
  cout << buf;
}
