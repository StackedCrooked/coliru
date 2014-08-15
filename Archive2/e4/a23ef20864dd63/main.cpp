#include <iostream>
#include <string>

template <class T>
class Stack
{
    public:
    Stack();
    Stack( const Stack& );
    ~Stack();
    Stack& operator=( const Stack& );
    int size() const;     // returns number of elements
    bool empty() const;   // returns true iff this is empty
    T& top() const;       // returns the top element
    void push( const T& );  // inserts given element on top
    void pop();           // removes element from top

    T& bottom();


    protected:
    class Node
    {
        public:
        Node( const T& data, Node* next = 0 ) : _data( data ), _next( next ) {}
        T _data;
        Node* _next;
    };
    Node* _top;
    int _size;
};

template <class T>
Stack<T>::Stack() : _top( 0 ), _size( 0 )
{}

template <class T>
Stack<T>::Stack( const Stack& s ) : _top( 0 ), _size( s._size )
{
    if( _size == 0 ) return;
    Node* pp = 0;
    for( Node* p = s._top; p; p = p->_next )
        if( p == s._top ) pp = _top = new Node( p->_data );
        else pp = pp->_next = new Node( p->_data );
}

template <class T>
Stack<T>::~Stack()
{
    while( _top )
    {
        Node* p = _top;
        _top = _top->_next;
        delete p;
    }
}

template <class T>
int Stack<T>::size() const
{
    return _size;
}

template <class T>
bool Stack<T>::empty() const
{
    return _size == 0;
}

template <class T>
T& Stack<T>::top() const
{
    return _top->_data;
}

template <class T>
void Stack<T>::pop()
{
    Node* p = _top;
    _top = _top->_next;
    delete p;
    --_size;
}

template <class T>
void Stack<T>::push( const T& x )
{
    if( _size == 0 ) _top = new Node( x );
    else _top = new Node( x, _top );
    ++_size;
}


class stack : public Stack<char>
{
    public:
    char& bottom();

};

/************************************************
template<class T>
T& Stack<T>::bottom()
{

    while( Stack<T>::size() != 1 )
    {
        Stack<T>::top();
        Stack<T>::pop(); // *** removes items from the stack
    }

    return _top->_data;

}
******************************************************/

template < typename T > T& Stack<T>::bottom() // invariant: !empty()
{
    auto n = _top ;
    for( int i = 1 ; i < size() ; ++i ) n = n->_next ;
    return n->_data ;
}


#include <iostream>
#include <string.h>


template <class T>
void print( Stack<T> );

int main()
{
    Stack<std::string> s;

    s.push( "first" );     print( s );

    s.push( "second" )    ;     print( s );

    s.push( "third" )   ;     print( s );

    s.pop();     print( s );

    s.pop();        print( s );

    std::cout << std::endl;


}


template<class T>
void print( Stack<T> s )
{
    std::cout << "size=" << s.size() << " top=" << s.top()
              << " bottom=" << s.bottom() ;

    while( s.size()>0 )
    {
        std::cout << " ( " << s.top() << ", ";
        s.pop();

        while( !s.empty() )
        {
            std::cout << s.top() << ", ";
            s.pop();
        }

        std::cout << " )" << std::endl;
    }
}
