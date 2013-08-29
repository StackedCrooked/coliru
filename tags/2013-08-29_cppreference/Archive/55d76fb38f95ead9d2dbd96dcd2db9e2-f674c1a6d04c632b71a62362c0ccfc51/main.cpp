class Something
{
  private:
  static int s_nValue;
  
  public:
  static int staticAccess() { return s_nValue; }
  int Access() { return s_nValue; }

};

int Something::s_nValue = 1; // initializer


int main()
{
    Something s;
    Something::staticAccess();
    s.Access();
    
    return 0;
}