 #include <iostream>
 #include <functional>

class B
{
  public:
    B(const std::function<double (double)>& func) : func(func) {}
    
    void foo(double d) 
    {
       std::cout << func(d);   
    }
    
  private:
    std::function<double (double)> func;
};

class A
{   
  public:
    double md;
    B b;
  
    double f(double d) const
    {
      return md * d;
    }
  
  public:
    A(double d) : md(d), b(std::bind(&A::f, this,  std::placeholders::_1)) { }
};



int main() {
   A a(42);
   a.b.foo(2); 
}