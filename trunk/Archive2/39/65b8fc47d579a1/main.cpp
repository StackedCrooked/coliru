#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class MyObject  
{    
protected:
    string length;
    string width;
    float cost;

public:
    friend ostream& operator<<(ostream& output, const MyObject& _myObject);
    friend istream& operator>>(istream& input, MyObject& _myObject);
};

istream& operator>>(istream& input, MyObject& _myObject)
{
    cout << "Enter Length, zones and cost:" << endl;
    std::getline(input, _myObject.length);
    std::getline(input, _myObject.width);
    input >> _myObject.cost;
    return input;
}

ostream& operator<<(ostream& output, const MyObject& _myObject)
{
    cout.precision(2);
    output << "Length is: " << _myObject.length << "\nWidth is: " << _myObject.width << "\nCost is : $" << fixed << _myObject.cost << endl;
    return output;
}

int main(){
    std::istringstream ss("This Length\nThis Width\n2.50");
    MyObject obj;
    ss >> obj;
    std::cout << obj;
}