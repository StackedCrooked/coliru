#include <iostream>
#include <memory>

using namespace std;

class C {
public:
    C( string n ) : _name{n} { cout << "Constructing a C named '" << _name << "'\n"; };

    C() : _name( "EMPTY" ) { cout << "Default-constructing a C named '" << _name << "'\n"; } ;     // default-ctor

    C( const C& c ) : _name{c._name} {
        _name += " [copied]";
        cout << "Copy-constructing a C named '" << _name << "'\n";
    };

    C( C&& c )
        : _name{c._name} {
        _name += " [moved]";
        cout << "Move-constructing a C named '" << _name << "'\n";
    };

    ~C() { cout << "Destructing a C named '" << _name << "'\n"; };

    string getName() { return _name; };

private:
    string _name;
};

C fooVal() {    
    cout << "In fooVal\n";
    string str = "value return";
    C c(str);
    return c;
}

// IMPORTANT: THIS NEEDS TO BE COMPILED WITH FLAG -fno-elide-constructors
int main(int argc, const char * argv[])
{
    C cv(fooVal());        
    cout << "cv constructed\n";  
    cout << "Alive: " << cv.getName() << ".\n";
}