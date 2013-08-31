#include <iostream>
#include <string>
#include <vector>

using namespace std;




class Base 
{
        
    public:
        virtual string Classname() = 0;
        Base() { ++myCount; }
        ~Base() { --myCount; }
        static int getCount() { return myCount; }
        
    private:
        static int myCount;
};

int Base::myCount = 0;

class Derived1 : public Base
{
    public: 
        virtual string Classname() override { return "Derived1"; }
        string GetLabel() { return myLabel; }
        void SetLabel ( string x ) { myLabel = x; }
        
    private:
        string myLabel;

};

namespace 
{
    static void f ( Base* base) 
    {
        cout << base->Classname();
    }
}

int main () {
    
    //auto b1 = new Base;
    
    Derived1 b2;
    Derived1* b3 = new Derived1();
    f ( &b2 );
    f ( b3 );
    
}


    
    
    
    
    
    
    

    