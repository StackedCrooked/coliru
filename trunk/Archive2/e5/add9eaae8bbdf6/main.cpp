#include <iostream>
using namespace std;

template<typename T, unsigned ROW, unsigned COL>
void callfun(T const (&text)[ROW][COL]){ 

    //This was giving the wrong output 
    cout<< "The no.of rows in a array in cal fun is  :" << ROW <<endl;
}

int main()
{
    const int columns = 30;
    char sampletext[][columns] = { {'M','Y'},{'E','X','A','M','P','L','E'},{'I','S'},{'N','O','T'},{'W','O','R','K'} };

    //This was giving the correct output 
    cout<< "The no.of rows in a array in main fun is :" <<sizeof(sampletext)/sizeof(sampletext[0])<<endl;
    callfun(sampletext);
    return 0;
}
