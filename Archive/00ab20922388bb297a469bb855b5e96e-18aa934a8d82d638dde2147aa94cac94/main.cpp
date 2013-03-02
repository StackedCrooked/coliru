#include <iostream>
#include <string>

using namespace std;

string myreturn(){
    int myInt = 1234;
    return to_string(myInt);
}


int main()
{
    cout << myreturn() << endl;
    return 0;

}