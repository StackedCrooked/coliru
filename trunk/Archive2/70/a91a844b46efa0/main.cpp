#include <iostream>
#include <strings.h>

using namespace std;

string Message()
{
    cout<<"Entrer le message a criper/decripter d'après le codage de césar"<<endl;
    string phrase;
    getline(cin, phrase);
    return phrase;
}

int main()
{
    return 0;
}
