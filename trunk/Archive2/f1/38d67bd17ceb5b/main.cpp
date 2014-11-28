#include <iostream>
#include <stdio.h>

using namespace std;

int main ()
{
    int i;
    int *vPtr;
    int *e;
    
    e = new int[5];
    e[0] = 2;
    
    for (i=1 ; i<5 ; i++ )
    {
        cout << "Values in array: " << endl;
        
        for (i=0 ; i<5 ; i++)
        {
            cout << "e is ["<<i<<"] is " << e[i] << endl;
        }
        
        cout << endl;
        cout << "Values by 1st statement : vPtr = &e[i] : " << endl;
        
        for ( i=0 ; i<5 ; i++ )
        {
            vPtr = &e[i];
            cout << "Address for e ["<< i <<"] is : " << vPtr << endl;
        }
        
        cout << endl;
        cout << "Values by 2nd statement : vPtr = (e + i) : " << endl;
        
        for ( i=0 ; i<5 ; i++ )
        {
            vPtr = (e + i);
            cout << "Address for e ["<<i<<"] is : " << vPtr << endl;
        }
        
        cout << endl;
        cout << "Values stored using pointer notation : *(e+i) : " << endl;
        
        for ( i=0 ; i<5 ; i++ )
        {
            cout << "Values stored: " << *(e+i) << endl;
        }
        
        system ("Pause");
        return 0;
    }
}
    
    