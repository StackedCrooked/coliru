// This program requires C++11 support
#include <iostream>
#include <cstdlib>
#include <queue>

enum Color {
    RED = 0,
	BLACK = 1
};

struct Node {
	int data;
	bool color;
	Node *leftChild, *rightChild, *parent;
	// Constructor
	explicit Node(int n) : data(n), color(RED), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {} 
};

class RBTree {
	private:
	Node *root;

	public:
	// Constructor
	RBTree() : root(nullptr) {}

	// Functionalities
	void insert(int n);
	void inorder_walk();
	void level_order_walk();
};

void inorder_helper(Node *root) {
	if (root == nullptr)
		return;

	inorder_helper(root->leftChild);
	std::cout << root->data << "  ";
	inorder_helper(root->rightChild);
}

void RBTree::inorder_walk() {
	inorder_helper(root);
}

void RBTree::level_order_walk() {
	if (root == nullptr)
		return;

	std::queue<Node *> q;
	q.push(root);

	while (!q.empty()) {
		Node *temp = q.front();
		std::cout << temp->data << "  ";
		q.pop();

		if (temp->leftChild != nullptr)
			q.push(temp->leftChild);

		if (temp->rightChild != nullptr)
			q.push(temp->rightChild);
	}
}	

void BST_Insert(Node *&root, Node *pt) {
	static Node *prev = nullptr;

	if (root == nullptr) {
		root = pt;
		pt->parent = prev;
	}

	else {
		prev = root;

		if (root->data > pt->data)
			BST_Insert(root->leftChild, pt);

		else if (root->data < pt->data)
			BST_Insert(root->rightChild, pt);
	}
}

void rotate_left(Node *&root, Node *&pt) {
	Node *pt_right = pt->rightChild;

	pt->rightChild = pt_right->leftChild;

	if (pt->rightChild != nullptr)
		pt->rightChild->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == nullptr)
		root = pt_right;

	else if (pt == pt->parent->leftChild)
		pt->parent->leftChild = pt_right;

	else
		pt->parent->rightChild = pt_right;

	pt_right->leftChild = pt;
	pt->parent = pt_right;		
}

void rotate_right(Node *&root, Node *&pt) {
	Node *pt_left = pt->leftChild;

	pt->leftChild = pt_left->rightChild;

	if (pt->leftChild != nullptr)
		pt->leftChild->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == nullptr) 
		root = pt_left;

	else if (pt == pt->parent->leftChild)
		pt->parent->leftChild = pt_left;	

	else
		pt->parent->rightChild = pt_left;

	pt_left->rightChild = pt;
	pt->parent = pt_left;
}

void fix_violation(Node *&root, Node *&pt) {
	Node *parent_pt = nullptr;
	Node *grand_parent_pt = nullptr;

	while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {

		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/**
		* Case : A
		* Parent of pt is left child of Grand-parent of pt
		**/

		if (parent_pt == grand_parent_pt->leftChild) {
			
			Node *uncle_pt = grand_parent_pt->rightChild;
			
			/**
			* Case : 1
			* The uncle of pt is also red
			* Only Recoloring required
			**/

			if (uncle_pt != nullptr && uncle_pt->color == RED) {
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}

			else {

				/**
				* Case : 2
				* pt is right child of its parent
				* Left-rotation required
				**/

				if (pt == parent_pt->rightChild) {
					rotate_left(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/**
				* Case : 3
				* pt is left child of its parent
				* Right-rotation required
				**/

				rotate_right(root, grand_parent_pt);
				std::swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		/**
		* Case : B
		* Parent of pt is right child of Grand-parent of pt
		**/

		else {
			Node *uncle_pt = grand_parent_pt->leftChild;
			
			/**
			* Case : 1
			* The uncle of pt is also red
			* Only Recoloring required
			**/

			if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}

			else {

				/**
				* Case : 2
				* pt is left child of its parent
				* Right-rotation required
				**/

				if (pt == parent_pt->leftChild) {
					rotate_right(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/**
				* Case : 3
				* pt is right child of its parent
				* Left-rotation required
				**/

				rotate_left(root, grand_parent_pt);
				std::swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	root->color = BLACK;
}

void RBTree::insert(int n) {
	Node *pt = new Node(n);

	BST_Insert(root, pt);

	fix_violation(root, pt);
}

int main() {
	// This program requires C++11 support
    #if __cplusplus <= 199711L
	#error C++11 support required !!!
    #endif

	RBTree rb_tree;

	rb_tree.insert(15);
	rb_tree.insert(8);
	rb_tree.insert(10);
	rb_tree.insert(12);
	rb_tree.insert(18);
	rb_tree.insert(25);
	rb_tree.insert(20);

	rb_tree.inorder_walk();
	std::cout <<'\n';
	rb_tree.level_order_walk();

	return 0;
}