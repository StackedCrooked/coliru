#include <cassert>
#include <memory>
#include <boost/iterator/iterator_facade.hpp>

#if !defined _MSC_VER
namespace std
{
    template<typename T, typename... A>
    unique_ptr<T> make_unique(A&&... a) { return unique_ptr<T>{new T(std::forward<A>(a)...)}; }
}
#endif

template<typename T>
class List
{
    struct Node
    {
        template<typename... A>
        Node(A&&... a) : m_value(std::forward<A>(a)...) {}

        T m_value;
        std::unique_ptr<Node> m_next;
    };

public:
    List() {}
    List(List&& rhs) { swap(rhs); }
    void operator=(List&& rhs) { swap(rhs); }
    void swap(List<T>& rhs) { m_head.swap(rhs.m_head); }

    struct iterator : boost::iterator_facade<iterator, T, boost::forward_traversal_tag>
    {
        Node* m_node = nullptr;
        iterator() {}
        iterator(Node* node) : m_node{node} {}

        void increment() { m_node = m_node->m_next.get(); }
        bool equal(const iterator& other) const { return m_node == other.m_node; }
        T& dereference() const { return m_node->m_value; }
    };

    iterator begin() { return{m_head.get()}; }
    iterator end() { return{}; }

    template<typename... A>
    void emplace_front(A&&... a)
    {
        prepend_node(std::make_unique<Node>(std::forward<A>(a)...));
    }

    bool empty() const { return !m_head; }

    void reverse()
    {
        List revList;

        while (!empty())
        {
            auto tail = std::move(m_head->m_next);
            revList.prepend_node(std::move(m_head));
            m_head = std::move(tail);
        }

        swap(revList);
    }

private:
    void prepend_node(std::unique_ptr<Node> node)
    {
        assert(!node->m_next);
        node->m_next = std::move(m_head);
        m_head = std::move(node);
    }

    std::unique_ptr<Node> m_head = nullptr;
};

#include <cstdio>

int main()
{
    List<int> lst;
    lst.emplace_front(3);
    lst.emplace_front(2);
    lst.emplace_front(1);

    for (auto n : lst) std::printf("%d", n);
    std::printf("\n----\n");

    lst.reverse();

    for (auto n : lst) printf("%d", n);
    std::printf("\n----\n");
}