#include <iostream>
#include <functional>
#include <map>

using namespace std;

struct Numbers { double X, Y, Z; };

int main()
{
    Numbers Input;
    string memberVariable;
    double variableValue;

    map<string, function<double&(Numbers&)> > mappings {
        { "X", &Numbers::X },
        { "Y", &Numbers::Y },
        { "Z", &Numbers::Z },
    };

    cout << "Enter number" << endl;
    cin  >> variableValue;            // User enters 100.0 for example
    cout << "Enter variable" << endl;
    cin  >> memberVariable;           // User enters a char or string that equals X

    mappings[memberVariable](Input) = variableValue;
}
