class Bar { };

class Foo
{
public:
  void do_something(Bar& bar) {}
 
};

int main()
{
  Bar bar;
  Foo foo;
  foo.do_something(bar);
}