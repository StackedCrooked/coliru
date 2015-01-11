#include <iostream>
using namespace std;

#define ItemType int  // instead of struct/class ItemType ...
struct BTNode { ItemType info; BTNode* left; BTNode* right; };

class BinarySearchTree {
public: 
  BinarySearchTree( BTNode* tree );
  void InOrderPrint ( );
  void Mirror( );
private:
  void RecursiveInOrderPrint( BTNode* tree );
  void RecursiveMirror( BTNode* tree );
  BTNode* root;
};
BinarySearchTree::BinarySearchTree( BTNode* tree ) { root = tree; }
void BinarySearchTree::InOrderPrint( ) { RecursiveInOrderPrint( root ); cout << endl; }
void BinarySearchTree::RecursiveInOrderPrint( BTNode* tree ) {
  if (tree != NULL) {
    RecursiveInOrderPrint(tree->left);
	cout << " " << tree->info;
	RecursiveInOrderPrint(tree->right);
  }
}
void BinarySearchTree::Mirror( ) { RecursiveMirror( root ); }
void BinarySearchTree::RecursiveMirror( BTNode* tree ) {
  if ( tree == NULL ) return;     // base case
  RecursiveMirror( tree->left );  // general case: mirror the
  RecursiveMirror( tree->right ); // left and right sub-trees
  BTNode* tmpNode = tree->left;   // then swap the
  tree->left = tree->right;       // left-right children
  tree->right = tmpNode; 
}

int main() {
  BTNode *n0 = new BTNode, *n1 = new BTNode, *n2 = new BTNode, *n3 = new BTNode,
     *n4 = new BTNode, *n5 = new BTNode, *n6 = new BTNode; 
  n0->info = 16; n0->left = n1; n0->right = n2;
  n1->info = 12; n1->left = n3; n1->right = NULL;       //        16
  n2->info = 32; n2->left = n4; n2->right = NULL;      //    12      32
  n3->info =  4; n3->left = n5; n3->right = NULL;      //   4      20
  n4->info = 20; n4->left = NULL; n4->right = n6;      //  1        24
  n5->info =  1; n5->left = NULL; n5->right = NULL;
  n6->info = 24; n6->left = NULL; n6->right = NULL;
  BinarySearchTree bst( n0 );

  bst.InOrderPrint( );
  bst.Mirror( );
  bst.InOrderPrint( );
}