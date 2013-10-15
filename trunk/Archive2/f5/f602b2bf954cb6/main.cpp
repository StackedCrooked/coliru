#include <list>
#include <memory>
#include <iostream>

using Item = int;

int main()
{
    auto lst = std::list< std::shared_ptr<Item> > 
    { 
        std::make_shared<int>(0), 
        std::make_shared<int>(1), 
        std::make_shared<int>(2), 
        std::make_shared<int>(3),         
    };    
    
    // shared_ptrs to even elements
    auto x0 = *std::next(begin(lst), 0);
    auto x2 = *std::next(begin(lst), 2);
    
    // remove even numbers
    lst.remove_if([](std::shared_ptr<int> p){
        return *p % 2 == 0;    
    });
    
    // even number have been erased
    for (auto it = begin(lst); it != end(lst); ++it)
        std::cout << **it << ",";    
    std::cout << "\n";
    
    // shared pointers to even member are still valid
    std::cout << *x0 << "," << *x2;
}