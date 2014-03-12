#include <iostream>
#include <vector>
#include <memory>

namespace li
{
  template <typename T> class linked_list
  {
    struct Node
    {
        Node(const T t,
             const std::shared_ptr<Node>& before,
             const std::shared_ptr<Node>& after) : t(t), before(before),
                                                         after(after) {}
        T t;
        std::shared_ptr<Node> before;
        std::shared_ptr<Node> after;
    };
  public:
    struct list_iterator
    {
        using value_type = T;
        using difference_type = int;
        using pointer = list_iterator::value_type*;
        using reference = list_iterator::value_type&;
        using iterator_category = std::bidirectional_iterator_tag;
        
        std::shared_ptr<Node> node;
        
        T& operator*()
        {
            return node->t;
        }
        T& operator++()
        {
            node = node->after;
            return node->t;
        }
        T& operator--()
        {
            node = node->before;
            return node->t;
        }
        T operator++(int)
        {
            T t = node->t;
            node = node->after;
            return t;
        }
        T operator--(int)
        {
            T t = node->t;
            node = node->before;
            return t;
        }
        
        bool operator==(list_iterator it) { return this->node == it.node;}
        bool operator!=(list_iterator it) { return !(*this == it); }
    };
    using iterator = list_iterator;
    using value_type = typename iterator::value_type;
    using difference_type = typename iterator::difference_type;
    using pointer = typename iterator::pointer;
    using reference = typename iterator::reference;
    using iterator_category = typename iterator::iterator_category;
  public:
    linked_list() : begin_(nullptr) {}
    void push_back(const T& t)
    {
        if(!begin_)
        {
            this->begin_ = std::make_shared<Node>(t, nullptr, nullptr);
            return;
        }
        std::shared_ptr<Node> node = begin_;
        while(!node->after)
        {
            node = node->after;
        }
        node->after = std::make_shared<Node>(t, nullptr, nullptr);
        node->after->before = node;
    }
    iterator begin()
    {
        return iterator{begin_};    
    }
    iterator end()
    {
        return iterator{nullptr};  
    }
    void erase(iterator it)
    {
      Node& node = *it.node;
      node.before->after = node.after;
      node.after->before = node.before;
    }
  private:
    std::shared_ptr<Node> begin_;
  };
}
int main()
{
  // Populate
  li::linked_list<int> list;
  list.push_back(5);
  list.push_back(7);
  list.push_back(1);
  list.push_back(7);
  list.push_back(5);
  // Iterate through
  for(int i : list)
  {
    std::cout << i << std::endl;    
  }
  // Remove an element
  auto it = list.begin();
  std::advance(it, 2);
  list.erase(it);
  // Iterate through
  for(int i : list)
  {
    std::cout << i << std::endl;
  }
}