#include <iostream>

template <class T>
class MyClass
{
public:
  MyClass() { }
private:
  void PrivateFunction() { 
    std::cout << "Message From Private Function" << std::endl; 
  }
};

template <class T>
void f()
{
  MyClass<int> a;
  a.PrivateFunction();
}

int main()
{
    f<double>();
}
