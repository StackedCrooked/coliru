#include <iostream>
#include <string>

using namespace std;

class Base
{
public:
    Base()
    {  show();  }  // wszystkie metody w ctor będą wywołane w wersjach z klasy Base
    
    void show() const
    {  cout << "Base::show()\n"; ping();  }
    virtual void ping() const
    { cout << "Base::ping()\n";  }
};

class Sub : public Base
{
public:
    Sub()
    : Base()  // w konstruktorze Base metoda show oraz ping będą wywołane w wersjach dla Base nawet jeśli są virtual
    {  show();  }
    
    virtual void show() const
    {  cout << "Sub::show()\n"; ping();  }
    virtual void ping() const
    { cout << "Sub::ping()\n";  }
};

int main()
{
    cout << "> Base b;\n";
    Base b;
    cout << endl;
    
    cout << "> Sub s;\n";
    Sub s;  // najpierw tworzy Base z wywołaniem metod w wersjach tylko dla Base
    cout << endl;
    
    cout << "> Base& ref = s;\n> ref.show();\n";
    Base& ref = s;
    ref.show();  // show nie jest virtual ale ping już tak
}
