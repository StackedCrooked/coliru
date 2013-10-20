#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isUnique(string &str);

int main()
{

    char a[] ="abcdefg";
    
    char *aPtr;
    aPtr = a;
    
    for(int m = 0; m < sizeof(a); ++m){
        cout << m << ": " << a[m] << endl;;   
    }
    
    cout << endl;
    
    return 0;
}

