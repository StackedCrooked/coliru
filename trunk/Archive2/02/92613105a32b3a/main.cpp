class foo
{
  friend void bar() {}
  void asd() {bar();}
};

int main() { }