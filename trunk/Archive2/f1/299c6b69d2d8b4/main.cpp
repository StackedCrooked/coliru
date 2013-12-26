#include <iostream>

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

//the name min is okay, since nobody used our treeNode class before
int min(const treeNode & root) {//you can’t pass nullptrs here
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
        if (root->left != nullptr && root->right != nullptr) {
            root->value = min(*root->right);//get and set replacement
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
            //create new root
            if (left == nullptr && right == nullptr) {
                root = nullptr;
            } else if (left != nullptr && right == nullptr) {
                root = left;
            } else if (left == nullptr && right != nullptr) {
                root = right;
            }
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
    deleteTreeElement(root, 5);
    std::cout << root << '\n';
}

int main() {
    binarySearchTreeTest();
}