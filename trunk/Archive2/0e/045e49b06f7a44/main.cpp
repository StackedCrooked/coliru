#include <map>
#include <string>

class Foo
{
  static const int Bar = 5;

public:
  Foo() {}
  
  void blub()
  {
      _map[Bar] = "some characters";
  }

  ~Foo() {}

private:
  std::map<int, std::string> _map;
};

int main()
{
  Foo a;
  a.blub();

  return (0);
}