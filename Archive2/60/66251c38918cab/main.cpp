#include <memory>
#include <string>
#include <iostream>

struct Node
{
    std::string name = "Node";
    virtual ~Node() = default;
};

struct Filter : Node
{
    Filter(unsigned id) : filter_id(id) 
    {
        name = "Filter";
    }
    unsigned filter_id;
};

int main()
{
    std::shared_ptr<Node> n = std::make_shared<Filter>(42);
    auto f = std::dynamic_pointer_cast<Filter>(n);
    
    if(f) {
        // The managed object is a Filter
        std::cout << f->filter_id << '\n';
    }
}
