#include <memory>

template<class T>
struct shared_stack_node {
    T head;
    std::shared_ptr<shared_stack_node> tail;
};

template<class T>
class shared_stack {
private:
    std::shared_ptr<shared_stack_node<T>> data_;
    
public:
    bool empty() const { return !data_; }
    const T& top() const { return data_->head; }
    void pop() { data_ = data_->tail; }
    void push(const T& value) {
        data_ = std::make_shared<shared_stack_node<T>>(value, data_);
    }
};

//...
class tree_iterator {
    //...
    shared_stack<tree_node*> stack;
    //...
};


