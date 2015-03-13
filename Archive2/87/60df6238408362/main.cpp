#include <iostream>
#include <algorithm>

struct Something
{
    int number ;
    Something* next ;
};

int main()
{
    Something* list = new Something{ 51, new Something{ 37, new Something{ 76, new Something{ 48, new Something{ 60, nullptr } } } } };
    for( Something* p = list ; p != nullptr ; p = p->next ) std::cout << p->number << ' ' ; std::cout << '\n' ;

    // sort O(N*N)
    for( Something* p = list ; p != nullptr ; p = p->next )
        for( Something* q = p->next ; q != nullptr ; q = q->next )
            if( q->number < p->number ) std::swap( p->number, q->number ) ;

    for( Something* p = list ; p ; p = p->next ) std::cout << p->number << ' ' ; std::cout << '\n' ;
}
