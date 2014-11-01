struct Base
{
   Base(){}
};

struct Derived : Base
{
   Derived() {}
};

int main()
{
    Derived d;
    //d.Base();
    d.~Base();
}