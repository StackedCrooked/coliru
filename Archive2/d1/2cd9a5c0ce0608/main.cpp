struct bar
{
     bar() {};    
};

void func()
{
  static bar tbar;
}

int main() {func();}