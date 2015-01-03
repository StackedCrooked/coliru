#include <iostream>
#include <vector>

/**
 Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    You may only use constant extra space.
    You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL

  */

/* Solution:
  * */
using namespace std;

struct TreeLinkNode {
 int val;
 TreeLinkNode *left, *right, *next;
 TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root==NULL) { return; }
        TreeLinkNode *leftWall=root, *curn;

        while (leftWall!=NULL) {
            curn = leftWall;
            while (curn!=NULL) {
                if (curn->left!=NULL) { curn->left->next = curn->right; }
                if (curn->right!=NULL) {
                    curn->right->next = (curn->next!=NULL)? curn->next->left : NULL;
                }
                curn = curn->next;
            }
            leftWall = leftWall->left;
        }
        return;
    }
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {
    os << '{';
    for (auto el : vec) { os << el << ','; }
    os << '}';
    return os;
}


int main()
{
   Solution sol;

   return 0;
}


