#include <unordered_set>
#include <memory>
#include <iostream>

struct MyHasher
{
    std::size_t operator() (const std::shared_ptr<int>& ptr) const
    {
        return std::hash<int>()(*ptr);
    }
};

int main()
{
    std::unordered_set<std::shared_ptr<int>, MyHasher> s;
    
    s.emplace(std::make_shared<int>(1));
    s.emplace(std::make_shared<int>(2));
    
    std::cout << s.size() << ' ';
    
    s.emplace(std::make_shared<int>(1));
    s.emplace(std::make_shared<int>(2));
    
    std::cout << s.size() << "\n\nHashes:\n";
 
    for (auto el : s)
        std::cout << s.hash_function()(el) << '\n';
}

// Output is 4, not 2. Yet the hashes clearly are the same.
