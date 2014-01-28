#include <string>
using std::string;

class Parser {

  struct table {
     string first;
     string second;
     string third;
  } c_table [3] = {
   {"0","a","b"}, // <-- note the braces
   {"0","c","d"},
   {"0","e","f"}
  };
};

int main() {}