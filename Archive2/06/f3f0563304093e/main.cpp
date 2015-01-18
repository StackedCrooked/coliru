#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {
    os << '{';
    for (auto el : vec) { os << el << ','; }
    os << '}';
    return os;
}

/**
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
  */

/* Solution:
  * */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* Make a WorkNode struct for iterative solution */
struct WorkNode {
    TreeNode *t;
    int inl;
    int inr;
    int postl;
    int postr;
    WorkNode(vector<int> &inorder, vector<int> &postorder, int inl, int inr, int postl, int postr) {
        this->t = new TreeNode(postorder[postr]);
        this->inl = inl;
        this->inr = inr;
        this->postl = postl;
        this->postr = postr;
        cout << "+++ rt=" << t->val << " inl=" << inl << " inr=" << inr << " postl=" << postl << " postr=" << postr << endl;
    }
    pair<WorkNode *, WorkNode*> getSubTrees(vector<int> &inorder, vector<int> &postorder) {
        //find this->t->val among inorder, which breaks left and right sub-tree in both traversal list
        WorkNode *lwork=NULL, *rwork=NULL;
        int rtpos;

        for (rtpos=inl; rtpos<=inr; ++rtpos) {
            if (inorder[rtpos]==t->val) { break; }
        }
        if (rtpos<=inr) {
            if (rtpos>=(inl+1)) {
                lwork = new WorkNode(inorder, postorder, inl, rtpos-1, postl, postl+(rtpos-inl-1) );
                t->left = lwork->t;
                cout << "111 t=" << t->val << " add left=" << t->left->val << endl;
            }
            if (rtpos<=(inr-1)) {
                rwork = new WorkNode(inorder, postorder, rtpos+1, inr,  postr-(inr-rtpos), postr-1);
                t->right = rwork->t;
                cout << "111 t=" << t->val << " add right=" << t->right->val << endl;
            }
        }
        return make_pair(lwork,rwork);
    }
};

class Solution {
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if (inorder.size()!=postorder.size()) { return NULL; }
        if (inorder.empty() || postorder.empty()) { return NULL; }
        stack<WorkNode *> stk;
        pair<WorkNode *, WorkNode *> lr;
        WorkNode *w = new WorkNode(inorder, postorder, 0, inorder.size()-1, 0, postorder.size()-1);
        TreeNode *rt = w->t;

        stk.push(w);
        while (!stk.empty()) {
            WorkNode *cw = stk.top();
            cout << "3333 stack pop=" << cw->t->val;
            stk.pop();
            cout << "  end" << endl;
            lr = cw->getSubTrees(inorder, postorder);
            if (lr.first != NULL) { stk.push(lr.first);  cout << "3333 push left=" << lr.first->t->val << endl; }
            if (lr.second != NULL) { stk.push(lr.second); cout << "3333 push right=" << lr.second->t->val << endl; }
        }
        return rt;
    }

    //Example: non recurrsive in-order traverse
    void inorderTraverse(TreeNode *root) {
        deque<TreeNode *> trav;
        TreeNode *node=root;
        while (!trav.empty() || node!=NULL) {
            if (node!=NULL) {
                trav.push_front(node);
                node = node->left;
            }
            else{
                node = trav.front();
                trav.pop_front();
                cout << node->val << " ";  //visit node->
                node = node->right;
            }
        }
    }
};


int main()
{
   vector<int> inp   = { 3, 2, 4, 1, 5, 6 };
   vector<int> postp = { 3, 4, 2, 6, 5, 1 };

   Solution sol;
   TreeNode *ret = sol.buildTree(inp, postp);
   cout << "finished buildTree" << endl;
   //sol.inorderTraverse(ret);
   cout << endl;
   return 0;
}

