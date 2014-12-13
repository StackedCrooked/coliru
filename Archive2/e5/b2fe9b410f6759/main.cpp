#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
string s;
std::getline(std::cin, s);

istringstream iss(s);

do
{
    string sub;
    iss >> sub;
    cout << "Substring: " << sub << endl;
} while (iss);

}