#include <string>

class Foo
{
public:
  /*explicit*/ operator std::string() const { return ""; }
};

std::string bar{Foo{}};
std::string baz(Foo{});

int main(){}
