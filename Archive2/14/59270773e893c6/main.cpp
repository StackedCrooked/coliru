#include <atomic>
 
template<class T>
struct node
{
    T data;
    node* next;
    node(const T& data) : data(data), next(nullptr) {}
};
 
template<class T>
class stack
{
    std::atomic<node<T>*> head;
 public:
    void push(const T& data)
    {
        node<T>* new_node = new node<T>(data);
 
        // put the current value of head into new_node->next
        new_node->next = head.load(std::memory_order_relaxed);
 
        // now make new_node the new head, but if the head
        // is no longer what's stored in new_node->next
        // (some other thread must have inserted a node just now)
        // then put that new head into new_node->next and try again
        while(!std::atomic_compare_exchange_weak_explicit(
                                &head,
                                &new_node->next,
                                new_node,
                                std::memory_order_release,
                                std::memory_order_relaxed))
                ; // the body of the loop is empty
    }
};
 
int main()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
}