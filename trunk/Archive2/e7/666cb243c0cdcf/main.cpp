#include <algorithm>
#include <fstream>   // output file   
#include <iostream>
#include <istream>   // input file
#include <string>    // OPTION
#include <unistd.h>  // for argc and argv[]
#include <vector>    // read file and put in std::vector

template <typename Comparable_1, typename Comparable_2> class AvlTree;

template <typename Comparable_1, typename Comparable_2>
class AvlNode
{
      Comparable_1 element1; // sequence
      Comparable_2 element2; // enzy
      AvlNode *left;
      AvlNode *right;
      int height;
      bool exist;
      AvlNode( const Comparable_1 & theElement1, const Comparable_2 & theElement2, AvlNode *lt, AvlNode *rt, int h = 0, bool ex = false): 
      element1( theElement1 ),element2( theElement2 ), left( lt ), right( rt ), height( h ), exist( ex ) { }
      friend class AvlTree<Comparable_1, Comparable_2>;
};

template <typename Comparable_1, typename Comparable_2>
class AvlTree
{
      public:
             AvlTree() : root ( NULL ) { }
             ~AvlTree( );
             explicit AvlTree( const Comparable_1 & notFound );
             AvlTree( const AvlTree & rhs);
             const Comparable_1 & findMin( ) const;
             const Comparable_1 & findMax( ) const;
             const Comparable_1 & find( const  Comparable_1 &x ) const;
             const Comparable_1 & find( const Comparable_1 & x, const Comparable_2 y  ) const;
             bool isEmpty( ) const;
             bool findEnzyme( const Comparable_1 & x, const Comparable_2 y  ) const;
             int height( ) const;
             void stats(double &avgd, int &height);    // compute statistics
             void print (const int order) const;
             const int printNodeNumber( ) const;
             const int & printDepth( ) const;
//             void insert( const  Comparable_1 & x ); 
             void insert( const Comparable_1 & x, const Comparable_2 y );
             void remove( const  Comparable_1 &x );
             void lazydeletion ( const Comparable_1 & x);
        	 void lazydeletion ( const  Comparable_1 &x, AvlNode<Comparable_1, Comparable_2> * & t );
			 void makeEmpty(  );
			 const AvlTree operator=( const AvlTree & rhs );
			 bool operator==( const AvlTree & rhs );     // This is compare the whole node
			 bool operator!=( const AvlTree & rhs );
			 bool operator< ( const AvlTree & rhs );
			 
      private:
              AvlNode<Comparable_1, Comparable_2> *root;
              const Comparable_1 ITEM_NOT_FOUND;
              const Comparable_1 & elementAt( AvlNode<Comparable_1, Comparable_2> *t ) const;
//              void insert( const  Comparable_1 &x, AvlNode<Comparable_1, Comparable_2> * & t );
              void insert( const Comparable_1 & x, const Comparable_2 y , AvlNode<Comparable_1, Comparable_2> * & t );
              AvlNode<Comparable_1, Comparable_2> * findMin( AvlNode<Comparable_1, Comparable_2> *t ) const;
              AvlNode<Comparable_1, Comparable_2> * findMax( AvlNode<Comparable_1, Comparable_2> *t ) const;
              AvlNode<Comparable_1, Comparable_2> * find( const  Comparable_1 &x, AvlNode<Comparable_1, Comparable_2> *t ) const;
              AvlNode<Comparable_1, Comparable_2> * find( const Comparable_1 & x, const Comparable_2 y, AvlNode<Comparable_1, Comparable_2> *t ) const;
              bool findEnzyme( const Comparable_1 & x, const Comparable_2 y, AvlNode<Comparable_1, Comparable_2> *t ) const;
              void printPre(AvlNode<Comparable_1, Comparable_2> *t) const;
              void printPost(AvlNode<Comparable_1, Comparable_2> *t) const;
              void printIn(AvlNode<Comparable_1, Comparable_2> *t) const;
              int height( AvlNode<Comparable_1, Comparable_2> *t ) const;
              void stats( int &nnodes, int cdepth, int &tdepth, int &mdepth, AvlNode<Comparable_1, Comparable_2> *t );
              const int printNodeNumber( AvlNode<Comparable_1, Comparable_2> * & t ) const;
              const int * printDepth( AvlNode<Comparable_1, Comparable_2> * t ) const;
              void remove( const  Comparable_1 &x , AvlNode<Comparable_1, Comparable_2> * & t );
              int max( int lhs, int rhs ) const;
              void rotateWithLeftChild( AvlNode<Comparable_1, Comparable_2> * & k2 ) const;
              void rotateWithRightChild( AvlNode<Comparable_1, Comparable_2> * & k1 ) const;
              void doubleWithLeftChild( AvlNode<Comparable_1, Comparable_2> * & k3 ) const;
              void doubleWithRightChild( AvlNode<Comparable_1, Comparable_2> * & k1 ) const;
              void clone( AvlNode<Comparable_1, Comparable_2> * & t );
              void makeEmpty( AvlNode<Comparable_1, Comparable_2> * & t );
};

