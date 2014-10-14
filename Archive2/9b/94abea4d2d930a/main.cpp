/*
    AVL Tree
    Author : Prashant Srivastava
             Algorithmica Batch Sept,2014.
             
    Compiled with gcc 4.8.1 (C++11)
        g++ -o AVL AVL.cpp -std=c++11 -Wall -Wextra -O2
        
    Coliru Link : http://coliru.stacked-crooked.com/a/55f5c35ff5044d78
*/

#include <iostream>
#include <queue>
#include <functional>
#include <cassert>


template<typename T>
struct Node 
{
    T data;
    std::size_t height ;
    Node<T>* left;
    Node<T>* right;
    Node( T val ):data(val),height(1),left(nullptr),right(nullptr) { }

};


template<typename T>
class AVLTree
{
    private:
        Node<T>* root;
        std::size_t size;
        
        std::size_t Height( Node<T>* current ) const 
        {
            if(current == nullptr )
                return 0;
            return current->height ;        
        }
        
        Node<T>*  RotateLeft( Node<T>*  );
        Node<T>*  RotateRight( Node<T>*  );
        void aux_delete( Node<T>*  );
        Node<T>* aux_add( Node<T>* , T  );
        bool aux_contains( Node<T>* , T  ) const ;
        
    public:
        void add(T );
        bool remove(T ); // Not Implemented
        bool contains(T ) const ;
        void display( const std::function<void(T)>&  ) const;
        std::size_t count( ) const { return size ; }
        
        AVLTree(): root(nullptr),size(0) { }
        AVLTree& operator=(const AVLTree& ) = delete;
        AVLTree (const AVLTree& ) = delete;
        ~AVLTree() ;
};

template<typename T>
AVLTree<T>::~AVLTree()
{
   aux_delete( root );
   root = nullptr ;
}

template<typename T>
void AVLTree<T>::aux_delete( Node<T>* current )
{
    if( current != nullptr )
    {
        aux_delete( current->left );
        aux_delete( current->right );
        delete current ;
    }
}

template<typename T>
bool AVLTree<T>::contains(T val) const 
{
    return aux_contains( root, val );
}

template<typename T>
bool AVLTree<T>::aux_contains( Node<T>* current, T val) const 
{
    if( current != nullptr )
    {
        if( val < current->data )
            return aux_contains( current->left, val );
        if( val == current->data ) 
            return true ;
        else 
            return aux_contains( current->right, val );
    }
    
    return false ;
}

template<typename T>
void AVLTree<T>::add(T val )
{
    root = aux_add( root, val );
    ++size ;
}

template<typename T>
Node<T>* AVLTree<T>::RotateLeft( Node<T>* current )
{
    Node<T> *y = current->right;
    Node<T> *T2 = y->left;

    y->left = current;
    current->right = T2;
 
    current->height = std::max( Height(current->left), 
                                Height(current->right) )+1;
    y->height = std::max( Height(y->left), 
                          Height(y->right) )+1;
 
    return y;
}

template<typename T>
Node<T>* AVLTree<T>::RotateRight( Node<T>* current )
{
    Node<T> *x = current->left;
    Node<T> *T2 = x->right;
 
    x->right = current;
    current->left = T2;
 
    current->height = std::max( Height(current->left), 
                                Height(current->right) )+1;
    x->height = std::max( Height(x->left), 
                          Height(x->right) )+1;
    
    return x;
}


template<typename T>
Node<T>* AVLTree<T>::aux_add(Node<T>* current,  T val )
{
    
    if( current == nullptr )
        return new Node<T>( val );
    if( val < current->data )
        current->left = aux_add( current->left, val );
    else
        current->right = aux_add( current->right, val );   
  
    current->height = std::max( Height(current->left), 
                                Height(current->right) ) + 1;

    int balance = ( current == nullptr ) ? 0:
                  ( Height(current->left) - Height(current->right) ) ;
                          
    // Balance the Tree                          
    if (balance > 1 && val < current->left->data )
        return RotateRight(current);
 
    if (balance < -1 && val > current->right->data )
        return RotateLeft(current);

    if (balance > 1 && val > current->left->data )
    {
        current->left =  RotateLeft( current->left );
        return RotateRight(current);
    }

    if (balance < -1 && val < current->right->data )
    {
        current->right = RotateRight(current->right);
        return RotateLeft(current);
    }
   
    return current ;
}

template<typename T>
void AVLTree<T>::display( const std::function<void(T)>& visit ) const
{
    // Level Order
   std::queue< Node<T>* > Q;
   Q.push( root );
   Node<T>* temp;
   while ( !Q.empty() )
   {
    temp = Q.front();
    Q.pop();
    visit( temp->data );
    if( temp->left )
        Q.push( temp->left );
    if( temp->right )
        Q.push( temp->right );
   }
   
}

int main()
{
    AVLTree<char> Tree;
    
    std::string input("ABCDEF"), str;
    for( auto x: input )
        Tree.add(x);
        
    
    // std::function<void(const char& )> visit = 
                        // []( const char& x)
                        // { std::cout << x << ' '; } ;
    // Tree.display (visit ) ;
    
    std::function<void(const char& )> visit1 = 
                        [&str]( const char& x)
                        { str+=x; } ;
                        
    Tree.display ( visit1 ) ;
    
    assert( str == "DBEACF" ); 
    assert( Tree.count() == input.length() );
    assert( Tree.contains('E') == true ); 
    assert( Tree.contains('X') == false ); 
    
    return 0;
}


