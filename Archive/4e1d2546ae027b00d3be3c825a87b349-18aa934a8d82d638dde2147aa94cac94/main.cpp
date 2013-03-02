#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string myreturn(){
    int myInt = 1234;
    string myStr;
    stringstream out;
    out << myInt;
    myStr = out.str();
    return myStr;
}


int main()
{
    cout << myreturn() << endl;
    return 0;

}