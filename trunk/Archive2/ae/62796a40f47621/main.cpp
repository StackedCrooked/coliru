#include <iostream>
#include <string>
#include <vector>
#include <queue>

typedef struct NODE
{
    int num;
    NODE *left;
    NODE *right;
} NODE;


void insert(NODE* &root, int num)
{
    if(!root)
    {
        root = new NODE();
        root->num = num;
        return;
    }
    
    if(num < root->num) //Left subTree//
    {
        insert(root->left, num);
    }
    else
    {
        insert(root->right, num);   
    }
}


void inOrderTraversal(NODE *root)
{
    if(!root) return;
    
    inOrderTraversal(root->left);
    std::cout<<root->num<<" ";
    inOrderTraversal(root->right);
}


void preOrderTraversal(NODE *root)
{
    if(!root) return;
    
    std::cout<<root->num<<" ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}


void PrintEachRow(NODE *root)
{
    //Do a breadth-first search, and add line when the element is smaller than last one.
    std::queue<NODE *> qq;
    qq.push(root);
    int last = 0;
    
    while(!qq.empty())
    {
        NODE *curr = qq.front();
        qq.pop();
        if(curr->num < last) 
            std::cout<<std::endl;
        last = curr->num;    
        std::cout<<curr->num<<" ";
        if(curr->left)
            qq.push(curr->left);
        if(curr->right)
            qq.push(curr->right);
    }
}


int main()
{
    NODE *root;
    insert(root,10);
    insert(root,5);
    insert(root,3);
    insert(root,2);
    insert(root,1);
    insert(root,4);
    insert(root,6);
    insert(root,13);
    insert(root,11);
    insert(root,12);
    insert(root,14);
    inOrderTraversal(root);
    std::cout<<std::endl;
    preOrderTraversal(root);
    std::cout<<std::endl;
    
    PrintEachRow(root);
    std::cout<<std::endl;
}
