struct EmployeeRecord {
    EmployeeRecord* m_pParent;
    EmployeeRecord* m_pLeft;
    EmployeeRecord* m_pRight;

    int getID() {return 0;}
};

EmployeeRecord* LowerBound(EmployeeRecord* node, int ID); //finds node, or node to the _left_
EmployeeRecord* NextDown(EmployeeRecord* node); //finds next right CHILD
EmployeeRecord* PrevDown(EmployeeRecord* node);
EmployeeRecord* NextUpDown(EmployeeRecord* node); //find next right NODE, might be a parent
EmployeeRecord* PrevUpDown(EmployeeRecord* node);
bool IsLeftChild(EmployeeRecord* node);

EmployeeRecord* LowerBound(EmployeeRecord* node, int ID) {
    while(node->getID() != ID) {
        //too high: move left
        if (node->getID() > ID) {
            if (node->m_pLeft == nullptr)
                return PrevUpDown(node);
            node = node->m_pLeft;
        }
        //too low: move right
        if (node->getID() < ID) {
            if (node->m_pRight == nullptr) 
                return node;
            node = node->m_pRight;
        }
    }
    //just right
    return node;
}

EmployeeRecord* NextDown(EmployeeRecord* node) {
    if (node->m_pRight == nullptr)
        return nullptr;
    //move right one
    node = node->m_pRight;
    //then left a bunch
    while(node->m_pLeft != nullptr)
        node = node->m_pLeft;
    return node;
}

EmployeeRecord* PrevDown(EmployeeRecord* node) {
    if (node->m_pLeft == nullptr)
        return nullptr;
    //move left one
    node = node->m_pLeft;
    //then right a bunch
    while(node->m_pRight != nullptr)
        node = node->m_pRight;
    return node;
}

EmployeeRecord* NextUpDown(EmployeeRecord* node) {
    //try child
    EmployeeRecord* next = NextDown(node);
    if (next!=nullptr)
        return next;
    //must be a parent: find parent to right
    while(node->m_pParent && IsLeftChild(node)==false) 
        node = node->m_pParent;
    //if none, return nullptr
    if (node->m_pParent == nullptr)
        return nullptr;
    node = node->m_pParent;
    return node;
}

EmployeeRecord* PrevUpDown(EmployeeRecord* node) {
    //try child
    EmployeeRecord* prev = PrevDown(node);
    if (prev!=nullptr)
        return prev;
    //must be a parent: find parent to left
    while(node->m_pParent && IsLeftChild(node)==true) 
        node = node->m_pParent;
    //if none, return nullptr
    if (node->m_pParent == nullptr)
        return nullptr;
    node = node->m_pParent;
    return node;
}

bool IsLeftChild(EmployeeRecord* node) {
    if (node->m_pParent==nullptr)
        return true;
    bool res = node->m_pParent->m_pLeft == node;
    return res;
}

struct EmployeeDatabase {
    EmployeeRecord* m_pRoot;
    bool removeEmployee(int ID);
};

#include <iostream>
using namespace std;

bool EmployeeDatabase::removeEmployee(int ID)
{
    EmployeeRecord* deleteme = LowerBound(m_pRoot, ID);
    if(deleteme == nullptr) // Didn't find the one to delete 
        return false;
    
    //if it has a right-child, swap positions of deleteme and next node to right
    //this shuffles deleteme down in the tree where it has no left child
    EmployeeRecord *replaceWith = NextDown(deleteme);
    if (replaceWith != nullptr) {
        std::swap(deleteme->m_pParent, replaceWith->m_pParent);
        std::swap(deleteme->m_pLeft, replaceWith->m_pLeft);
        std::swap(deleteme->m_pRight, replaceWith->m_pRight);
    }
    
    //the new position is incorrect, but that's ok because we're about to delete the node anyway
    //now link rightchild (if any) and the parent (if any)
    if (deleteme->m_pRight) { //if it has a right child
        //link deleteme's parent to that right child
        if (deleteme->m_pParent == nullptr) {
            m_pRoot = deleteme->m_pRight;
            deleteme->m_pRight->m_pParent = nullptr;
            deleteme->m_pRight = nullptr;
        } else if (IsLeftChild(deleteme)) {
            deleteme->m_pParent->m_pLeft = deleteme->m_pRight;
            deleteme->m_pRight->m_pParent = deleteme->m_pParent;
            deleteme->m_pRight = nullptr;
        } else {
            deleteme->m_pParent->m_pRight = deleteme->m_pLeft;
            deleteme->m_pLeft->m_pParent = deleteme->m_pParent;
            deleteme->m_pRight = nullptr;
        }
    } else { //deleteme has no children
        //remove parent pointer to this
        if (deleteme->m_pParent == nullptr)
            m_pRoot = nullptr;
        else if (IsLeftChild(deleteme))
            deleteme->m_pParent->m_pLeft = nullptr;
        else
            deleteme->m_pParent->m_pRight = nullptr;
    }
    deleteme->m_pParent = nullptr;
    return true;
}

int main() {
}