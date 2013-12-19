#include <iostream>

struct treeNode {
    //both childs are initialized with nullptr 
    treeNode * left{nullptr};
    treeNode * right{nullptr};
	int value;
    treeNode(int value) : value{value} {}//initialize value
    ~treeNode() {//recursive destruction of all linked nodes
        //deleting nullptrs is a no-op (is valid, but does nothing)
        delete left;
        delete right;
    }
};

void insertTreeElement(treeNode * & root, const int value) {
    if (root == nullptr) {
        root = new treeNode{value};//since root is a reference to a pointer, we can fill it
    } else if(value < root->value) {//go left
        insertTreeElement(root->left, value);
    } else if(value > root->value) {//go right
        insertTreeElement(root->right, value);
    }//ignore, if value is already present in tree
}

//the name min is okay, since nobody used our treeNode class before
int min(const treeNode & root) {//you can’t pass nullptrs here
    if (root.left != nullptr) {//more smaller elements
        return min(*root.left);
    } else {//no more smaller elements
        return root.value;
    }
}

void deleteTreeElement(treeNode * & root, const int value) {
    if (root == nullptr) {
        return;
    } else if(value == root->value) {
        if (root->left != nullptr && root->right != nullptr) {
            root->value = min(*root->right);//get and set replacement
            //we only changed the value, links to the childs persist
            deleteTreeElement(root->right, root->value);//remove it from tree
        } else {
            //backup child nodes
            treeNode * left{root->left};
            treeNode * right{root->right};
            //null child pointers to prevent their deletion
            root->left = nullptr;
            root->right = nullptr;
            //delete node
            delete root;
            //set new root
            if (left == nullptr && right == nullptr) {
                root = nullptr;
            } else if (left != nullptr && right == nullptr) {
                root = left;
            } else if (left == nullptr && right != nullptr) {
                root = right;
            }
        }
    } else {//not null and != value
        deleteTreeElement(root->left, value);
        deleteTreeElement(root->right, value);
    }
}

std::ostream & operator<<(std::ostream & out, const treeNode * const root) {
    if (root == nullptr) {
        return out << " ";//indicate, that there could be an element
    } else if (root->left == nullptr && root->right == nullptr) {
        return out << root->value;//print only root if there are no childs
    } else {//if there is at least one child, print them recursively
        return out << root->value << '{' << root->left << ',' << root->right << '}';
    }
}

void binarySearchTreeTest() {
    treeNode * root{nullptr};
	for (const auto & elem : {5,1,3,2,4,8,6,9,7}) {
        insertTreeElement(root, elem);
        std::cout << root << '\n';
	}
    deleteTreeElement(root, 5);
    std::cout << root << '\n';
}

int main() {
    binarySearchTreeTest();
}