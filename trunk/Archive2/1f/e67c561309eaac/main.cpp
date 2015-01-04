#include <memory>
#include <utility>

template<typename T>
struct node
{
    node* next;
    
    T& get_data();
};

template<typename T>
struct node_plus_data : node<T>
{
    T data;
    
    template<typename... Args>
    node_plus_data(node<T>* next, Args&&... args)
        : node<T>{next}, data{std::forward<Args>(args)...}
    {}
};

template<typename T>
T& node<T>::get_data()
{
    auto const npd = static_cast<node_plus_data<T>*>(this);
    return npd->data;
}

template<typename TargetType, typename... CreationArgs>
auto create_node(node<TargetType>* const prev, CreationArgs&&... ca)
-> node_plus_data<TargetType>*
{
    auto const npd = new node_plus_data<TargetType>{nullptr, std::forward<CreationArgs>(ca)...};
    if(prev) prev->next = npd;
    return npd;
}

template<typename TargetType>
auto create_node(node<TargetType>* const prev)
-> node<TargetType>*
{
    auto const n = new node<TargetType>{nullptr};
    if(prev) prev->next = n;
    return n;
}


#include <iostream>

int main()
{
    auto x = create_node<int>(nullptr);
    auto y = create_node<int>(x, 42);
    std::cout << y->get_data();
}