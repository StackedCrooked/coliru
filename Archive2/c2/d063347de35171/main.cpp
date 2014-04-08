template<typename Type>
class List
{
private:
    struct Node
    {
        Type  m_Value;
        Node* m_pNext;
    };
    
    Node* m_pHead;
    
public:
    
    class const_iterator
    {
    private:
        Node* m_pNode;
        friend List;
        const_iterator(Node* p_pNode) : m_pNode(p_pNode) {}
        
    public:
        const_iterator() : m_pNode(nullptr) {}
        
        explicit operator bool() const
        { return m_pNode; }
        
        const_iterator& operator++()
        { m_pNode = m_pNode->m_pNext; return *this; }
        
        Type const& operator*()
        { return m_pNode->m_Value; }
        
        friend bool operator!=(const_iterator const& lhs, const_iterator const& rhs)
        {
            return lhs.m_pNode != rhs.m_pNode;
        }
    };
    
    List() : m_pHead(nullptr) {}
    ~List()
    {
        // delete nodes
    }
    List(List const&) = delete; // needs to be customized
    List& operator=(List const&) = delete; // this one, too

    void AddHead( Type const& value )
    {
        Node* pNode = new Node{value, m_pHead};
        m_pHead = pNode;
    }

    const_iterator begin() const
    { return {m_pHead}; }
    const_iterator end() const
    { return {nullptr}; }
};

#include <iostream>
int main()
{
    List<int> l;
    for(int i = 0; i < 10; ++i) l.AddHead(i);
    for(auto i = l.begin(); i != l.end(); ++i) std::cout << *i << ", ";
}