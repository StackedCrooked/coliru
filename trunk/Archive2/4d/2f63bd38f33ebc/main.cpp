#include <list>
#include <iostream>
#include <iterator>
 
int main( )
{
    std::list<int> testing;
    for (int i = 0; i < 10; ++i)
    {
        testing.push_back(i);
    }
    for (std::list<int>::iterator it = testing.begin(); it != testing.end(); it++)
    {
        if (*it == 2 || *it == 3)
        {
            testing.erase(it);
            //if you do it = testing.erase(it), it will skip the check for 3
        }
    }
    for (std::list<int>::iterator it = testing.begin(); it != testing.end(); it++)
    {
        printf("%d ", *it);
    }
    printf("\n");
}