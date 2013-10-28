#include <iostream>
#include <string>

using namespace std;


bool operator <<(const string& member, const string& player)
{
    return member == player;
}



int main()
{
    bool b = string("Hi") << string("Hi");

    cout << b;

}