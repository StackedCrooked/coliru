#include <iostream>

struct node
{
    int data ;
    node* next ;
};

node* first = nullptr ;
node* last = nullptr ;

void push( int number )
{
    node* n = new node { number, nullptr } ;

    if( first == nullptr ) first = last = n ;

    else
    {
        last->next = n ;
        last = n ;
    }
}

void find( int number )
{
    int cnt = 0 ;

    for( node* n = first ; n != nullptr ; n = n->next )
    {
        if( n->data == number )
        {
            std::cout << "found " << number << " at position " << cnt << '\n' ;
            return ;
        }

        else ++cnt ;
    }

    std::cout << number << " was not found\n" ;
}

int main()
{
    for( int v : { 23, 56, 78, 93, 41, 52, 12, 78, 65, 84 } ) push(v) ;
    
    find(23) ; // found 23 at position 0
    find(52) ; // found 52 at position 5
    find(84) ; // found 84 at position 9
    find(200) ; // 200 was not found
}
