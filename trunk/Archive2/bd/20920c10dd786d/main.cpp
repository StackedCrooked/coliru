#include <algorithm>
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
    auto res = std::remove_if(begin(lst), end(lst), [](std::shared_ptr<int> p){
        return *p % 2 == 0;    
    });
    
    // even numbers have been put at the end of the list in an unspecified state
    for (auto it = begin(lst); it != res; ++it)
        std::cout << **it << ",";    
    std::cout << "\n";
    
    // erase even numbers
    lst.erase(res, end(lst));
    
    // even number have been put at the end of the list
    for (auto it = begin(lst); it != end(lst); ++it)
        std::cout << **it << ",";    
    std::cout << "\n";

    // shared pointers to even member are still valid
    std::cout << *x0 << "," << *x2;
}