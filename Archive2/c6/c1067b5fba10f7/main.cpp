#include <iostream>
#include <string>

using namespace std;


int main()
{

    char bytearray[] = {65,66,67};
    string s = string((char*)bytearray); 

    cout << s << endl;
}
