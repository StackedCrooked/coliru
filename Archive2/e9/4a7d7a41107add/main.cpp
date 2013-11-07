#include <iostream>
#include <string>
#include <vector>
#include <memory>

template <typename T>
struct Tree
{
    Tree(T key, std::shared_ptr<Tree<T>> left, std::shared_ptr<Tree<T>> right): key{key},left{left},right{right} {}
    T key;
    std::shared_ptr<Tree<T>> left;
    std::shared_ptr<Tree<T>> right;
};

template <typename T>
std::shared_ptr<Tree<T>> build_subtree(
    typename std::vector<T>::const_iterator& in_start,
    typename std::vector<T>::const_iterator& post_start,
    typename std::vector<T>::const_iterator& post_end,
    T post_end_val)
{
    std::shared_ptr<Tree<T>> current{nullptr};
    
    while (post_start != post_end && *post_start != post_end_val) {
        if (*in_start == *post_start) {
            current = std::make_shared<Tree<T>>(*in_start, current, nullptr); 
            ++in_start; ++post_start;
        } else {
            int new_stop_val = *in_start++;
            current = std::make_shared<Tree<T>>(new_stop_val, current, 
                build_subtree(in_start, post_start, post_end, new_stop_val));
            ++post_start;
        }
    }
    
    return current;
}

template <typename T>
std::shared_ptr<Tree<T>> build_tree(const std::vector<T>& in,
                                    const std::vector<T>& post)
{
    auto in_start = in.cbegin();
    auto post_start = post.cbegin();
    auto post_end = post.cend();
    
    return build_subtree(in_start, post_start, post_end, -1);
}

template <typename T>
void print_in_order(std::shared_ptr<Tree<T>> tree)
{
    if (tree->left != nullptr) {
        print_in_order(tree->left);
    }
    
    std::cout << tree->key << ' ';
    
    if (tree->right != nullptr) {
        print_in_order(tree->right);
    }
}

template <typename T>
void print_post_order(std::shared_ptr<Tree<T>> tree)
{
    if (tree->left != nullptr) {
        print_post_order(tree->left);
    }
    
    if (tree->right != nullptr) {
        print_post_order(tree->right);
    }
    
    std::cout << tree->key << ' ';
}

int main()
{
    auto tree = build_tree<int>({2,1,5,6,7,3}, {2,1,7,6,5,3});
    
    print_in_order(tree);
    std::cout << std::endl;
    
    print_post_order(tree);
    std::cout << std::endl;
}
