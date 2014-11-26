#include <iostream>
#include <memory>
#include <cassert>
#include <sstream>

template <typename T>
struct Node 
{
    T data ;
    std::shared_ptr< Node<T>> next ;
    Node( T x ):data(x),next( nullptr )
    {
    }
    Node( const Node<T>& ) = delete ;
    Node<T>& operator = (const Node<T>& ) = delete ;

} ;

template <typename T>
class LinkedList
{
    std::shared_ptr< Node<T> > head ;
    
    public :
        LinkedList( ):head( nullptr ) 
        {
        }
        
        LinkedList( const LinkedList<T>& ) = delete ;
        LinkedList<T>& operator = (const LinkedList<T>& ) = delete ;
        void add( T data ) ;
        void remove( T data );
        bool contains( T data );
        template <typename U>
        friend std::ostream& operator <<( std::ostream& os, const LinkedList<U> & L );
} ;


template <typename T>
void LinkedList<T>::add( T data )
{
    std::unique_ptr<Node<T>> temp ( new Node<T>( data )  ); // Key Idea 
    
    if( head == nullptr )
    {
        head = std::move ( temp ) ;
    }
    else
    {
        temp->next = head ;
        head = std::move ( temp ) ;
    }
        
}

template <typename U>
std::ostream& operator <<( std::ostream& os, const LinkedList<U> & L )
{
    auto ptr = L.head ;
    while ( ptr != nullptr )
    {   
        os << ptr->data << " ";
        ptr = ptr->next ;
    }
    
    return os ;
}


template <typename T>
bool LinkedList<T>::contains( T data )
{
    auto ptr = head ;
    while ( ptr != nullptr )
    {   
        if ( ptr->data == data  )
        {
            return true ;
        }
        ptr = ptr->next ;
    }
    return false ;
}

template <typename T>
void LinkedList<T>::remove( T data )
{
    auto curr = head ;
    auto prev = head ;
    if( head->data == data )
    {
        if( head->next != nullptr )
        {
            head = head->next ;
        }
        else
        {
            head = nullptr ;
        }
        return ;
    }
    while ( curr->next != nullptr )
    {   
        if ( curr->data == data  )
        {
            break ;
        }
        prev = curr ;
        curr = curr->next ;
    }    
    
    prev->next =  curr->next ; 
}

int main( )
{

    LinkedList<std::string> ll ;
    
    for( const auto& x: { "Jack", "King", "Queen", 
                          "Ace", "Rook", "Bishop", 
                          "Pawn", "Knight", "Joker"
                         }  )
    { 
       ll.add( x ) ;
    }
   
   std::ostringstream oss;
   oss << ll ;
   
   assert( oss.str( ) == "Joker Knight Pawn Bishop Rook Ace Queen King Jack " ) ;
   assert( ll.contains("King") == true );
   
   ll.remove ( "Queen" );
   assert( ll.contains("Queen") == false );
   
}