#include <iostream>
#include <string>

using namespace std;

class Base
{
public:
    Base(string parameter = "bums")
    {
        std::cout << parameter;
    }
};

int main() {
    Base("poops");   
}