#include <iostream>
#include <vector>
#include <stack>
#include <deque>

using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {
    os << '{';
    for (auto el : vec) { os << el << ','; }
    os << '}';
    return os;
}

/**
 Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
  */
/* Solution:
  * */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    void recoverTree(TreeNode *root) {
        if (root==NULL) { return; }
        stack<TreeNode *> st;
        TreeNode *node=root;
        int preval = std::numeric_limits<int>::min();
        int found = 0;
        int curval;
        TreeNode *pn=NULL, *qn=NULL, *pren;

        while (!st.empty() || node!=NULL) {
            if (node!=NULL) {
                st.push(node);
                node = node->left;
            }
            else{
                node = st.top();
                st.pop();
                    //cout << "  " << node->val;
                curval = node->val;
                if (curval<preval) {
                    if (found==0) {
                        pn = pren;
                        found++;
                    }
                    if (found==1) {
                        qn = node;
                        found++;
                    }
                }
                preval = curval;
                pren = node;

                node = node->right;
            }
        }

        if (pn!=NULL && qn!=NULL) {
            curval=pn->val; pn->val=qn->val; qn->val=curval;
        }
    }
};


int main()
{
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(3);
    root->right = new TreeNode(1);

   Solution sol;
   sol.recoverTree(root);

   return 0;
}

