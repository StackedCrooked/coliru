struct Base
{
    virtual void method() = 0;
};

void Base::method(){}

struct Derived : Base
{
    void method() { Base::method(); };
};

int main()
{
  Derived d;
  d.method();
}