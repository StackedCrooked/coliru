#include <string>
#include <functional>
#include <iostream>
using namespace std;

void bar(const std::string& s) { cout << s << endl; }
void bar(std::function<void()> f) { cout << "function" << endl; }

int main()
{
    bar("ala");
}
