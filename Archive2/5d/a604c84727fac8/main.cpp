#include <string>
using std::string;
struct Foo { 
  string a;
};

class C {
  Foo f;
public:
  C(string s) : f{s}
  {}
};

int main() {
  C c{"12"};   
}
