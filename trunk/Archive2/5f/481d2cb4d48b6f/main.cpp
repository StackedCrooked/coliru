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

coro bf(Node *tree) {                                     //def bf(tree):
    return coro([=](auto &yield) {                        //
        vector<Node *> tree_list = {tree};                //    tree_list = [tree]
        while (!tree_list.empty()) {                      //    while tree_list:
            vector<Node *> new_tree_list;                 //        new_tree_list = []
            for (auto tree : tree_list) {                 //        for tree in tree_list:
                if (tree != nullptr) {                    //            if tree is not None:
                    yield(tree->value);                   //                yield tree.value
                    new_tree_list.push_back(tree->left);  //                new_tree_list.append(tree.left)
                    new_tree_list.push_back(tree->right); //                new_tree_list.append(tree.right)
                }                                         //
            }                                             //
            tree_list = move(new_tree_list);              //        tree_list = new_tree_list
        }                                                 //
    });                                                   //
}                                                         //

int main() {
    Node a{'a'}, b{'b'}, c{'c'}, d{'d'}, e{'e'};

    a.left = &b;
    a.right = &c;
    b.right = &d;
    d.left = &e;

    for (auto node_value : bf(&a))
        std::cout << node_value << " ";
}