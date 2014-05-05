class A
{
  public:
  A()
  {
    m_Integer = 0;
  }
  private:
  int m_Integer;
};


class B : A
{
  public:
  B()
  {
  }
  private:
  int m_Integer;
  
  public:
  bool check() { return m_Integer;}
  
};

int main()
{
  B vB;
  
  if (false == vB.check())
  {
    return 1;
  }

  return 0;
}
