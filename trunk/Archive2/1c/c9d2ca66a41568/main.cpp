#include <iostream>
#include <string>

using namespace std;

class Base
{
public:
    virtual ~Base() {}
    virtual void whoami(const string& str= string()) const
    {  cout << "Base::whoami(" << str <<")\n";  }
};

class Child;

class Sub : public Base
{
public:
    Sub()
    {  whoami();  }
    Sub(const Base&)
    {  whoami("Base&");  }
    Sub(const Sub&)
    {  whoami("Sub&");  }
    Sub(const Child&)
    {  whoami("Child&");  }
    virtual ~Sub() {}
    virtual void whoami(const string& str= "") const
    {  cout << "Sub::whoami(" << str <<")\n";  }
};

class Child : public Base
{
public:
    Child()
    {  whoami();  }
    Child(const Child&)
    {  whoami("Child&");  }
    virtual ~Child() {}
    virtual void whoami(const string& str= "") const
    {  cout << "Child::whoami(" << str <<")\n";  }
};


int main()
{
    Base b;
    Sub s;
    Child c;
    cout << "---\n";
    
    Sub copy(static_cast<Sub>(c));
    static_cast<Sub>(c);
    cout << "---\n";
    
    //copy.whoami("!");
    Sub s2(c);
}
