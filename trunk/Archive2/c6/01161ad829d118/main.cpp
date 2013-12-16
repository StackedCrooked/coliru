#include <iostream>
#include <memory>
#include <utility>
 
int main () 
{
    auto deleter = [](int* ptr){
        std::cout << "[deleter called]\n";
        delete ptr;
    };
 
    std::unique_ptr<int,decltype(deleter)> uniq(new int, deleter);
    std::cout << (uniq ? "not empty\n" : "empty\n");
    uniq.reset();
    std::cout << (uniq ? "not empty\n" : "empty\n");
    
    {
        std::shared_ptr<int> sh(new int, deleter);
        std::cout << (sh ? "not empty\n" : "empty\n");
    }
    {
        std::shared_ptr<int> sh(nullptr, deleter);
        std::cout << (sh ? "not empty\n" : "empty\n");
    }
    
    {
        std::unique_ptr<int,decltype(deleter)> uniq(nullptr, deleter);
        std::shared_ptr<int> sh(std::move(uniq));
        std::cout << (sh ? "not empty\n" : "empty\n");
    }
}
