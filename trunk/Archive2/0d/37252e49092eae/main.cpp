#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <iomanip>
#include <initializer_list>

using std::cout;   using std::endl;
using std::cin;    using std::cerr;  
using std::begin;  using std::end;           /* lib begin and end function (for arrays) */
using std::vector;
using std::string; using std::setw;  
using std::left;   using std::right;         /* align print out result */
using std::initializer_list;

void error_msg(initializer_list<string> il) {
  for(const auto &elem : il)
    cout << elem << " ";
  cout << endl;

}

int main(int argc, char *argv[]) {

  string expected = "Hello", actual = "There";

  error_msg({"FunctionX: ", expected, actual});

  return 0;

}
