#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;
using namespace std::placeholders;



typedef bool (*FN)( void* a, int b, void * );

bool same( void* a, int b )
{
    return cout << (a != NULL) << endl;
}

void some( int* a )
{
    cout << (a != NULL) << endl;
}

int main()
{
    std::function<void(int*, int)> fun;

    int K = 10;
    bool x = true;
    if( fun )
        fun(&K,20);
        
    FN fptr = NULL;
    void *data = NULL;
    fun = std::bind(same, _1 , _2); 

    if( fun ) {
        cout << "-calling with fn ptr" << endl;
        fun(&K,20);
    }
    
    fun = std::bind(some, _1); 
    if( fun ) {
        cout << "-calling with fn ptr" << endl;
        fun(&K,20);
    }
    
    std::cout << x << std::endl;
}
