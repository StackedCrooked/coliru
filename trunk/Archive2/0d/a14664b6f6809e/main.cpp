void BinarySearchTree::preorder(tree_node* p, int indent=0)
{
    if (indent) 
        std::cout << std::setw(indent) << ' ';
    std::cout << p->data << '\n';
    if (p->left) postorder(p->left, indent);
    if (p->right) postorder(p->right, indent);
}