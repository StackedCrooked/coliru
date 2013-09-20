#include <unordered_map>

int main()
{
    typedef std::allocator<std::pair<const int, int>> A;
    typedef std::unordered_map<int, int, std::hash<int>, std::equal_to<int>, A> H;    
    
    auto h = H{A()}; // should call H::H(const A&)
}
