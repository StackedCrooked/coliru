/* bst.h */
#include <iosfwd>
#include <functional>

template<typename T>
class BST
{
private:
    struct node {
        T val;
        node* left;
        node* right;
        
        node(T const& v) : val(v), left(nullptr), right(nullptr) {};
        ~node() { delete left; delete right; };
    };
    node* head;
    bool isChild;
    
    BST(node* const n) : head(n), isChild(true) {};
public:
    BST() : head(nullptr), isChild(false) {};
    ~BST() { if(!isChild) delete head; };

    void insert(T const& v) {
        if(head == nullptr) {
            head = new node(v);
        } else if(v < head->val) {
            if(head->left == nullptr)
                head->left = new node(v);
            else
                BST(head->left).insert(v);
        } else {
            if(head->right == nullptr)
                head->right = new node(v);
            else
                BST(head->right).insert(v);
        }
    };
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const BST<U>& t);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const BST<T>& t) {
    using node = typename BST<T>::node;

    std::function<void(const int, const node* const)> recurse
    = [&](const int d, const node* const n) {
        if(n == nullptr) return;
        recurse(d + 1, n->left);
        os << std::string(d, '-') << n->val << '\n';
        recurse(d + 1, n->right);
    };
    
    recurse(0, t.head);
    
    return os;
}


/* bst_test.cpp */
#include <cstdlib>
#include <iostream>
//#include "bst.h"

int main() {
    BST<int> t;

    // seed random number generator so we get the same output every time
    std::srand(0);
    
    // insert 10 random numbers
    for(int i = 0; i < 10; i++) {
        t.insert(std::rand() % 100);
    }
    
    // output tree, and see whether or not it's correct
    std::cout << t;
    
    return 0;
}