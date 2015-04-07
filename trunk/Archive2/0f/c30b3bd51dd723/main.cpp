#include <iostream>
#include <cstring>
 
int main()
{
    char a[20];
    std::memset(a, '1', sizeof a);
    for (char ai : a) std::cout << ai;
}