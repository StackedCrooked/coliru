#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;


void FindElements ( const list<int>& inputList, list<int>& outputList )
{
    for ( int i : inputList )
    {
        if ( i > 5 ) { outputList.push_back ( i );     }
    }
}


int main()
{
    std::cout << "hello world" << std::endl;
    
    list<int> initialList = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    
    list<int> finalList;
    FindElements ( initialList, finalList );
    
    for ( int i : finalList )
    {
        std::cout << "listElement: " << i << std::endl;
    }
}
