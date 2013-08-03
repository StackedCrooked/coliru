class Foo
{
public:
  void Bar(int param = 0);

private:
  void Bar();
};

void Foo::Bar(int param)
{
  // do something
  return Bar();
}

int main() {}