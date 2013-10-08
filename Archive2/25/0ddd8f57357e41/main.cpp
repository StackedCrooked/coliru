#include <iostream>
#include <sstream>

using namespace std;
 
int main()
{
    istringstream input("abcd\ndef\ngh");

 
    for (char a[4]; input.getline(&a[0], 5, '\n'); ) {
        cout << &a[0] << endl;
    }
 

}