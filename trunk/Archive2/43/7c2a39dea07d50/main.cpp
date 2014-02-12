#include <vector>

using std::vector;

class Node {
private:
    vector<Node*> children; 
public: 
    vector<Node*>& getChildren() {
        return children;
    }

    void addChild(Node* child) {
        children.push_back(child);
    }
};

void f(Node* root)
{
    vector<Node*>& tmp = root->getChildren(); // intellisense error on 'root' here
}

int main()
{
    Node root;
    Node child1, child2;
    root.addChild(&child1);
    root.addChild(&child2);
    f(&root);   
}