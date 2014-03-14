#include <iostream>
#include <cassert>
#include <string>

using namespace std;

struct SBL_Node{
    string name;
    SBL_Node* left, * right;
    SBL_Node* next;
};

typedef SBL_Node* BST;

struct Queue { 
    BST first; 
    BST last; 
};

struct SBL{
    BST root;
    Queue q;
    int size;
};

void SBL_init (SBL& sbl){
    sbl.root = NULL;
    sbl.q.first = NULL;
    sbl.q.last = NULL;
    sbl.size = 0;
}

bool SBL_empty (const SBL& sbl){
    return sbl.size==0;
}

int SBL_size (const SBL& sbl){
    return sbl.size;
}

BST BST_lookup (string key, const BST& curNode) {
    if (NULL == curNode) {
        return NULL;
    }else if (key == curNode->name){
        return curNode;
    }
    else if (key < curNode->name) {
        return BST_lookup(key, curNode->left);
    }else{
        return BST_lookup(key, curNode->right);
    }
}

BST BST_insert (string key, BST& curNode) {
    if (curNode == NULL) {
        curNode = new SBL_Node;
        curNode->name = key;
        curNode->left = NULL;
        curNode->right = NULL;
        curNode->next = NULL;
    }else if (key == curNode->name) {
        cerr << "duplicate key: " << key << endl;
        assert(false);
        } else if (key < curNode->name) {
            curNode->left = BST_insert(key,curNode->left);
    }else {
        curNode->right = BST_insert(key,curNode->right);
    }
    return curNode;
}

void SBL_arrive (string name, SBL& sbl){
	if (sbl.size == 0){
		sbl.root = BST_insert(name, sbl.root);
		sbl.root->next = NULL;
		sbl.q.first = sbl.root;
		sbl.q.last = sbl.root;
	}else{
		BST_insert(name, sbl.root);
		BST temp = BST_lookup (name, sbl.root);
		sbl.q.last->next = temp;
		sbl.q.last = temp;
	}
	sbl.size++;
}

string SBL_first (const SBL& sbl){
    return sbl.q.first->name;
}

BST BST_parentLookup (string key, const BST& curNode) {
	if (curNode == NULL || key == curNode->name){
		assert(false);
	}
	if (curNode->left!=NULL){
		if (curNode->left->name==key){
			return curNode;
		}
	}
	if (curNode->right!=NULL){
		if (curNode->right->name==key){
			return curNode;
		}
	}
    if (key < curNode->name) {
        return BST_parentLookup(key, curNode->left);
    }else{
        return BST_parentLookup(key, curNode->right);
    } 
}


void BST_delete(string key, BST & root) { //remove
    BST temp = BST_lookup(key, root);
    if (temp == NULL){
        return;
    }
    if (temp->left == NULL && temp->right == NULL){
        if (root == temp){
            delete root;
            root = NULL;
            return;
        }
        BST temp2 = BST_parentLookup(key, root);
        if (temp2->right == temp){
            temp2->right = NULL;
        }else{
            temp2->left = NULL;
        }
        delete temp;
    }else if (temp->left == NULL || temp->right == NULL){
        BST temp2;
        if (temp->left==NULL){
            temp2 = temp->right;
        }else{
            temp2 = temp->left;
        }
		if (temp == root){
			root = temp2;
			delete temp;
			return;
		}else{
			BST parent = BST_parentLookup(key, root);
			if (parent->right == temp){
				parent->right = temp2;
			}else{
				parent->left = temp2;
			}
			delete temp;
		}
    }else{
        BST temp2 = temp->left;
        BST temp3=NULL;
        while(temp2->right!=NULL){
            if (temp2->right->right == NULL){
                temp3 = temp2;
            }
            temp2 = temp2->right;
            
        }
        if (temp2 == temp->left){
            root = temp2;
            temp2->right = temp->right;
            delete temp;
            return;
        }
		if (temp2->left!=NULL){
			temp3->right = temp2->left;
		}
		temp2->left = temp->left;
		temp2->right = temp->right;
		if (temp == root){
			root = temp2;
		}else{
			BST parent = BST_parentLookup(key, root);
			if (parent->left!=NULL && parent->left == temp){
				parent->left = temp2;
			}else{
				parent->right = temp2;
			}
		}
        delete temp;
    }
}

void SBL_leave (SBL& sbl){
	if (sbl.size == 1){
		delete sbl.q.first;
		sbl.q.first = NULL;
		sbl.q.last = NULL;
		sbl.root = NULL;
	}
	else{
		string x = SBL_first(sbl);
		sbl.q.first = sbl.q.first->next;
		BST_delete(x, sbl.root);
	}
    sbl.size--;
}

bool SBL_lookup (const SBL& sbl, string name){
    if (SBL_empty(sbl)){
        return false;
    }
    BST temp = BST_lookup (name, sbl.root);
    if (NULL == temp){
        return false;
    }else{
        return true;
    }
}

void BST_print(const BST& curNode){
    if(curNode != NULL){
        BST_print(curNode->left);
        cout<<curNode->name<< endl;
        BST_print(curNode->right);
    }
}

void SBL_printInArrivalOrder (const SBL& sbl){
    if (SBL_empty(sbl)){
        return;
    }
	BST temp = sbl.q.first;
	while (temp!=NULL){
		cout << temp -> name << endl;
        temp = temp -> next;
	}
}

void SBL_printInAlphabeticalOrder (const SBL& sbl){
    if (!SBL_empty(sbl)){
        BST_print(sbl.root);
    }
}

int main () {
    SBL sbl;
    SBL_init(sbl);
    SBL_arrive("cat", sbl);
    SBL_arrive("dat", sbl);
    SBL_arrive("car", sbl);
    SBL_arrive("cas", sbl);
    SBL_arrive("bob", sbl);
    SBL_arrive("but", sbl);
    SBL_arrive("apple", sbl);
    SBL_arrive("aaahh", sbl);
    SBL_arrive("dog", sbl);
    SBL_arrive("dan", sbl);
    SBL_arrive("elephant", sbl);
    SBL_arrive("ear", sbl);
    SBL_arrive("tv", sbl);

    SBL_leave(sbl);
    SBL_printInArrivalOrder(sbl);
    SBL_leave(sbl);
    SBL_printInArrivalOrder(sbl);
    SBL_leave(sbl);
    SBL_printInArrivalOrder(sbl);
    SBL_leave(sbl);
    SBL_printInArrivalOrder(sbl);
    SBL_leave(sbl);
    SBL_leave(sbl);
    SBL_leave(sbl);
    SBL_leave(sbl);
    SBL_leave(sbl);
    SBL_leave(sbl);
    SBL_leave(sbl);
    SBL_leave(sbl);
    SBL_printInArrivalOrder(sbl);
    SBL_leave(sbl);
}
    
    
    
    