#include <mutex>
#include <unordered_map>
#include <cassert>

int main()
{
    std::unordered_map<int, std::mutex> m;
    
    m[1];
    
    assert(m.size() == 1);
}
