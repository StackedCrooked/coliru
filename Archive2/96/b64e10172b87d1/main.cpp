#include <iostream>

struct Tree
{
    int data;
	Tree *left, *right;
};

int Min(int count, Tree *temp)
{
    if (temp == nullptr || count <= 0)
        return count;
        
    if (temp->left != nullptr) {
        count = Min(count, temp->left);
    }
    if (count > 0) {
        count--;
        std::cout << temp->data << ' ';
    }
    if (temp->right != nullptr) {
        count = Min(count, temp->right);
    }
    return count;
}

Tree *insert(Tree *temp , int elm)
{
    if(temp == nullptr)
		temp = new Tree{elm, nullptr, nullptr};
	else if(elm >= temp->data) 
		temp->right = insert(temp->right, elm);
	else temp->left = insert(temp->left, elm);
    
	return temp;
}

int main()
{
    Tree *root = insert(nullptr ,9);
	insert(root,11);
	insert(root,4);
	insert(root,3);
	insert(root,6);
	insert(root,22);
	insert(root,1);
	insert(root,6);
    insert(root,21);
	insert(root,7);
    Min(6, root);
    return 0;
}