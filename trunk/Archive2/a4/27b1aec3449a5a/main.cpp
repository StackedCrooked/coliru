#include <type_traits>
#include <string>
#include <iostream>
using namespace std;

class Parameter
{
public:
    enum eVarType { BOOL, NUMBER};

    Parameter() {};
    template<class X>
    Parameter( string param_name, string param_description, X dft, enable_if_t<is_same<decay_t<X>, bool>::value> = 0 ) { type_ = BOOL; cout << "BOOL" << endl;}
    Parameter( string param_name, string param_description, double dft ) { type_ = NUMBER; cout << "NUMBER" << endl;};
    eVarType type_;
};

int main() {
    Parameter p1("", "", true);
    Parameter p2("", "", 10);
    return 0;
}