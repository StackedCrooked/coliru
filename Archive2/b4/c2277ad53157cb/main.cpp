#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <vector>
#include <ctime>

struct node {
    node* parent;
    
    node* left;
    node* right;
    
    int data;
    
    node(int data, node* parent = nullptr) : 
        parent(parent),
    	data(data),
        left(nullptr),
        right(nullptr)
    {}
};


struct bst {
    node* head;
    
private:
    void destroy(node* n) {
        if(!n) {
            return;
        }
        
        destroy(n->left);
        destroy(n->right);
        
        delete n;
    }  
    
public:
    ~bst() {
        destroy(head); 
    }
    
    bst() : head(nullptr) {}
    
////////////
// INSERT //
////////////

private:
    node* insert(int p, node*& n, node* par = nullptr) {
        if(!n) {
            n = new node(p, par);
            return n;
        }
        
        if(p < n->data) {
            return insert(p, n->left, n);
        }
        else {
            return insert(p, n->right, n);
        }
    }
    
public:
    node* insert(int p) {
        return insert(p, head);   
    }
	
////////////
// DELETE //
////////////

public:
	void erase(node* n) {
		//TODO
	}
    
////////////
// LOOKUP //
////////////

private:
    node* find(int p, node* n) {
        if(!n) {
            return nullptr;
        }
        
        if(p < n->data) {
            return find(p, n->left);
        }
        else {
            return find(p, n->right);
        }
    }
    
public:
    node* find(int p) {
        return find(p, head);
    }
};

static std::string print(node* n) {
    std::ostringstream os;
	
	if(!n) {
		return "";
	}
	
	os << n->data;
	
	if(n->left || n->right) {
		os << "[";
		if(n->left)
			os << print(n->left);
		else
			os << "Null";
		
		os << ",";
		
		if(n->right)
			os << print(n->right);
		else
			os << "Null";
		
		os << "]";
	}
	
	return os.str();
}

static void replace(bst& b, node* parent, node* child, node* with) {
	if(!parent) {
		b.head = with;
	}
	else {
		if(parent->left == child)
			parent->left = with;
		else
			parent->right = with;
	}
}

//AVL balancing
namespace AVL {
    static std::pair<int, bool> depth(node* n, bool left = false, int count = 0) {
        if(!n) {
            return std::make_pair(count, left);
        }
        
		bool left_next;
		if(n->parent) {
			if(n->parent->left == n)
				left_next = true;
			else
				left_next = false;
		}
		
		auto left_d = depth(n->left, left_next, count+1);
		auto right_d = depth(n->right, left_next, count+1);
		
        return (left_d.first < right_d.first ? right_d : left_d);
    }
    
    static void single_rotate_left(bst& b, node* k1, node* k2) {
		node* Y = k2->right;
		k1->left = Y; if(Y) { Y->parent = k1; }
		
		k2->parent = k1->parent;
		replace(b, k1->parent, k1, k2);
		
		k2->right = k1; k1->parent = k2;
    }
	
	static void single_rotate_right(bst& b, node* k1, node* k2) {
		node* Y = k2->left;
		k1->right = Y;  if(Y) { Y->parent = k1; }
		
		k2->parent = k1->parent;
		replace(b, k1->parent, k1, k2);
		
		k2->left = k1; k1->parent = k2;
	}
    
	static void double_rotate_left(bst& b, node* k1, node* k2, node* k3) {
		node* B = k2->right;
		node* C = k2->left;
		
		k2->parent = k3->parent;
		replace(b, k3->parent, k3, k2);
		
		k3->right = C;  if(C) { C->parent = k3; }
		k1->left = B; if(B) { B->parent = k1; }
		
		k2->right = k1;  k1->parent = k2;
		k2->left = k3; k3->parent = k2;
    }
	
    static void double_rotate_right(bst& b, node* k1, node* k2, node* k3) {
		node* B = k2->left;
		node* C = k2->right;
		
		k2->parent = k3->parent;
		replace(b, k3->parent, k3, k2);
		
		k3->left = C;  if(C) { C->parent = k3; }
		k1->right = B; if(B) { B->parent = k1; }
		
		k2->left = k1;  k1->parent = k2;
		k2->right = k3; k3->parent = k2;
    }
    
    static void fviol_(bst& b, node* A) {
        if(!A) {
            return;
        }
        
		fviol_(b, A->left);
        fviol_(b, A->right);
		
		std::pair<int, bool> left_depth = depth(A->left);
		std::pair<int, bool> right_depth = depth(A->right);
		
		if(std::abs(left_depth.first - right_depth.first) > 1) { //imbalance
			if(left_depth.first > right_depth.first) { //left subtree
				if(left_depth.second) { //left child
					node* k1 = A;
					node* k2 = A->left;
					std::cout << "Left-Left: Performing left child single rotate on subtree: " << print(A) << " with k1=" << k1->data << " k2=" << k2->data << std::endl;
					single_rotate_left(b, k1, k2);
				}
				else { //right child
					node* k1 = A->left; 
					node* k2 = k1->right;
					node* k3 = A;
					std::cout << "Left-Right: Performing right child double rotate on subtree: " << print(A) << " with k1=" << k1->data << " k2=" << k2->data << " k3=" << k3->data << std::endl;
					double_rotate_right(b, k1, k2, k3);
				}
			}
			else {	//right subtree
				if(right_depth.second) { //left child
					node* k1 = A->right; 
					node* k2 = k1->left;
					node* k3 = A;
					std::cout << "Right-Left: Performing left child double rotate on subtree: " << print(A) << " with k1=" << k1->data << " k2=" << k2->data << " k3=" << k3->data << std::endl;
					double_rotate_left(b, k1, k2, k3);
				}
				else { //right child
					node* k1 = A;
					node* k2 = A->right;
					std::cout << "Right-Right: Performing right child single rotate on subtree: " << print(A) << " with k1=" << k1->data << " k2=" << k2->data << std::endl;
					single_rotate_right(b, k1, k2);
				}
			}
		}
    }
    
    static void balance(bst& b) {
        fviol_(b, b.head);
    }
}

int main() {
	std::vector<int> set = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	
    bst b;
    for(int i : set) {
		std::cout << "Inserting #" << i;
        b.insert(i);
		std::cout << ": " << print(b.head) << std::endl;
		
		AVL::balance(b);		
		
		std::cout << "Tree: " << print(b.head) << std::endl;
	}
	
	std::cout << "Final: "<< print(b.head) << std::endl;
	
    return 0;
}