class A
{
public:
  A(){}
  A(const A&) = delete;
};

class B
{
  A a;
};

int main()
{
  B b;
  B c = b;  
}