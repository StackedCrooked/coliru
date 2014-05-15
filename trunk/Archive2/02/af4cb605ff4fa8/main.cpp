#include <iostream>

template <class T> class LinkList
{
private:

    struct node
    {
        explicit node( const T& v, node* n = 0 ) : value(v), next(n) {}
        T value ;
        node *next ;
    };

    node* head;   // List head pointer
    node* tail; // keepinm track of the tail makes a lot of things efficient

public:

    bool empty() { return head == 0 ; }

    LinkList() : head(0), tail(0) {}

    LinkList( const LinkList<T>& that ) : head(0), tail(0)
    { for( node* n = that.head ; n != 0 ; n = n->next ) append(n->value) ; }

    ~LinkList() { clear() ; }

    LinkList& operator=( const LinkList & that )
    {
        if( head != that.head ) // if not trivial self-assignment
        {
            clear() ; // what the destructor does

            // what the copy constructor does
            for( node* n = that.head ; n != 0 ; n = n->next ) append(n->value) ;
        }
        return *this ;
    }

    void clear() // empty the list
    {
        while( !empty() )
        {
            node* n = head ;
            head = head->next ;
            delete n ;
        }
    }

    void append( const T& v )
    {
        if( !empty() ) { tail->next = new node(v) ; tail = tail->next ; }
        else head = tail = new node(v) ;
    }

    void insert( const T& v )
    {
        if( empty() || tail->value < v ) append(v) ;

        else if( head->value > v ) head = new node(v,head) ;

        else
        {
            node* n = head ;

            // bump n till the next node has a larger value
            for( ; n->next->value <= v ; n = n->next ) ;

            n->next = new node( v, n->next ) ; // insert after n
        }
    }

    // etc.

    void print() const
    {
        if( head == 0 ) std::cout << "[empty]\n" ;
        else
        {
            std::cout << "[ " ;
            for( node* n = head ; n != 0 ; n = n->next ) std::cout << n->value << ' ' ;
            std::cout << "]\n" ;
        }
    }
};

int main()
{
    LinkList<int> lst ;
    lst.print() ; // [empty]

    for( int i = 0 ; i < 5 ; ++i ) lst.append(i) ;
    lst.print() ; // [ 0 1 2 3 4 ]

    lst.insert(-7) ;
    lst.insert(7) ;
    lst.insert(3) ;
    lst.print() ; // [ -7 0 1 2 3 3 4 7 ]

    LinkList<int> lst2 = lst ;
    lst2.print() ; // [ -7 0 1 2 3 3 4 7 ]

    lst.clear() ;
    lst.append(87) ;
    lst.insert(23) ;
    lst.print() ; // [ 23 87 ]

    lst = lst2 ;
    lst.print() ; // [ -7 0 1 2 3 3 4 7 ]
}
