#include <vector>
#include <iostream>
#include <boost/coroutine/all.hpp>

using namespace std;

struct Node {
    char value;
    Node *left;
    Node *right;
};

using coro =
    boost::coroutines::asymmetric_coroutine<decltype(Node::value)>::pull_type;

coro bf(Node *tree) {
    return coro([&](auto &yield) {
        vector<Node *> tree_list = {tree};
        while (!tree_list.empty()) {
            vector<Node *> new_tree_list;
            for (auto tree : tree_list) {
                if (tree != nullptr) {
                    yield(tree->value);
                    new_tree_list.push_back(tree->left);
                    new_tree_list.push_back(tree->right);
                }
            }
            tree_list = move(new_tree_list);
        }
    });
}

int main() {
    Node a{'a'}, b{'b'}, c{'c'}, d{'d'}, e{'e'};

    a.left = &b;
    a.right = &c;
    b.right = &d;
    d.left = &e;

    for (auto node_value : bf(&a))
        std::cout << node_value << " ";
}