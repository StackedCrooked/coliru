#include <iostream>       // std::cout
#include <vector>

using namespace std;

/*int ret;

int fun(const int& val)
{
    //int ret;
    ret += val;
    
    return ret;
}

int main ()
{
    for( const int& i : std::vector<int>({1,2,3}) )
        std::cout << i << ": " << fun(0) << std::endl;
    
    return 0;
}*/

int main () 
{   
    int a[10]; // wystarczy do zainicjalizowania: int a[10] = {};
    int i;   // nie zainicjalizowana
    cout << i << endl;
    for(int i = 0; i< 10; i++)
        cout << a[i] << " ";
    return 0;
}