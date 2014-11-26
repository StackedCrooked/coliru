/*
   Implementation for Binary Search Tree
   
   g++ -o tree tree.cpp -std=c++11 -Wall -Wextra -O3
   
Author :
   Prashant Srivastava

*/

#include <iostream>
#include <queue>
#include <functional>
#include <limits>

template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
    Node( T x ): data(x), left(nullptr), right(nullptr)
    {
    
    }
    ~Node( )
    {
        left = right = nullptr ;
    }
};

typedef enum {
        PREORDER,
        INORDER,
        POSTORDER,
        BFS
} VISIT_TYPE;
    
template <typename T>
class Tree
{
    Node<T>* root ;
    bool verbose ;
    std::function<void(Node<T>*) > func ;
    
    Tree ( const Tree& ) = delete ;
    Tree& operator = (const Tree& ) =delete ;
    
    Node<T>* insert( T, Node<T>*   ) ;
    Node<T>* deattach( T, Node<T>*   ) ;
    
 
    void dfs( VISIT_TYPE, Node<T>* , std::function<void(Node<T>*) >  )  ;
    template< typename F >
    F bfs( Node<T>*, F  );
    Node<T>* findMin( Node<T>*  );
    public :
        Tree ( std::function<void(Node<T>*) > fobj, bool ver = false ):root( nullptr ), verbose(ver), func( fobj )
        {
        
        }
    
    std::size_t height( )
    {
        std::function<std::size_t(Node<T>*)> f;
        
        f=[this,&f]( Node<T>*r ) -> std::size_t
                {
                    if( r == nullptr ) return 0;
                    else 
                    {
                        std::size_t leftL, rightL;
                        leftL = f( r->left );
                        rightL =f( r->right );
                        
                        return std::max( leftL, rightL ) +1 ;
                    }
                    return 1;
                } ;
                
        return f( root );
    }
    
    void visit( VISIT_TYPE dt )
    {
        switch( dt )
        {
            case INORDER:
                std::cout << "INORDER   :" ;
            break;
            case PREORDER:
                std::cout << "PREORDER  :" ;
            break;
            case POSTORDER:
                std::cout << "POSTORDER :" ;
            break;
            case BFS:
                std::cout << "BFS       :" ;
                bfs( root, func );
                std::cout << std::endl ;
                return ;
            break ;
        }
        
        dfs( dt, root, func );
        
        std::cout << std::endl ;
    }
    
    void add( T data )
    {
        root = insert( data, root );
    }
    
    void remove( T data )
    {
        root = deattach( data, root );
    }
        
    ~Tree( )
    {
        std::function<void(Node<T>*) > fobj =
                    [this] ( Node<T>* r)
                    { 
                        if ( verbose )
                        std::cout << r->data 
                                  << " ...deleted."
                                  << std::endl ; 
                        delete r ;
                    } ;
       
         dfs( POSTORDER, root, fobj );
         root = nullptr ;
    }
};


template<typename T>
Node<T>* Tree<T>::findMin( Node<T>* r )
{

   struct X
   {
        T min_val ;
        Node<T>* min_node; 
        
        X( ):min_val( std::numeric_limits<T>::max( ) ), min_node( nullptr )
        {      
        }
        void operator()( Node<T>* r)
        {
            if( r->data < min_val )
            {
                min_val = r->data ;
                min_node = r  ;
            }
        }
   };
   
   X x = bfs( r, X() ) ;
   if ( verbose )
    std::cout << x.min_node->data << " Min Val ";
   
   return x.min_node ;
}
    
    
template<typename T>
template<typename F> 
F Tree<T> :: bfs( Node<T>* r, F fobj )
{
    if (r == nullptr ) std::move( fobj ) ;
    std::queue<Node<T>* > Q;
    Q.push( r );
    
    while( !Q.empty() )
    {
        Node<T>* current = Q.front( );
        fobj( current );
        Q.pop( );
        if( current->left != nullptr ) 
            Q.push( current->left );
        if( current->right != nullptr ) 
            Q.push( current-> right );
        
    }
    return std::move( fobj ) ; 
}

template<typename T>
void Tree<T>::dfs(  VISIT_TYPE dt, Node<T>* r, std::function<void(Node<T>*) > func ) 
{
    if ( r == nullptr ) return ;
    switch( dt )
    {
        case PREORDER:
            func( r );
            dfs( dt,r->left,func );
            dfs( dt,r->right,func  );
        break;
        case INORDER:
            dfs( dt, r->left,func );
            func( r );
            dfs( dt, r->right,func  );
        break;
        case POSTORDER:
            dfs( dt, r->left,func  );
            dfs( dt, r->right,func );
            func( r );
        break;
        default :
            break;
    }

}

template<typename T>
Node<T>* Tree<T>::insert( T data, Node<T>* r )
{
    
    if( r == nullptr )
    {
        if ( verbose )
            std::cout << "\tAdded "<< data << ".\n" ;
        Node<T>* temp = new Node<T>( data );
        r = temp ;
    }
    else if( r->data > data )
    {
        if ( verbose )
            std::cout <<  data << " going left.\n" ;
        r->left = insert( data, r->left );
    }
    else
    {
       if ( verbose )
        std::cout <<  data << " going right.\n" ;
       r->right = insert( data, r->right );
    }
    return r;
}

template<typename T>
Node<T>* Tree<T>::deattach( T data, Node<T>* r )
{
   if( r == nullptr ) return nullptr ;
   else if ( r->data > data )
    r->left = deattach( data, r->left );
   else if ( r->data < data )
    r->right = deattach( data, r->right );
   else
   {
        if( r->left == nullptr && r->right == nullptr )
        {
            delete r;
            r = nullptr ;
        }
        else if( r->right == nullptr )
        {
            Node<T>* temp = r;
            r = r->left ;
            delete temp ;
        }
        else if( r->left == nullptr )
        {
            Node<T>* temp = r;
            r = r->right ;
            delete temp ;
        }
        else 
        {
            Node<T>* temp = findMin( r->right );
            r->data = temp->data;
            r->right = deattach( temp->data, r->right ) ;
        }
   }
   
   return r ;
}

// void visit ( Node<char>* r )
// {
    // std::cout << r->data << " " ;
// }

int main( )
{

    std::string s="FDJBEGKACI";
    std::function<void(Node<char>*) > visit = 
            []( Node<char>* r ) 
            { 
                std::cout << r->data << " " ;
            } ;
            
    Tree<char> tree( visit );
    
    for( const char& x: s )
        tree.add( x  ) ;
        
    tree.visit( VISIT_TYPE::PREORDER );
    tree.visit( VISIT_TYPE::INORDER );
    tree.visit( VISIT_TYPE::POSTORDER  );
    tree.visit( VISIT_TYPE::BFS  );
    
    std::cout << "Height of Tree :"<< tree.height( ) << std::endl ;
    std::cout << "Remove Node : B\n";
    tree.remove ( 'B' );
    tree.visit( VISIT_TYPE::INORDER );
    
}

