class bar
{
  public:
    bar() { a=0; };    
  private:
    int a;
};

void func()
{
  static bar tbar;
}
