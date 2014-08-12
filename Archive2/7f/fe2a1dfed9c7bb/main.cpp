#include <iostream>
#include <list>

std::list<int> A;
std::list<int> B;
std::list<int>::iterator location;

int main()
{
    A.push_back( 1 );
    location = A.begin();
    B.splice( B.end(), A, A.begin() );
    std::cout<<(*location)<<std::endl;
}