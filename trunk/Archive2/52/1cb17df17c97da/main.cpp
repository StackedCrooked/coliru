#include <iostream>
#include <string>
#include <sstream>


using namespace std;

template<class T>
void writeln(T item)
{
    stringstream ss;
    ss << item << '\r' << endl;

    cout << ss.str();
}


int main()
{
    writeln("123");

    std::string s = "abc";

    writeln(s);
}