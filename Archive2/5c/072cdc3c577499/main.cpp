#include <iostream>

class X
{
public:
  X()
  {
    m_size = 0;
    std::cout << "default";
    std::cout << this << std::endl;
  };
  
  explicit X(int size)
  {
    m_size = size;
    std::cout << "ordinary";
    std::cout << this;
    std::cout << " size";
    std::cout << &size << std::endl;
  }
  
  X(const X &otherX)
  {
    std::cout << "copy";
    std::cout << this;
    std::cout << &otherX << std::endl;   
  }
  
  X(X&&)
  {
    std::cout << "move";
    std::cout << this << std::endl;
  }
  
  X BiggerSize(const X &otherX)
  {
    std::cout << "BiggerSize";
    std::cout << this;
    std::cout << &otherX << std::endl;
    if (m_size > otherX.m_size)
        return *this;
    else
        return otherX;
  }
  
  X SmallerSize(const X &otherX)
  {
    std::cout << "SmallerSize";
    std::cout << this;
    std::cout << &otherX << std::endl;
    if (m_size < otherX.m_size)
        return *this;
    else
        return otherX;
  }
  
  ~X()
  {
    std::cout << "destructor";
    std::cout << this << std::endl;
};

private:
    int m_size;
};

int main()
{
    X x1 = X();
    X x2 = X(1);
    X x3 = x1;
    X x4 = x1.BiggerSize(x2);
    X x5 = x1.SmallerSize(x2);
  return 0;
}
