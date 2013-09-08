//main.cpp
#include <iostream>
using std::cout;
using std::cin;

int main()
{
    unsigned short numbers[3];
    short legnagyobb;
    
    for(unsigned short index = 0; index < 3; ++index)
    {
        cout << index + 1 << " szam: ";
        cin >> numbers[index];
    }
    
    legnagyobb = *numbers;
    short index = 1;
    while(index < 3)
    {
        if(numbers[index] > legnagyobb)
            legnagyobb = numbers[index];
        ++index;
    }
    
    cout << "A legnagyobb szam a: " << legnagyobb;
    return 0;
}