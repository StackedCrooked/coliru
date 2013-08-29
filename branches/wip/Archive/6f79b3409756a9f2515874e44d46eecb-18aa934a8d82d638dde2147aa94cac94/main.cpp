#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

string myreturn(){
    int myInt = 1234;
    char buffer[5];
    sprintf(buffer,"%d",myInt);
    return string(buffer); 
}


int main()
{
    cout << myreturn() << endl;
    return 0;

}