template <typename Comparable_1, typename Comparable_2>
bool AvlTree<Comparable_1, Comparable_2>::isEmpty( ) const
{
     if (root == NULL){return true; }
     else if ((root != NULL )) {return false;}
     else{ return false;}
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 & AvlTree<Comparable_1, Comparable_2>::elementAt( AvlNode<Comparable_1, Comparable_2> *t ) const
{
           return t == NULL ? ITEM_NOT_FOUND : t->element1;
}

template <typename Comparable_1, typename Comparable_2>
AvlTree<Comparable_1, Comparable_2>::AvlTree( const AvlTree & rhs)
{
    root = new AvlNode<Comparable_1, Comparable_2> (rhs->element1, rhs->element2, rhs->left, rhs->right, rhs->height, rhs->exist);

}

template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::insert( const Comparable_1 & x, const Comparable_2 y )
{
     insert( x, y, root );                        // x = key, y = value
}

template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::insert( const Comparable_1 & x, const Comparable_2 y, AvlNode<Comparable_1, Comparable_2> * & t )
{
     if( t == NULL )
         t = new AvlNode<Comparable_1, Comparable_2>( x, y, NULL, NULL, true );
     else if( x < t->element1 )
     {
          insert( x, y, t->left );
          if( height( t->left ) - height( t->right ) == 2 )
          {
              if( x < t->left->element1 )
                  rotateWithLeftChild( t );
              else
                  doubleWithLeftChild( t );
          }
     }
     else if( x > t->element1 )
     {
          insert( x, y, t->right );
          if( height( t->right ) - height( t->left ) == 2 )
          {
              if( x < t->right->element1 )
                  rotateWithRightChild( t );
              else
                  doubleWithRightChild( t );
          }
     }
     else // ( x == t->element1 )
     {
         t->element2 = y;
     }
     t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 & AvlTree<Comparable_1, Comparable_2>::findMin( ) const
{
      return elementAt( findMin( root ) );
}

template <typename Comparable_1, typename Comparable_2>
AvlNode<Comparable_1, Comparable_2> * AvlTree<Comparable_1, Comparable_2>::findMin( AvlNode<Comparable_1, Comparable_2> *t ) const
{
                       if( t == NULL )
                           return NULL;
                       if( t->left == NULL )
                           return t;
                       return findMin( t->left );
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 & AvlTree<Comparable_1, Comparable_2>::findMax( ) const
{
      return elementAt ( findMin( root ) );
}

template <typename Comparable_1, typename Comparable_2>
AvlNode<Comparable_1, Comparable_2> *AvlTree<Comparable_1, Comparable_2>::findMax( AvlNode<Comparable_1, Comparable_2> *t ) const
{
                       if( t == NULL )
                           return NULL;
                       if( t->right == NULL )
                           return t;
                       return findMin( t->right );
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 & AvlTree<Comparable_1, Comparable_2>::find( const  Comparable_1 &x ) const
{
	return elementAt( find( x, root ) );
}

template <typename Comparable_1, typename Comparable_2>
AvlNode<Comparable_1, Comparable_2> *AvlTree<Comparable_1, Comparable_2>::find( const  Comparable_1 &x, AvlNode<Comparable_1, Comparable_2> *t ) const
{
	if( t == NULL )
		return NULL;
	else if( t->exist == false )
	{
		std::cout << x << " is not exist in the list.\n";
		return 0;
	}
	else if( x < t->element1 )
		return find( x, t->left );
	else if( x > t->element1 )
		return find( x, t->right );
	else
		return t; // Match
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 & AvlTree<Comparable_1, Comparable_2>::find( const Comparable_1 & x, const Comparable_2 y ) const
{
      return  elementAt( find( x, y, root ) );
}

template <typename Comparable_1, typename Comparable_2>
AvlNode<Comparable_1, Comparable_2> *AvlTree<Comparable_1, Comparable_2>::find( const Comparable_1 & x, const Comparable_2 y, AvlNode<Comparable_1, Comparable_2> *t ) const
{
                       if( t == NULL )
                           return NULL;
                       else if( t->exist == false ) // for lazydeletion
                       {
                            return NULL;
                       }
                       else if( x < t->element1 )
                            return find( x, t->left );
                       else if( x > t->element1 )
                            return find( x, t->right );
                       else // find the key node and looking for the new enzyme
                       {
                            std::cout << "Sequence: "<< t->element1 << std::endl;
                            std::cout << "Enzyme: "<< t->element2 << std::endl;
                            return t; // Match
                       }
}

template <typename Comparable_1, typename Comparable_2>
bool AvlTree<Comparable_1, Comparable_2>::findEnzyme( const Comparable_1 & x, const Comparable_2 y ) const
{
      return findEnzyme( x, y, root );
}

template <typename Comparable_1, typename Comparable_2>
bool AvlTree<Comparable_1, Comparable_2>::findEnzyme( const Comparable_1 & x, const Comparable_2 y, AvlNode<Comparable_1, Comparable_2> *t ) const
{
    if( t == NULL )
       return false;
    else if( t->exist == false ) // for lazydeletion
    {
        return false;
    }
    else if( x < t->element1 )
        return find( x, t->left );
    else if( x > t->element1 )
        return find( x, t->right );
    else // find the key node and start looking for the new enzyme
    {
        if ( t->element2 == y )
        {
           return true; // found
        }
    }
    return false;
}

template <typename Comparable_1, typename Comparable_2>
const int AvlTree<Comparable_1, Comparable_2>::printNodeNumber( ) const
{
      return printNodeNumber ( root );
}

template <typename Comparable_1, typename Comparable_2>
const int AvlTree<Comparable_1, Comparable_2>::printNodeNumber( AvlNode<Comparable_1, Comparable_2> * & t ) const
{
      if (t!=NULL)
      {
                 int r,l;
                 r = printNodeNumber(t->right);
                 l = printNodeNumber(t->left);
                 return r+l+1;
      }
      else
      {
          return 0;
      }
}


template <typename Comparable_1, typename Comparable_2>
const int & AvlTree<Comparable_1, Comparable_2>::printDepth( ) const
{
      return printDepth ( root );
}

template <typename Comparable_1, typename Comparable_2>
const int *AvlTree<Comparable_1, Comparable_2>::printDepth( AvlNode<Comparable_1, Comparable_2> * t ) const
{
    if ( t != NULL )
    {
                int r, l;
                r = printDepth( t->right );
                l = printDepth( t->left );
                if ( r > l )
                {
                        return r + 1;
                }
                else
                {
                    return l + 1;
                }
    }
    return 0;
}

// Print the tree in preorder (order < 0), inorder (order == 0),
// or postorder (order > 0), one value in one line
template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::print (const int order) const
{
    if (order < 1) printPre(root);
    else if (order == 1) printIn(root);
    else printPost(root);
}

//  Printing tree in preorder
template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::printPre(AvlNode<Comparable_1, Comparable_2> * t) const
{
    if (t == NULL){};			    // base case
    std::cout << t->element2
    	 << t->element1;			// print the key
    if (t->exist) 
       std::cout << " [d]" << std::endl;		// (if deleted)
    if (t->left != NULL)
    	printPre(t->left);				// then the left subtree
    if (t->right != NULL)
        printPre(t->right);				// and then the right subtree
}

// Printing tree in postorder 
template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::printPost(AvlNode<Comparable_1, Comparable_2> *t) const
{
    if (t == NULL){};			    // base case
    if (t->left != NULL)
    	printPost(t->left);				// First print the left subtree
    if (t->right != NULL)
    	printPost(t->right);			// then the right subtree
    std::cout << t->element2
    	 << t->element1;			// print the key
    if (t->exist)
       std::cout << " [d]" << std::endl;		// (if deleted)
}

// Printing tree in inorder
template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::printIn(AvlNode<Comparable_1, Comparable_2> *t) const
{
    if (t == NULL){};			    // base case
    if(t->left != NULL)
        printIn(t->left);			    // First print the left subtree
    std::cout << t->element2
    	 << t->element1;			// print the key
    if (t->exist) 
       std::cout << " [d]" << std::endl;		// (if deleted)
    if(t->right != NULL)
    	printIn(t->right);				// and then the right subtree
}

template <typename Comparable_1, typename Comparable_2>
int AvlTree<Comparable_1, Comparable_2>::height( ) const
{
    return height ( root );
}

template <typename Comparable_1, typename Comparable_2>
int AvlTree<Comparable_1, Comparable_2>::height( AvlNode<Comparable_1, Comparable_2> *t ) const
{
    if (t == NULL) {return -1;}
    else {return t->height;}
}

template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::stats(double &avgd, int &height)
{
    int nnodes = 0;		// total # of nodes in the tree
    int cdepth = 0;
    int tdepth = 0;		// sum of depths of all nodes in the tree
    int mdepth = -1;	// maximum depth of any node in the tree
    
    stats(nnodes, cdepth, tdepth, mdepth, root);
    height = mdepth;
    if (nnodes > 0) avgd = double(tdepth) / nnodes;
    else avgd = 0.0;
}


template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::stats( int &nnodes, int cdepth, int &tdepth, int &mdepth, AvlNode<Comparable_1, Comparable_2> *t)
{
    if (t != NULL)
    {
	    nnodes++;
	    tdepth += cdepth;
	    if (cdepth > mdepth) mdepth = cdepth;
	    stats(nnodes,cdepth+1,tdepth,mdepth,t->left);
	    stats(nnodes,cdepth+1,tdepth,mdepth,t->right);    
	}
}

template <typename Comparable_1, typename Comparable_2>
int AvlTree<Comparable_1, Comparable_2>::max( int lhs, int rhs ) const
{
    if (lhs < rhs) 
       return rhs;
    return lhs;
}

template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::remove( const  Comparable_1 &x )
{
     remove( x, root );
}

template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::remove( const  Comparable_1 &x, AvlNode<Comparable_1, Comparable_2> * & t )
{
     if ( t == NULL )
        return;
     // can't delete from an empty tree
     if ( x < t->element1 )
     {
     // delete from the left subtree
     remove( x, t->left );
     // check if the heights of the subtrees are now too different
     if ( height( t->right ) - height( t->left ) == 2 ) // unbalanced
     {
     // right subtree too tall relative to left
     // Which rotation to use depends on whether the left subtree of the
     // right subtree is larger, or the right of the right is larger.
     // If the left is larger we MUST use
        if ( height((t->right)->right) >= height((t->right)->left) )
           rotateWithRightChild( t );
        else
            doubleWithRightChild( t );
     }
     }
     else if( x > t->element1 )
     {
          // delete from the right subtree
          remove( x, t->right );
          if( height( t->left ) - height( t->right ) == 2 ) // unbalanced
          {
          // left subtree too tall
             if( height((t->left)->left) >= height((t->left)->right) )
                 rotateWithLeftChild( t );
             else
                 doubleWithLeftChild( t );
          }
     }
     else { // delete this node
          if ((t->left != NULL) && (t->right != NULL) ) // two non-empty subtrees
          {
                       t->element1 = findMin(t->right)->element1;
                       remove(t->element1, t->right);
                       if ( height( t->left ) - height( t->right ) == 2 ) // unbalanced
                       {
                       // left subtree too tall
                          if ( height((t->left)->left) >= height((t->left)->right) )
                             rotateWithLeftChild( t );
                          else
                              doubleWithLeftChild( t );
                       }
          }
          else {
               AvlNode<Comparable_1, Comparable_2>* OldNode = t;
               t = (t->left != NULL)? t->left : t->right;
               delete OldNode;
               }
          }
          if ( NULL != t )
          t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::lazydeletion ( const  Comparable_1 &x)
{
	lazydeletion(x, root);
}
template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::lazydeletion ( const  Comparable_1 &x, AvlNode<Comparable_1, Comparable_2> * & t )
{
     if( t == NULL )
         return; // Item not found; do nothing
     if( x < t->element1 )
         remove( x, t->left );
     else if( x > t->element1 )
          remove( x, t->right );
     else if( t->left != NULL && t->right != NULL ) // Two children
     {
          t->element1 = findMin( t->right )->element1;
          remove( t->element1, t->right );
     }
     else
     {
         AvlNode<Comparable_1, Comparable_2> *oldNode = t;
         t = ( t->left != NULL ) ? t->left : t->right;
         oldNode -> exist = false;
     }
}

template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::rotateWithLeftChild( AvlNode<Comparable_1, Comparable_2> * & k2 ) const
{
     AvlNode<Comparable_1, Comparable_2> *k1 = k2->left;
     k2->left = k1->right;
     k1->right = k2;
     k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
     k1->height = max( height( k1->left ), k2->height ) + 1;
     k2 = k1;
}

/**
* Rotate binary tree node with right child.
* For AVL trees, this is a single rotation for case 4.
* Update heights, then set new root.
*/
template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::rotateWithRightChild( AvlNode<Comparable_1, Comparable_2> * & k1 ) const
{
     AvlNode<Comparable_1, Comparable_2> *k2 = k1->right;
     k1->right = k2->left;
     k2->left = k1;
     k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
     k2->height = max( height( k2->right ), k1->height ) + 1;
     k1 = k2;
}

/**
* Double rotate binary tree node: first left child.
* with its right child; then node k3 with new left child.
* For AVL trees, this is a double rotation for case 2.
* Update heights, then set new root.
*/
template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::doubleWithLeftChild( AvlNode<Comparable_1, Comparable_2> * & k3 ) const
{
     rotateWithRightChild( k3->left );
     rotateWithLeftChild( k3 );
}

/**
* Double rotate binary tree node: first right child.
* with its left child; then node k1 with new right child.
* For AVL trees, this is a double rotation for case 3.
* Update heights, then set new root.
*/
template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::doubleWithRightChild( AvlNode<Comparable_1, Comparable_2> * & k1 )const
{
     rotateWithLeftChild( k1->right );
     rotateWithRightChild( k1 );
}

template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::makeEmpty( )
{
     makeEmpty( root );
     
}

template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::makeEmpty( AvlNode<Comparable_1, Comparable_2> * & t )
{
     if (t != NULL)
     {
     	makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
     }
     t = NULL;
}

template <typename Comparable_1, typename Comparable_2>
AvlTree<Comparable_1, Comparable_2>::~AvlTree(  )
{
    makeEmpty( root );
}


template <typename Comparable_1, typename Comparable_2>
const AvlTree<Comparable_1, Comparable_2> AvlTree<Comparable_1, Comparable_2>::operator=( const AvlTree & rhs )
{
    if (this != &rhs) {
	makeEmpty();
	root = clone(rhs.root);
    }
    return *this;
}

template <typename Comparable_1, typename Comparable_2>
void AvlTree<Comparable_1, Comparable_2>::clone( AvlNode<Comparable_1, Comparable_2> * & t )
{
     if ( t == NULL )
        return NULL;
     else
         return new AvlNode<Comparable_1, Comparable_2> (t->element1, t->element2, t->left, t->right, t->height, t->exist);
}

template <typename Comparable_1, typename Comparable_2>
bool AvlTree<Comparable_1, Comparable_2>::operator< ( const AvlTree & rhs )
{
     if (this->element2 > rhs->element2){return true;}
     else{ return false;}
}

template <typename Comparable_1, typename Comparable_2>
bool AvlTree<Comparable_1, Comparable_2>::operator== ( const AvlTree & rhs )
{
     return this->element1 == rhs.element1 && this->element2 == rhs.element2;
}

template <typename Comparable_1, typename Comparable_2>
bool AvlTree<Comparable_1, Comparable_2>::operator!= ( const AvlTree & rhs )
{
          return !(this->element1 == rhs.element1) || !(this->element2 == rhs.element2);
}

template <typename Comparable_1, typename Comparable_2> class BinarySearchTree;

template <typename Comparable_1, typename Comparable_2>
class BinaryNode
{
      Comparable_1 element1; // sequence
      Comparable_2 element2; // enzy
      BinaryNode *left;
      BinaryNode *right;
      int height;
      bool exist;
      BinaryNode( const Comparable_1 & theElement1, const Comparable_2 & theElement2, BinaryNode *lt, BinaryNode *rt , int h = 0, bool ex = false): 
	  element1( theElement1 ),element2( theElement2 ), left( lt ), right( rt ), height(h), exist( ex ) { }
      friend class BinarySearchTree<Comparable_1, Comparable_2>;
};

template <typename Comparable_1, typename Comparable_2>
class BinarySearchTree
{
      public:
             BinarySearchTree(): root ( NULL ) { }
             ~BinarySearchTree( );
             void makeEmpty( );
             explicit BinarySearchTree( const Comparable_1 & notFound );
             BinarySearchTree( const BinarySearchTree & rhs );
             bool isEmpty( ) const;
             int height( ) const;
//             void insert( const Comparable_1 & x );
             void insert( const Comparable_1 & x , const Comparable_2 y);
             const Comparable_1 & findMin( ) const;
             const Comparable_1 & findMax( ) const;
             const Comparable_1 & find( const Comparable_1 & x ) const;
             const Comparable_1 & find( const Comparable_1 & x, const Comparable_2 y ) const;
             bool findEnzyme( const Comparable_1 & x, const Comparable_2 y ) const;
             const int & printNodeNumber( ) const;
             void print (const int order) const;
             const int & printDepth( ) const;
             void remove( const Comparable_1 & x );
             void lazydeletion ( const Comparable_1 & x);
             void stats(double &avgd, int &height);
             bool operator< ( const BinarySearchTree & rhs );
             const BinarySearchTree operator=( const BinarySearchTree & rhs );
             bool operator==( const BinarySearchTree & rhs );
             bool operator!=( const BinarySearchTree & rhs );
             
      private:
              BinaryNode<Comparable_1, Comparable_2> *root;
              const Comparable_1 ITEM_NOT_FOUND;
              const Comparable_1 & elementAt( BinaryNode<Comparable_1, Comparable_2> *t ) const;
//              void insert( const Comparable_1 & x, BinaryNode<Comparable_1, Comparable_2> * & t ) const;
              void insert( const Comparable_1 & x, const Comparable_2 y , BinaryNode<Comparable_1, Comparable_2> * & t ) const;
              BinaryNode<Comparable_1, Comparable_2> * findMin( BinaryNode<Comparable_1, Comparable_2> *t ) const;
              BinaryNode<Comparable_1, Comparable_2> * findMax( BinaryNode<Comparable_1, Comparable_2> *t ) const;
              BinaryNode<Comparable_1, Comparable_2> *
              find( const Comparable_1 & x, BinaryNode<Comparable_1, Comparable_2> *t ) const;
              BinaryNode<Comparable_1, Comparable_2> *
              find( const Comparable_1 & x, const Comparable_2 y, BinaryNode<Comparable_1, Comparable_2> *t ) const;
              bool findEnzyme( const Comparable_1 & x, const Comparable_2 y, BinaryNode<Comparable_1, Comparable_2> *t ) const;
              const int * printNodeNumber( BinaryNode<Comparable_1, Comparable_2> * & t ) const;
              const int * printDepth( BinaryNode<Comparable_1, Comparable_2> * t ) const;
              void printPre(BinaryNode<Comparable_1, Comparable_2> * t ) const;	// internal: preorder print
              void printIn(BinaryNode<Comparable_1, Comparable_2> * t ) const;	// internal: inorder print
              void printPost(BinaryNode<Comparable_1, Comparable_2> * t ) const;	// internal: postorder print
              void remove( const Comparable_1 & x, BinaryNode<Comparable_1, Comparable_2> * & t );
              void lazydeletion( const Comparable_1 & x, BinaryNode<Comparable_1, Comparable_2> * & t );
              void clone( BinaryNode<Comparable_1, Comparable_2> * & t );
              void makeEmpty( BinaryNode<Comparable_1, Comparable_2> * & t  );
              void stats( int &nnodes, int cdepth, int &tdepth, int &mdepth, BinaryNode<Comparable_1, Comparable_2> * & t );
              int max( int lhs, int rhs ) const;
              int height( BinaryNode<Comparable_1, Comparable_2> *t ) const;
};

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 & BinarySearchTree<Comparable_1, Comparable_2>::
elementAt( BinaryNode<Comparable_1, Comparable_2> *t ) const
{
           return t == NULL ? ITEM_NOT_FOUND : t->element1;
}

template <typename Comparable_1, typename Comparable_2>
BinarySearchTree<Comparable_1, Comparable_2>::BinarySearchTree( const BinarySearchTree & rhs)
{
	root = new BinaryNode<Comparable_1,Comparable_2> (rhs->element1, rhs->element2, rhs->left, rhs->right, rhs->height, rhs->exist);
}
	
template <typename Comparable_1, typename Comparable_2>
bool BinarySearchTree<Comparable_1, Comparable_2>::isEmpty( ) const
{
     if (root == NULL){return true;}
     else if (root != NULL){return false;}
     else {return false;}
}

template <typename Comparable_1, typename Comparable_2>
int BinarySearchTree<Comparable_1, Comparable_2>::max( int lhs, int rhs ) const
{
    if (lhs < rhs) 
       return rhs;
    return lhs;
}

template <typename Comparable_1, typename Comparable_2>
int BinarySearchTree<Comparable_1, Comparable_2>::height( ) const
{
    return height ( root );
}

template <typename Comparable_1, typename Comparable_2>
int BinarySearchTree<Comparable_1, Comparable_2>::height( BinaryNode<Comparable_1, Comparable_2> *t ) const
{
    if (t == NULL) {
          return -1;}
    else {
         return t->height;}
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::insert( const Comparable_1 & x, const Comparable_2 y )
{
     insert( x, y, root );
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::insert( const Comparable_1 & x, const Comparable_2 y , BinaryNode<Comparable_1, Comparable_2> * & t ) const
{
     if( t == NULL )
         t = new BinaryNode<Comparable_1, Comparable_2>( x, y, NULL, NULL );
     else if( x < t->element1 )
          insert( x, y, t->left );
     else if( x > t->element1 )
          insert( x, y, t->right );
     else // ( x == > t->element1 )
          t->element2.insert( t->element2.end(), y.begin(), y.end() );
          t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 & BinarySearchTree<Comparable_1, Comparable_2>::find( const Comparable_1 & x ) const
{
      return elementAt( find( x, root ) );
}

template <typename Comparable_1, typename Comparable_2>
BinaryNode<Comparable_1, Comparable_2> *BinarySearchTree<Comparable_1, Comparable_2>:: find( const Comparable_1 & x,BinaryNode<Comparable_1, Comparable_2> *t ) const
{
                       if( t == NULL )
                           return NULL;
                       else if( x < t->element1 )
                            return find( x, t->left );
                       else if( x > t->element1 )
                            return find( x, t->right );
                       else if( t->exist == false )
                       { // lazydeletion
                            std::cout << x << " is not exist in the list.\n";
                            return NULL;
                       }     
                       else // find the key node
                           return t; // Match
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 & BinarySearchTree<Comparable_1, Comparable_2>::find( const Comparable_1 & x, const Comparable_2 y ) const
{
      return elementAt( find( x, y, root ) );
}

template <typename Comparable_1, typename Comparable_2>
BinaryNode<Comparable_1, Comparable_2> *BinarySearchTree<Comparable_1, Comparable_2>:: find( const Comparable_1 & x, const Comparable_2 y, BinaryNode<Comparable_1, Comparable_2> *t ) const
{
                       if( t == NULL )
                           return NULL;
                       else if( x < t->element1 )
                            return find( x, t->left );
                       else if( x > t->element1 )
                            return find( x, t->right );
                       else if( t->exist == false ) // for lazydeletion
                       {
                            return NULL;
                       }     
                       else // find the key node and looking for the new enzyme
                       {
                            for (std::vector<int>::iterator it = t->element2.begin() ; it != t->element2.end(); ++it)
                            {
                                 if ( *it == y ) 
                                 {
                                      return t; // Match
                                 }
                                 else
                                 {
                                     return NULL;
                                 }
                            }
                       }
}

template <typename Comparable_1, typename Comparable_2>
bool BinarySearchTree<Comparable_1, Comparable_2>::findEnzyme( const Comparable_1 & x, const Comparable_2 y ) const
{
      return  findEnzyme( x, y, root );
}

template <typename Comparable_1, typename Comparable_2>
bool BinarySearchTree<Comparable_1, Comparable_2>::findEnzyme( const Comparable_1 & x, const Comparable_2 y, BinaryNode<Comparable_1, Comparable_2> *t ) const
{
    if( t == NULL )
       return false;
    else if( t->exist == false ) // for lazydeletion
    {
        return false;
    }
    else if( x < t->element1 )
        return find( x, t->left );
    else if( x > t->element1 )
        return find( x, t->right );
    else // find the key node and start looking for the new enzyme
    {
        if ( t->element2 == y )
        {
           return true; // found
        }
    }
    
    return false;
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 & BinarySearchTree<Comparable_1, Comparable_2>::findMin( ) const
{
      return elementAt( findMin( root ) );
}

template <typename Comparable_1, typename Comparable_2>
BinaryNode<Comparable_1, Comparable_2> *BinarySearchTree<Comparable_1, Comparable_2>::findMin( BinaryNode<Comparable_1, Comparable_2> *t ) const
{
                       if( t == NULL )
                           return NULL;
                       if( t->left == NULL )
                           return t;
                       return findMin( t->left );
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 & BinarySearchTree<Comparable_1, Comparable_2>::findMax( ) const
{
      return elementAt( findMin( root ) );
}

template <typename Comparable_1, typename Comparable_2>
BinaryNode<Comparable_1, Comparable_2> *BinarySearchTree<Comparable_1, Comparable_2>::findMax( BinaryNode<Comparable_1, Comparable_2> *t ) const
{
                       if( t == NULL )
                           return NULL;
                       if( t->right == NULL )
                           return t;
                       return findMin( t->right );
}

template <typename Comparable_1, typename Comparable_2>
const int & BinarySearchTree<Comparable_1, Comparable_2>::printNodeNumber( ) const
{
      return printNodeNumber ( root );
}

template <typename Comparable_1, typename Comparable_2>
const int *BinarySearchTree<Comparable_1, Comparable_2>::printNodeNumber( BinaryNode<Comparable_1, Comparable_2> * & t ) const
{
      if (t!=NULL)
      {
                 int r,l;
                 r = printNodeNumber(t->right);
                 l = printNodeNumber(t->left);
                 return r+l+1;
      }
      else
      {
          return 0;
      }
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::print (const int order) const
{
     if (order < 1) printPre(root);
     else if (order == 1) printIn(root);
     else printPost(root);
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::printPre(BinaryNode<Comparable_1, Comparable_2> * t) const
{
    if (t == NULL) 
       return;			
    std::cout << t->element2
    	 << t->element1;			// print the key
    if (t->exist) 
       std::cout << " [d]" << std::endl;		// (if deleted)
    if (t->left != NULL)
        printPre(t->left);				// then the left subtree
    if (t->right != NULL)
        printPre(t->right);				// then the right subtree
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::printPost(BinaryNode<Comparable_1, Comparable_2> * t) const
{
    if (t == NULL) 
       return;	
	if (t->left != NULL)		
    	printPost(t->left);			// print the left subtree
    if (t->right != NULL)
    	printPost(t->right);		// then the right subtree
    std::cout << t->element2
    	 << t->element1;			// print the key
    if (t->exist) 
       std::cout << " [d]" << std::endl;		// (if deleted)
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::printIn(BinaryNode<Comparable_1, Comparable_2> * t) const
{
    if (t == NULL) 
       return;			 
    if (t->left != NULL)
		printIn(t->left);			// print the left subtree
    std::cout << t->element2
    	 << t->element1;			// print the key
    if (t->exist) 
       std::cout << " [d]" << std::endl;		// (if deleted)
    if (t->right != NULL)
		printIn(t->right);			// then the right subtree
}

template <typename Comparable_1, typename Comparable_2>
const int & BinarySearchTree<Comparable_1, Comparable_2>::printDepth( ) const
{
      return printDepth ( root );
}

template <typename Comparable_1, typename Comparable_2>
const int *BinarySearchTree<Comparable_1, Comparable_2>::printDepth( BinaryNode<Comparable_1, Comparable_2> * t ) const
{
    if ( t != NULL )
    {
                int r, l;
                r = printDepth( t->right );
                l = printDepth( t->left );
                if ( r > l )
                {
                        return r + 1;
                }
                else
                {
                    return l + 1;
                }
    }
    return 0;
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::remove( const  Comparable_1 &x )
{
      remove ( x , root );
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::remove( const  Comparable_1 &x, BinaryNode<Comparable_1, Comparable_2> * & t ) 
{
     if( t == NULL )
         ; // Item not found; do nothing
     if( x < t->element1 )
         remove( x, t->left );
     else if( t->element1 < x )
          remove( x, t->right );
     else if( t->left != NULL && t->right != NULL ) // Two children
     {
          t->element1 = findMin( t->right )->element1;
          remove( t->element1, t->right );
     }
     else
     {
         BinaryNode<Comparable_1, Comparable_2> *oldNode = t;
         t = ( t->left != NULL ) ? t->left : t->right;
         delete oldNode;
     }
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::lazydeletion( const  Comparable_1 &x )
{
	lazydeletion ( x , root );          
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::lazydeletion( const  Comparable_1 &x, BinaryNode<Comparable_1, Comparable_2> * & t ) 
{
     if( t == NULL )
         ; // Item not found; do nothing
     if( x < t->element1 )
         remove( x, t->left );
     else if( x > t->element1 )
          remove( x, t->right );
     else if( t->left != NULL && t->right != NULL ) // Two children
     {
          t->element1 = findMin( t->right )->element1;
          remove( t->element1, t->right );
     }
     else
     {
         BinaryNode<Comparable_1, Comparable_2> *oldNode = t;
         t = ( t->left != NULL ) ? t->left : t->right;
         oldNode -> exist = false;
     }
}

template <typename Comparable_1, typename Comparable_2>
BinarySearchTree<Comparable_1, Comparable_2>::~BinarySearchTree( )
{
    makeEmpty( );
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::makeEmpty( )
{
     makeEmpty( root );
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::makeEmpty( BinaryNode<Comparable_1, Comparable_2> * & t )
{
     if (t != NULL)
     {
     	if (t->left!=NULL)
     		makeEmpty(t->left);
		if(t->right!=NULL)
			makeEmpty(t->right);
		delete t;
     }
     t = NULL;
}

template <typename Comparable_1, typename Comparable_2>
const BinarySearchTree<Comparable_1, Comparable_2> BinarySearchTree<Comparable_1, Comparable_2>::operator=( const BinarySearchTree & rhs )
{
    if (this != &rhs) {
	makeEmpty();
	root = clone(rhs.root);
    }
    return *this;
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::clone( BinaryNode<Comparable_1, Comparable_2> * & t )
{
     if ( t == NULL )
        return NULL;
     else
         return new BinaryNode<Comparable_1, Comparable_2> (t->element1, t->element2, t->left, t->right, t->height, t->exist);
}

template <typename Comparable_1, typename Comparable_2>
bool BinarySearchTree<Comparable_1, Comparable_2>::operator<( const BinarySearchTree & rhs )
{
     if (this->element2 > rhs->element2){return true;}
     else{ return false;}
}

template <typename Comparable_1, typename Comparable_2>
bool BinarySearchTree<Comparable_1, Comparable_2>::operator==( const BinarySearchTree & rhs )
{
     return (this->element1 == rhs.element1) , (this->element2 == rhs.element2);
}

template <typename Comparable_1, typename Comparable_2>
bool BinarySearchTree<Comparable_1, Comparable_2>::operator!=( const BinarySearchTree & rhs )
{
          return !(this->element1 == rhs.element1), !(this->element2 == rhs.element2);
}

template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::stats(double &avgd, int &height)
{
    int nnodes = 0;		// total # of nodes in the tree
    int cdepth = 0;
    int tdepth = 0;		// sum of depths of all nodes in the tree
    int mdepth = -1;	// maximum depth of any node in the tree
    
    stats(nnodes, cdepth, tdepth, mdepth, root);
    height = mdepth;
    if (nnodes > 0) avgd = double(tdepth) / nnodes;
    else avgd = 0.0;
}


template <typename Comparable_1, typename Comparable_2>
void BinarySearchTree<Comparable_1, Comparable_2>::stats( int &nnodes, int cdepth, int &tdepth, int &mdepth, BinaryNode<Comparable_1, Comparable_2> * & t )
{
    if (t != NULL)
    {
	    nnodes++;
	    tdepth += cdepth;
	    if (cdepth > mdepth) mdepth = cdepth;
	    stats(nnodes,cdepth+1,tdepth,mdepth,t->left);
	    stats(nnodes,cdepth+1,tdepth,mdepth,t->right);    
	}
}

template <typename Comparable_1, typename Comparable_2>
class SequenceMap
{
      public:
                 
             Comparable_1 key;     					
			 Comparable_2 value;			
             AvlTree < Comparable_1, Comparable_2 > avl;
             BinarySearchTree < Comparable_1, Comparable_2 > bst;
             SequenceMap(){};
             ~SequenceMap();
             bool isEmpty( ) const;

             void insert(const std::string tree, const Comparable_1 & str ); 
             void insert( const std::string & tree, const Comparable_1 & str, const Comparable_2 & set );
             
             void selectTree( const std::string & tree, const Comparable_1 & str ); 
             // insert one element in one node and build the tree
             
             void selectTree( const std::string & tree, const Comparable_1 & str, const Comparable_2 & set );
			 // this auto insert to the tree with 2 element in the node
			 
             Comparable_1 find(const Comparable_1 & str) const; 
             Comparable_2 find(const Comparable_1 & str, const Comparable_2 & set) const;
             
             const Comparable_1 findMin( ) const;
             const Comparable_1 findMax( ) const;
             bool findEnzyme( const Comparable_1 & x, const Comparable_2 & y ) const;
             const int printNodeNumber( ) const;
             void print (int order) const;
             const int printDepth( ) const;
             void remove( const Comparable_1 & x ) ;
             void lazydeletion ( const Comparable_1 & x) ;
             void stats(double &avgd, int &height);
             void makeEmpty( );
             bool operator< ( const Comparable_1 & rhs );

      private:
              void AVLinsert( const Comparable_1 & str, const Comparable_2 & set );
              void BSTinsert( const Comparable_1 & str, const Comparable_2 & set );
              Comparable_2 merge( const Comparable_2 & set );    // if find() new enzy in the same 
                                                                 // node append it into the set
              void makeEmpty( AvlNode<Comparable_1, Comparable_2> & avl);
              void makeEmpty( BinarySearchTree<Comparable_1, Comparable_2> & bst );
};

template <typename Comparable_1, typename Comparable_2>
bool SequenceMap<Comparable_1, Comparable_2>::isEmpty( ) const
{
     if ( avl.isEmpty( ) )
     {
          if ( bst.isEmpty( ) ){return std::cout << "Both AVL Tree and Binary Search Tree are empty.\n";}
          if ( ! bst.isEmpty( ) ){return std::cout << "AVL Tree is empty. Binary Search Tree is not empty.\n";}
     }
     else
     {
          if ( bst.isEmpty( ) ){return std::cout << "AVL Tree is not empty. Binary Search Tree is empty.\n";}
          if ( ! bst.isEmpty( ) ){return std::cout << "Both AVL Tree and Binary Search Tree are not empty.\n";}
     }
}

template <typename Comparable_1, typename Comparable_2>
void  SequenceMap<Comparable_1, Comparable_2>::insert(const std::string tree, const Comparable_1 & str )
{
	selectTree( tree, str);
}

template <typename Comparable_1, typename Comparable_2>
void  SequenceMap<Comparable_1, Comparable_2>::insert( const std::string & tree, const Comparable_1 & str, const Comparable_2 & set )
{
	selectTree( tree, str, set );
}

template <typename Comparable_1, typename Comparable_2>
void SequenceMap<Comparable_1, Comparable_2>::selectTree( const std::string & tree, const Comparable_1 & str )
{
     if ( (tree == "avl") || (tree == "AVL") )
         AVLinsert( str );
     else if ( (tree == "bst") || (tree == "BST"))
         BSTinsert( str );
     else 
          std::cout << "Wrong Enter.\n";
}

template <typename Comparable_1, typename Comparable_2>
void SequenceMap<Comparable_1, Comparable_2>::selectTree( const std::string & tree, const Comparable_1 & str, const Comparable_2 & set )
{
     if ( (tree == "avl") || (tree == "AVL") )
         AVLinsert( str, set );
     else if ( (tree == "bst") || (tree == "BST"))
         BSTinsert( str, set );
     else 
          std::cout << "Wrong Enter.\n";
}

template <typename Comparable_1, typename Comparable_2>
void SequenceMap<Comparable_1, Comparable_2>::AVLinsert( const Comparable_1 & str, const Comparable_2 & set )
{
    if ( avl.isEmpty( ) )        
    {
        key = str;
        value = set;
        avl.insert( key, value );
	}	
    else                        // check the enzy is duplicated or not
    {
        for( unsigned int i=0; i<set.size( ); i++ )
        {
            if ( avl.findEnzyme( key, set ) ) // if cannot find the enzy in the node
            {
                    merge( set );
                    avl.insert( key, value ); 
            } 
        }  
        // if find the same enzy in the node, do nothing to avoid duplicated.
    }
}

template <typename Comparable_1, typename Comparable_2>
void SequenceMap<Comparable_1, Comparable_2>::BSTinsert( const Comparable_1 & str, const Comparable_2 & set )
{
	if ( bst.isEmpty( ) )        
    {
        key = str;
        value = set;
        bst.insert( key, value );
    }
    else                        // check the enzy is duplicated or not
    {
        for( unsigned int i=0; i<set.size( ); i++ )
        {
            if ( bst.findEnzyme( key, set ) ) // if cannot find the enzy in the node
            {
                 merge( set );
                 bst.insert( key, value ); 
            } 
        }
        // if find the same enzy in the node, do nothing to avoid duplicated.
    }
}

template <typename Comparable_1, typename Comparable_2>
Comparable_2 SequenceMap<Comparable_1, Comparable_2>::merge( const Comparable_2 & set )
{
             value += set;
             return value;
}

template <typename Comparable_1, typename Comparable_2>
Comparable_1 SequenceMap<Comparable_1, Comparable_2>::find(const Comparable_1 & str ) const 
{
	if (! avl.isEmpty()){return avl.find( str );}
	else if (! bst.isEmpty()){return bst.find( str );}
}

template <typename Comparable_1, typename Comparable_2>
Comparable_2 SequenceMap<Comparable_1, Comparable_2>::find(const Comparable_1 & str, const Comparable_2 & set ) const 
{
	if (! avl.isEmpty()){return avl.find( str, set );}	
	else if (! bst.isEmpty()){return bst.find( str, set );
	}
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 SequenceMap<Comparable_1, Comparable_2>::findMin( ) const
{
	if (! avl.isEmpty()){return avl.findMin(  );}
	else if (! bst.isEmpty( ) ){return bst.findMin( );}
}

template <typename Comparable_1, typename Comparable_2>
const Comparable_1 SequenceMap<Comparable_1, Comparable_2>::findMax( ) const
{
	if (! avl.isEmpty()){return avl.findMax(  );}
	else if (! bst.isEmpty( ) ){return bst.findMax( );}
}

template <typename Comparable_1, typename Comparable_2>
bool SequenceMap<Comparable_1, Comparable_2>::findEnzyme( const Comparable_1 & x, const Comparable_2 & y ) const
{
	if (! avl.isEmpty()){return avl.findEnzyme( y );}
	else if (! bst.isEmpty( ) ){return bst.findEnzyme( y );}	
}

template <typename Comparable_1, typename Comparable_2>
bool SequenceMap<Comparable_1, Comparable_2>::operator< ( const Comparable_1 & rhs )
{
     if(this->key > rhs ){return true;}
     else{ return false;}
}

template <typename Comparable_1, typename Comparable_2>
SequenceMap<Comparable_1, Comparable_2>::~SequenceMap( )
{
     if (! avl.isEmpty()){ avl.makeEmpty(); }
     if (! bst.isEmpty()){ bst.makeEmpty(); }
}

template <typename Comparable_1, typename Comparable_2>
const int SequenceMap<Comparable_1, Comparable_2>::printNodeNumber( ) const
{
     if (! avl.isEmpty()){ return avl.printNodeNumber(); }
     if (! bst.isEmpty()){ return bst.printNodeNumber(); }
}
template <typename Comparable_1, typename Comparable_2>
void SequenceMap<Comparable_1, Comparable_2>::print (int order) const
{
     if (! avl.isEmpty()){ avl.print( order ); }
     if (! bst.isEmpty()){ bst.print( order ); }
}
template <typename Comparable_1, typename Comparable_2>
const int SequenceMap<Comparable_1, Comparable_2>::printDepth( ) const
{
     if (! avl.isEmpty()){ return avl.printDepth(  ); }
     if (! bst.isEmpty()){ return bst.printDepth(  ); }	
}
template <typename Comparable_1, typename Comparable_2>
void SequenceMap<Comparable_1, Comparable_2>::remove( const Comparable_1 & x )
{
     if (! avl.isEmpty()){ avl.remove( x ); }
     if (! bst.isEmpty()){ bst.remove( x ); }
}
template <typename Comparable_1, typename Comparable_2>
void SequenceMap<Comparable_1, Comparable_2>::lazydeletion ( const Comparable_1 & x) 
{
     if (! avl.isEmpty()){ avl.lazydeletion( x ); }
     if (! bst.isEmpty()){ bst.lazydeletion( x ); }
}
template <typename Comparable_1, typename Comparable_2>
void SequenceMap<Comparable_1, Comparable_2>::stats(double &avgd, int &height)
{
	 if (! avl.isEmpty()){ avl.stats( avgd, height ); }
     if (! bst.isEmpty()){ bst.stats( avgd, height ); }
}

template <typename Comparable_1, typename Comparable_2>
void SequenceMap<Comparable_1, Comparable_2>::makeEmpty( )
{
     if ( ! avl.isEmpty( ) ){ avl.makeEmpty( );}
     if ( ! bst.isEmpty( ) ){ bst.makeEmpty( );}
}

void command()
{
    std::cout << "?   ==> display this help information" << std::endl;
    std::cout << "d   ==> display average node depth and tree height" << std::endl;
    std::cout << "e   ==> empty the tree" << std::endl;
    std::cout << "l # ==> remove the node containing the given std::string by lazy deletion" << std::endl;
    std::cout << "m   ==> display minimum key in the tree" << std::endl;
    std::cout << "M   ==> display maximum key in the tree" << std::endl;
    std::cout << "p # ==> print the tree:" << std::endl;
    std::cout << "        # < 1 for preorder" << std::endl;
    std::cout << "        # = 1 for inorder" << std::endl;
    std::cout << "        # > 1 for postorder" << std::endl;
    std::cout << "r # ==> remove node containing the given std::string" << std::endl;
    std::cout << "q   ==> quit" << std::endl;
}

int openfail(std::ifstream *fin)
{
    if (!fin)
    {
        std::cout << "file open fail\n";
        system("PAUSE");
        return -1;
    }
    
    return 0;
}

int main( )
{
    std::string tree = "AVL";				 // AVL, BST
    SequenceMap< std::string , std::string > map; 
	std::string sequence;
	std::string enzyme;    
    std::string x;			// movement command
//    char action;		// the action character
//    int p = 0;		    // which tree are we using (0 or 1)
//    double avgd;		// average depth of nodes in tree
//    int height;			// height of tree

    std::cout << "AVL Tree and BS Tree tree program ( with lazy deletion )\n\n" ;
    
    std::ifstream fin( "/Archive2/5e/39b9c8d616ffd4/main.cpp" ); 
    openfail(&fin);		
    while( true ) 
    {
		while ( ! fin.eof( ) )
	    {			
	        if ( fin.peek( ) == '/' )
	        {
	        	fin.get();		// skip "/" and move ptr to next sequence
	            while ( fin.peek() != '\n' ) 
	            {
	            	getline(fin, sequence, '/');
					std::cout << "enzyme: " << enzyme << std::endl;
					std::cout << "sequence: " << sequence << std::endl;
					map.insert(tree, sequence, enzyme);
					sequence.clear();
					fin.get();	// skip "/" and move ptr to next sequence
		            if(fin.peek() == '/')
		            	fin.get();					
	            }
	            fin.get();
	            enzyme.clear();
	        }
	        else // if( enz != '/' )
	        {
	          	enzyme += fin.get( );
	        }

	    }
	}


	
    fin.close();  
	return 0;
}