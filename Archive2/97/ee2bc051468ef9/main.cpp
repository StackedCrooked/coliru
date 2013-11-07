#include <iostream>
#include <algorithm>

struct List
{
    struct Node { int value ; Node* next ; };
    int mySize = 0 ;
    Node* first ;
    bool change(int first_pos, int second_pos) ;
};

bool List::change(int first_pos, int second_pos)
{
    if( first_pos > second_pos ) std::swap(first_pos,second_pos) ;

    if( first_pos < 0 || second_pos > mySize) return false ;
    if( first_pos == second_pos ) return true ;

    int cnt = 0 ;
    Node* n = first ;

    for( ; cnt < first_pos ; ++cnt ) n = n->next ;
    Node* first_node = n ;

    for( ; cnt < second_pos ; ++cnt ) n = n->next ;
    Node* second_node = n ;

    std::swap( first_node->value, second_node->value ) ;
    return true ;
}

int main()
{
    List lst ;
    using Node = List::Node ;
    lst.first = new Node{ 0, new Node{ 1, new Node{ 2, new Node{ 3,
                           new Node{ 4, new Node{5,nullptr} }}}}} ;
    lst.mySize = 6 ;

    for( Node* n = lst.first ; n ; n = n->next ) std::cout << n->value << ' ' ;
    std::cout << '\n' ;

    lst.change(1,4) ;
    for( Node* n = lst.first ; n ; n = n->next ) std::cout << n->value << ' ' ;
    std::cout << '\n' ;

    lst.change(2,3) ;
    for( Node* n = lst.first ; n ; n = n->next ) std::cout << n->value << ' ' ;
    std::cout << '\n' ;
}
