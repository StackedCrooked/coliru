#include <memory>
#include <utility>

template<typename T>
struct node
{
    node* next;
    T& get_data();
};

template<typename T>
struct node_and_data
{
    node<T> node;
    T data;
};

//template<typename T>
//T& node<T>::get_data(); // implementation missing


template<typename TargetType, typename... CreationArgs>
auto create_node(node<TargetType>* const prev, CreationArgs&&... ca)
-> node<TargetType>*
{
    auto const nad = new node_and_data<TargetType>{{nullptr}, {std::forward<CreationArgs>(ca)...}};
    auto const n = &nad->node;
    prev->next = n;
    return n;
}

template<typename TargetType>
auto create_node(node<TargetType>* const prev)
-> node<TargetType>*
{
    auto const n = new node<TargetType>{nullptr};
    return n;
}

int main()
{
    auto x = create_node<int>(nullptr);
    auto y = create_node<int>(x, 42);
}