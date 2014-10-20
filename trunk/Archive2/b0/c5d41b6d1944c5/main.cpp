#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int main() {
  string str = "string";
  istringstream is(str);
  is >> setw(6) >> str;
  return is.eof();
}