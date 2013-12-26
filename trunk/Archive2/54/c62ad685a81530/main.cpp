#include <iostream>
#include <stdexcept>

struct treeNode {
    treeNode * left{nullptr};
    treeNode * right{nullptr};
	int value;
    treeNode(int value) : value{value} {}
    ~treeNode() {
        delete left;
        delete right;
    }
};

void insertTreeElement(treeNode * & root, const int value) {
    if (root == nullptr) {
        root = new treeNode{value};
    } else if(value < root->value) {
        insertTreeElement(root->left, value);
    } else if(value > root->value) {
        insertTreeElement(root->right, value);
    }//ignore, if value is already present in tree
}

//min is okay, since nobody used our treeNode class before
int min(const treeNode & root) {//you cant pass nullptrs here
    if (root.left != nullptr) {
        return min(*root.left);
    } else {
        return root.value;
    }
}

void deleteTreeElement(treeNode * & root, const int value) {
    if (root == nullptr) {
        return;
    } else if(value == root->value) {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->left != nullptr && root->right == nullptr) {
            treeNode * left = root->left;
            root->left = nullptr;
            delete root;
            root = left;
        } else if (root->left == nullptr && root->right != nullptr) {
            treeNode * right = root->right;
            root->right = nullptr;
            delete root;
            root = right;
        } else {
            //backup child nodes
            treeNode * left = root->left;
            treeNode * right = root->right;
            //null child pointers to prevent deletion
            root->left = nullptr;
            root->right = nullptr;
            //delete node
            delete root;
            //create new root
            int substitute{min(*root->right)};//get replacement
            deleteTreeElement(root->right, substitute);//remove from tree
            root = new treeNode{substitute};
            //link childs of previous root
            root->left = left;
            root->right = right;
        }
    } else {
        deleteTreeElement(root->left, value);
        deleteTreeElement(root->right, value);
    }
}

std::ostream & operator<<(std::ostream & out, const treeNode * const root) {
    if (root == nullptr) {
        return out << " ";
    } else if (root->left == nullptr && root->right == nullptr) {
        return out << root->value;
    } else {
        return out << root->value << '{' << root->left << ',' << root->right << '}';
    }
}

void binarySearchTreeTest() {
    treeNode * root{nullptr};
	for (const auto & elem : {5,1,3,2,4,8,6,9,7}) {
        insertTreeElement(root, elem);
        std::cout << root << '\n';
	}
    deleteTreeElement(root, 7);
    std::cout << root << '\n';
}

int main() {
    binarySearchTreeTest();
}