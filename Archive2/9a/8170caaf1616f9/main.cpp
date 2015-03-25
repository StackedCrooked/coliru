#include <iostream>
using namespace std;

int main()
{
    cout << "Enter 10 numbers between 1 and 25" << endl;
    
    uint32_t word = 0;
    
    int input_number[10] = { 3, 8, 12, 4, 25, 15, 18, 5, 1, 10};
    
    for (int i = 0; i < 10; i++)
        word |= 1 << input_number[i];
    
    for (int i=0; i<32-3; i++) 
    {
        unsigned int mask = 7 << i;
        if ( ( word & mask ) == mask)
           // three consecutive bits set -> input contained i, i+1 and i+2
           cout << "3 consecutives " << i << " " << i+1 << " " << i+2 << endl;
    }
    
    return 0;
}
