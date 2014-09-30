struct bar
{
    constexpr bar() {};    
};

void func()
{
  static bar tbar;
}