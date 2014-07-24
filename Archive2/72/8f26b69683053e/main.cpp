#include <iostream>
#include <string>
#include <vector>

#include <iostream>
#include <cassert>

/**
 * 1. Single Linked List (ForwardList)
 */

// T should be copyable, comparable (==)
// cannot be derived

template <typename T>
class ForwardList final {
private:
    struct Node {
        T data;
        Node* next;
    };
public:
    ForwardList():
        m_pRoot(nullptr)
    {}
    ~ForwardList() { clearList(); }
    ForwardList(const ForwardList&) = delete;
    ForwardList(const ForwardList&&) = delete;
    ForwardList& operator=(const ForwardList&) = delete;

    Node* createNode() const
    {
        Node* pNode = new Node();
        return pNode;
    }

    bool insert(T data);
    bool remove(T data);
    bool empty() const;
    void print() const;
    void clearList();

private:
    Node* m_pRoot; // root of the FL
};

template <typename T>
bool ForwardList<T>::insert(T data)
{
    Node* pNode = createNode();
    assert(pNode != nullptr);
    pNode->data = data;
    pNode->next = m_pRoot;
    m_pRoot = pNode;
    return true;
}

template <typename T>
bool ForwardList<T>::remove(T data)
{
    Node* pCurr = m_pRoot;
    Node* pPrev = m_pRoot;
    while ((pCurr != nullptr)) {
        if(pCurr->data == data) {
            if(pCurr == m_pRoot) {
                m_pRoot = pCurr->next;
            }
            else {
                pPrev->next = pCurr->next;
            }
            delete pCurr;
            return true;
        }
        pPrev = pCurr;
        pCurr = pCurr->next;
    }

    return false;
}

template <typename T>
void ForwardList<T>::print() const
{
    const Node* pNode = m_pRoot;
    while(pNode != nullptr) {
        std::cout << pNode->data << "\t";
        pNode = pNode->next;
    }

    std::cout << std::endl;
}

template <typename T>
bool ForwardList<T>::empty() const
{
    return (m_pRoot == nullptr);
}

template <typename T>
void ForwardList<T>::clearList()
{
    while(m_pRoot != nullptr) {
        Node* pNode = m_pRoot;
        m_pRoot = pNode->next;
        delete pNode;
    }
}

void testEmptyDelete()
{
    ForwardList<int> fl;
    assert(fl.empty());
    fl.remove(INT16_MAX);
    assert(fl.empty());
}

void testRemove()
{
    ForwardList<int> fl;
    fl.insert(INT16_MAX);
    assert(fl.empty() == false);
    assert(fl.remove(INT16_MAX));
    assert(fl.remove(INT16_MAX) == false);
    assert(fl.empty());
}

void testRemoveFromEmpty()
{
    ForwardList<int> fl;
    assert(fl.empty());
    assert(fl.remove(INT16_MAX) == false);
    assert(fl.remove(INT16_MAX) == false);
    assert(fl.remove(INT16_MAX) == false);
    assert(fl.empty());
}

void testDupsOk()
{
    ForwardList<int> fl;
    fl.insert(INT16_MAX);
    fl.insert(INT16_MAX);
    assert(fl.empty() == false);
    assert(fl.remove(INT16_MAX));
    assert(fl.remove(INT16_MAX));
    assert(fl.empty());
}

int main()
{
    testEmptyDelete();
    testDupsOk();
    testRemove();
    testRemoveFromEmpty();
    std::cout << "Done" << std::endl;
}


