//ganito po pag nag enter ako ng word kaylangan nyang mag loop sa cin ulit. ang hinihingi po kasi number
#include <iostream>
using namespace std;

int main()
{
    int i;
    
    cout << "Enter a number> ";
    
    while( !(cin >> i) )
    {
        cout << "Invalid number entered. Enter Again> ";
        
        cin.clear(); // clear error flags
        cin.ignore(100, '\n'); // discard 100 characters or until newline is found
    }
    
    cout << "The number is: " << i << '\n';
}
