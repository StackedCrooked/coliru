#include <unordered_map>
#include <memory>
#include <iostream>

typedef std::unique_ptr < int > UniqueInt;

int main() {
    std::unordered_map<uint32_t, std::unique_ptr<int> > umap;
    UniqueInt p(new int(100));
    umap.emplace(1, std::move(p));
    
    // new
    for (const auto &i : umap)
      std::cout << *(i.second) << " " << std::endl;
    
    // old
    for(auto it = umap.begin(); it != umap.end(); it++)
    {
      std::cout << *(it->second);
    }
    return 0;
}