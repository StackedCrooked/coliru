#include <utility>
#include <tuple>
#include <iostream>


int main()
{
    int a,b;

    +[]
    {
        int a;  //  C4456: declaration of 'a' hides previous local declaration
    }; 
}
