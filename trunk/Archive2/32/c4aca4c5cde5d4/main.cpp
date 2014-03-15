#include <algorithm>
#include <iostream>
#include <iterator>
#include <ios>

int main()
{
    int bigList[] = {1,2,3,4,5,6,7,8,9};
    int smallList[] = {3,4,5,6};

    std::cout << std::boolalpha;
    std::cout << std::includes(
        std::begin(bigList), std::end(bigList), 
        std::begin(smallList), std::end(smallList)
    );
}
